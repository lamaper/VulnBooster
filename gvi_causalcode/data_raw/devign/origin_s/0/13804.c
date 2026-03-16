static ssize_t proxy_preadv(FsContext *ctx, V9fsFidOpenState *fs,

                            const struct iovec *iov,

                            int iovcnt, off_t offset)

{

    ssize_t ret;


    ret = preadv(fs->fd, iov, iovcnt, offset);


    ret = lseek(fs->fd, offset, SEEK_SET);

    if (ret >= 0) {

        ret = readv(fs->fd, iov, iovcnt);

    }


    return ret;

}
