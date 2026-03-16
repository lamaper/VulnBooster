static int pipe_open(URLContext *h, const char *filename, int flags)

{

    int fd;



    if (flags & URL_WRONLY) {

        fd = 1;

    } else {

        fd = 0;

    }


    setmode(fd, O_BINARY);


    h->priv_data = (void *)(size_t)fd;

    h->is_streamed = 1;

    return 0;

}
