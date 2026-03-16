static ssize_t handle_aiocb_discard(RawPosixAIOData *aiocb)

{

    int ret = -EOPNOTSUPP;

    BDRVRawState *s = aiocb->bs->opaque;



    if (s->has_discard == 0) {

        return 0;

    }



    if (aiocb->aio_type & QEMU_AIO_BLKDEV) {


        do {

            uint64_t range[2] = { aiocb->aio_offset, aiocb->aio_nbytes };

            if (ioctl(aiocb->aio_fildes, BLKDISCARD, range) == 0) {

                return 0;

            }

        } while (errno == EINTR);



        ret = -errno;


    } else {


        if (s->is_xfs) {

            return xfs_discard(s, aiocb->aio_offset, aiocb->aio_nbytes);

        }



        do {

            if (fallocate(s->fd, FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE,

                          aiocb->aio_offset, aiocb->aio_nbytes) == 0) {

                return 0;

            }

        } while (errno == EINTR);



        ret = -errno;


    }



    if (ret == -ENODEV || ret == -ENOSYS || ret == -EOPNOTSUPP ||

        ret == -ENOTTY) {

        s->has_discard = 0;

        ret = 0;

    }

    return ret;

}
