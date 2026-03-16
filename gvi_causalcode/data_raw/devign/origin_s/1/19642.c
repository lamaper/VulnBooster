ssize_t vnc_client_read_buf(VncState *vs, uint8_t *data, size_t datalen)

{

    ssize_t ret;


    if (vs->tls.session) {

        ret = vnc_client_read_tls(&vs->tls.session, data, datalen);

    } else {


        ret = qemu_recv(vs->csock, data, datalen, 0);


    }


    VNC_DEBUG("Read wire %p %zd -> %ld\n", data, datalen, ret);

    return vnc_client_io_error(vs, ret, socket_error());

}
