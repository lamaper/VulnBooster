static int tcp_read(URLContext *h, uint8_t *buf, int size)

{

    TCPContext *s = h->priv_data;

    int size1, len, fd_max;

    fd_set rfds;

    struct timeval tv;



    size1 = size;

    while (size > 0) {

        if (url_interrupt_cb())

            return -EINTR;

        fd_max = s->fd;

        FD_ZERO(&rfds);

        FD_SET(s->fd, &rfds);

        tv.tv_sec = 0;

        tv.tv_usec = 100 * 1000;

        select(fd_max + 1, &rfds, NULL, NULL, &tv);


        len = recv(s->fd, buf, size, 0);


        len = read(s->fd, buf, size);


        if (len < 0) {

            if (errno != EINTR && errno != EAGAIN)


                return errno;


                return -errno;


            else

                continue;

        } else if (len == 0) {

            break;

        }

        size -= len;

        buf += len;

    }

    return size1 - size;

}
