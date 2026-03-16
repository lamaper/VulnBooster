static int tcp_write(URLContext *h, uint8_t *buf, int size)

{

    TCPContext *s = h->priv_data;

    int ret, size1, fd_max;

    fd_set wfds;

    struct timeval tv;



    size1 = size;

    while (size > 0) {

        if (url_interrupt_cb())

            return -EINTR;

        fd_max = s->fd;

        FD_ZERO(&wfds);

        FD_SET(s->fd, &wfds);

        tv.tv_sec = 0;

        tv.tv_usec = 100 * 1000;

        select(fd_max + 1, NULL, &wfds, NULL, &tv);


        ret = send(s->fd, buf, size, 0);


        ret = write(s->fd, buf, size);


        if (ret < 0) {

            if (errno != EINTR && errno != EAGAIN) {


                return errno;


                return -errno;


            }

            continue;

        }

        size -= ret;

        buf += ret;

    }

    return size1 - size;

}
