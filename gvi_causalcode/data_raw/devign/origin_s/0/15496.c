static int img_rebase(int argc, char **argv)

{

    BlockDriverState *bs, *bs_old_backing = NULL, *bs_new_backing = NULL;

    BlockDriver *old_backing_drv, *new_backing_drv;

    char *filename;

    const char *fmt, *cache, *out_basefmt, *out_baseimg;

    int c, flags, ret;

    int unsafe = 0;

    int progress = 0;



     

    fmt = NULL;

    cache = BDRV_DEFAULT_CACHE;

    out_baseimg = NULL;

    out_basefmt = NULL;

    for(;;) {

        c = getopt(argc, argv, "uhf:F:b:pt:");

        if (c == -1) {

            break;

        }

        switch(c) {

        case '?':

        case 'h':

            help();

            return 0;

        case 'f':

            fmt = optarg;

            break;

        case 'F':

            out_basefmt = optarg;

            break;

        case 'b':

            out_baseimg = optarg;

            break;

        case 'u':

            unsafe = 1;

            break;

        case 'p':

            progress = 1;

            break;

        case 't':

            cache = optarg;

            break;

        }

    }



    if ((optind >= argc) || (!unsafe && !out_baseimg)) {

        help();

    }

    filename = argv[optind++];



    qemu_progress_init(progress, 2.0);

    qemu_progress_print(0, 100);



    flags = BDRV_O_RDWR | (unsafe ? BDRV_O_NO_BACKING : 0);

    ret = bdrv_parse_cache_flags(cache, &flags);

    if (ret < 0) {

        error_report("Invalid cache option: %s", cache);

        return -1;

    }



     

    bs = bdrv_new_open(filename, fmt, flags);

    if (!bs) {

        return 1;

    }



     

    old_backing_drv = NULL;

    new_backing_drv = NULL;



    if (!unsafe && bs->backing_format[0] != '\0') {

        old_backing_drv = bdrv_find_format(bs->backing_format);

        if (old_backing_drv == NULL) {

            error_report("Invalid format name: '%s'", bs->backing_format);

            ret = -1;

            goto out;

        }

    }



    if (out_basefmt != NULL) {

        new_backing_drv = bdrv_find_format(out_basefmt);

        if (new_backing_drv == NULL) {

            error_report("Invalid format name: '%s'", out_basefmt);

            ret = -1;

            goto out;

        }

    }



     

    if (unsafe) {

         

        bs_old_backing = NULL;

        bs_new_backing = NULL;

    } else {

        char backing_name[1024];



        bs_old_backing = bdrv_new("old_backing");

        bdrv_get_backing_filename(bs, backing_name, sizeof(backing_name));

        ret = bdrv_open(bs_old_backing, backing_name, BDRV_O_FLAGS,

                        old_backing_drv);

        if (ret) {

            error_report("Could not open old backing file '%s'", backing_name);

            goto out;

        }



        bs_new_backing = bdrv_new("new_backing");

        ret = bdrv_open(bs_new_backing, out_baseimg, BDRV_O_FLAGS,

                        new_backing_drv);

        if (ret) {

            error_report("Could not open new backing file '%s'", out_baseimg);

            goto out;

        }

    }



     

    if (!unsafe) {

        uint64_t num_sectors;

        uint64_t old_backing_num_sectors;

        uint64_t new_backing_num_sectors;

        uint64_t sector;

        int n;

        uint8_t * buf_old;

        uint8_t * buf_new;

        float local_progress;



        buf_old = qemu_blockalign(bs, IO_BUF_SIZE);

        buf_new = qemu_blockalign(bs, IO_BUF_SIZE);



        bdrv_get_geometry(bs, &num_sectors);

        bdrv_get_geometry(bs_old_backing, &old_backing_num_sectors);

        bdrv_get_geometry(bs_new_backing, &new_backing_num_sectors);



        local_progress = (float)100 /

            (num_sectors / MIN(num_sectors, IO_BUF_SIZE / 512));

        for (sector = 0; sector < num_sectors; sector += n) {



             

            if (sector + (IO_BUF_SIZE / 512) <= num_sectors) {

                n = (IO_BUF_SIZE / 512);

            } else {

                n = num_sectors - sector;

            }



             

            ret = bdrv_is_allocated(bs, sector, n, &n);

            if (ret) {

                continue;

            }



             

            if (sector >= old_backing_num_sectors) {

                memset(buf_old, 0, n * BDRV_SECTOR_SIZE);

            } else {

                if (sector + n > old_backing_num_sectors) {

                    n = old_backing_num_sectors - sector;

                }



                ret = bdrv_read(bs_old_backing, sector, buf_old, n);

                if (ret < 0) {

                    error_report("error while reading from old backing file");

                    goto out;

                }

            }



            if (sector >= new_backing_num_sectors) {

                memset(buf_new, 0, n * BDRV_SECTOR_SIZE);

            } else {

                if (sector + n > new_backing_num_sectors) {

                    n = new_backing_num_sectors - sector;

                }



                ret = bdrv_read(bs_new_backing, sector, buf_new, n);

                if (ret < 0) {

                    error_report("error while reading from new backing file");

                    goto out;

                }

            }



             

            uint64_t written = 0;



            while (written < n) {

                int pnum;



                if (compare_sectors(buf_old + written * 512,

                    buf_new + written * 512, n - written, &pnum))

                {

                    ret = bdrv_write(bs, sector + written,

                        buf_old + written * 512, pnum);

                    if (ret < 0) {

                        error_report("Error while writing to COW image: %s",

                            strerror(-ret));

                        goto out;

                    }

                }



                written += pnum;

            }

            qemu_progress_print(local_progress, 100);

        }



        qemu_vfree(buf_old);

        qemu_vfree(buf_new);

    }



     

    ret = bdrv_change_backing_file(bs, out_baseimg, out_basefmt);

    if (ret == -ENOSPC) {

        error_report("Could not change the backing file to '%s': No "

                     "space left in the file header", out_baseimg);

    } else if (ret < 0) {

        error_report("Could not change the backing file to '%s': %s",

            out_baseimg, strerror(-ret));

    }



    qemu_progress_print(100, 0);

     

out:

    qemu_progress_end();

     

    if (!unsafe) {

        if (bs_old_backing != NULL) {

            bdrv_delete(bs_old_backing);

        }

        if (bs_new_backing != NULL) {

            bdrv_delete(bs_new_backing);

        }

    }



    bdrv_delete(bs);

    if (ret) {

        return 1;

    }

    return 0;

}
