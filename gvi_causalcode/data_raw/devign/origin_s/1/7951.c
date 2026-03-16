int ff_socket(int af, int type, int proto)

{

    int fd;


    fd = socket(af, type | SOCK_CLOEXEC, proto);

    if (fd == -1 && errno == EINVAL)


    {

        fd = socket(af, type, proto);


        if (fd != -1)

            fcntl(fd, F_SETFD, FD_CLOEXEC);


    }

    return fd;

}
