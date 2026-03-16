int qemu_socket(int domain, int type, int protocol)

{

    int ret;


    ret = socket(domain, type | SOCK_CLOEXEC, protocol);


    ret = socket(domain, type, protocol);

    if (ret >= 0) {

        qemu_set_cloexec(ret);

    }




    return ret;

}
