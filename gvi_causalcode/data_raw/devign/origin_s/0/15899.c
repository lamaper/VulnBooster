static int qcow2_create2(const char *filename, int64_t total_size,

                         const char *backing_file, const char *backing_format,

                         int flags, size_t cluster_size, PreallocMode prealloc,

                         QemuOpts *opts, int version, int refcount_order,

                         Error **errp)

{

     

    int cluster_bits;

    cluster_bits = ffs(cluster_size) - 1;

    if (cluster_bits < MIN_CLUSTER_BITS || cluster_bits > MAX_CLUSTER_BITS ||

        (1 << cluster_bits) != cluster_size)

    {

        error_setg(errp, "Cluster size must be a power of two between %d and "

                   "%dk", 1 << MIN_CLUSTER_BITS, 1 << (MAX_CLUSTER_BITS - 10));

        return -EINVAL;

    }



     

    BlockDriverState* bs;

    QCowHeader *header;

    uint64_t* refcount_table;

    Error *local_err = NULL;

    int ret;



    if (prealloc == PREALLOC_MODE_FULL || prealloc == PREALLOC_MODE_FALLOC) {

         

        int64_t meta_size = 0;

        uint64_t nreftablee, nrefblocke, nl1e, nl2e;

        int64_t aligned_total_size = align_offset(total_size, cluster_size);

        int refblock_bits, refblock_size;

         

        double rces = (1 << refcount_order) / 8.;



         

        refblock_bits = cluster_bits - (refcount_order - 3);

        refblock_size = 1 << refblock_bits;



         

        meta_size += cluster_size;



         

        nl2e = aligned_total_size / cluster_size;

        nl2e = align_offset(nl2e, cluster_size / sizeof(uint64_t));

        meta_size += nl2e * sizeof(uint64_t);



         

        nl1e = nl2e * sizeof(uint64_t) / cluster_size;

        nl1e = align_offset(nl1e, cluster_size / sizeof(uint64_t));

        meta_size += nl1e * sizeof(uint64_t);



         

        nrefblocke = (aligned_total_size + meta_size + cluster_size)

                   / (cluster_size - rces - rces * sizeof(uint64_t)

                                                 / cluster_size);

        meta_size += DIV_ROUND_UP(nrefblocke, refblock_size) * cluster_size;



         

        nreftablee = nrefblocke / refblock_size;

        nreftablee = align_offset(nreftablee, cluster_size / sizeof(uint64_t));

        meta_size += nreftablee * sizeof(uint64_t);



        qemu_opt_set_number(opts, BLOCK_OPT_SIZE,

                            aligned_total_size + meta_size, &error_abort);

        qemu_opt_set(opts, BLOCK_OPT_PREALLOC, PreallocMode_lookup[prealloc],

                     &error_abort);

    }



    ret = bdrv_create_file(filename, opts, &local_err);

    if (ret < 0) {

        error_propagate(errp, local_err);

        return ret;

    }



    bs = NULL;

    ret = bdrv_open(&bs, filename, NULL, NULL, BDRV_O_RDWR | BDRV_O_PROTOCOL,

                    NULL, &local_err);

    if (ret < 0) {

        error_propagate(errp, local_err);

        return ret;

    }



     

    QEMU_BUILD_BUG_ON((1 << MIN_CLUSTER_BITS) < sizeof(*header));

    header = g_malloc0(cluster_size);

    *header = (QCowHeader) {

        .magic                      = cpu_to_be32(QCOW_MAGIC),

        .version                    = cpu_to_be32(version),

        .cluster_bits               = cpu_to_be32(cluster_bits),

        .size                       = cpu_to_be64(0),

        .l1_table_offset            = cpu_to_be64(0),

        .l1_size                    = cpu_to_be32(0),

        .refcount_table_offset      = cpu_to_be64(cluster_size),

        .refcount_table_clusters    = cpu_to_be32(1),

        .refcount_order             = cpu_to_be32(refcount_order),

        .header_length              = cpu_to_be32(sizeof(*header)),

    };



    if (flags & BLOCK_FLAG_ENCRYPT) {

        header->crypt_method = cpu_to_be32(QCOW_CRYPT_AES);

    } else {

        header->crypt_method = cpu_to_be32(QCOW_CRYPT_NONE);

    }



    if (flags & BLOCK_FLAG_LAZY_REFCOUNTS) {

        header->compatible_features |=

            cpu_to_be64(QCOW2_COMPAT_LAZY_REFCOUNTS);

    }



    ret = bdrv_pwrite(bs, 0, header, cluster_size);

    g_free(header);

    if (ret < 0) {

        error_setg_errno(errp, -ret, "Could not write qcow2 header");

        goto out;

    }



     

    refcount_table = g_malloc0(2 * cluster_size);

    refcount_table[0] = cpu_to_be64(2 * cluster_size);

    ret = bdrv_pwrite(bs, cluster_size, refcount_table, 2 * cluster_size);

    g_free(refcount_table);



    if (ret < 0) {

        error_setg_errno(errp, -ret, "Could not write refcount table");

        goto out;

    }



    bdrv_unref(bs);

    bs = NULL;



     

    ret = bdrv_open(&bs, filename, NULL, NULL,

                    BDRV_O_RDWR | BDRV_O_CACHE_WB | BDRV_O_NO_FLUSH,

                    &bdrv_qcow2, &local_err);

    if (ret < 0) {

        error_propagate(errp, local_err);

        goto out;

    }



    ret = qcow2_alloc_clusters(bs, 3 * cluster_size);

    if (ret < 0) {

        error_setg_errno(errp, -ret, "Could not allocate clusters for qcow2 "

                         "header and refcount table");

        goto out;



    } else if (ret != 0) {

        error_report("Huh, first cluster in empty image is already in use?");

        abort();

    }



     

    ret = bdrv_truncate(bs, total_size);

    if (ret < 0) {

        error_setg_errno(errp, -ret, "Could not resize image");

        goto out;

    }



     

    if (backing_file) {

        ret = bdrv_change_backing_file(bs, backing_file, backing_format);

        if (ret < 0) {

            error_setg_errno(errp, -ret, "Could not assign backing file '%s' "

                             "with format '%s'", backing_file, backing_format);

            goto out;

        }

    }



     

    if (prealloc != PREALLOC_MODE_OFF) {

        BDRVQcowState *s = bs->opaque;

        qemu_co_mutex_lock(&s->lock);

        ret = preallocate(bs);

        qemu_co_mutex_unlock(&s->lock);

        if (ret < 0) {

            error_setg_errno(errp, -ret, "Could not preallocate metadata");

            goto out;

        }

    }



    bdrv_unref(bs);

    bs = NULL;



     

    ret = bdrv_open(&bs, filename, NULL, NULL,

                    BDRV_O_RDWR | BDRV_O_CACHE_WB | BDRV_O_NO_BACKING,

                    &bdrv_qcow2, &local_err);

    if (local_err) {

        error_propagate(errp, local_err);

        goto out;

    }



    ret = 0;

out:

    if (bs) {

        bdrv_unref(bs);

    }

    return ret;

}
