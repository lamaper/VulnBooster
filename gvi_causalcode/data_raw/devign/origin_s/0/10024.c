static int qcow_read_extensions(BlockDriverState *bs, uint64_t start_offset,

                                uint64_t end_offset)

{

    BDRVQcowState *s = bs->opaque;

    QCowExtension ext;

    uint64_t offset;


    printf("qcow_read_extensions: start=%ld end=%ld\n", start_offset, end_offset);


    offset = start_offset;

    while (offset < end_offset) {


         

        if (offset > s->cluster_size)

            printf("qcow_handle_extension: suspicious offset %lu\n", offset);



        printf("attemting to read extended header in offset %lu\n", offset);




        if (bdrv_pread(s->hd, offset, &ext, sizeof(ext)) != sizeof(ext)) {

            fprintf(stderr, "qcow_handle_extension: ERROR: pread fail from offset %llu\n",

                    (unsigned long long)offset);

            return 1;

        }

        be32_to_cpus(&ext.magic);

        be32_to_cpus(&ext.len);

        offset += sizeof(ext);


        printf("ext.magic = 0x%x\n", ext.magic);


        switch (ext.magic) {

        case QCOW_EXT_MAGIC_END:

            return 0;



        case QCOW_EXT_MAGIC_BACKING_FORMAT:

            if (ext.len >= sizeof(bs->backing_format)) {

                fprintf(stderr, "ERROR: ext_backing_format: len=%u too large"

                        " (>=%zu)\n",

                        ext.len, sizeof(bs->backing_format));

                return 2;

            }

            if (bdrv_pread(s->hd, offset , bs->backing_format,

                           ext.len) != ext.len)

                return 3;

            bs->backing_format[ext.len] = '\0';


            printf("Qcow2: Got format extension %s\n", bs->backing_format);


            offset += ((ext.len + 7) & ~7);

            break;



        default:

             

            offset += ((ext.len + 7) & ~7);

            break;

        }

    }



    return 0;

}
