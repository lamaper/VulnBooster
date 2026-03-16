int qemu_accept(int s, struct sockaddr *addr, socklen_t *addrlen)

{

    int ret;


    ret = accept4(s, addr, addrlen, SOCK_CLOEXEC);

    if (ret != -1 || errno != EINVAL) {

        return ret;

    }


    ret = accept(s, addr, addrlen);

    if (ret >= 0) {

        qemu_set_cloexec(ret);

    }



    return ret;

}
