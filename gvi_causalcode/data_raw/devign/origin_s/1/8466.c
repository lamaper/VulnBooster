ssize_t vnc_client_write_buf(VncState *vs, const uint8_t *data, size_t datalen)

{

    ssize_t ret;


    if (vs->tls.session) {

        ret = vnc_client_write_tls(&vs->tls.session, data, datalen);

    } else {


        ret = send(vs->csock, (const void *)data, datalen, 0);


    }


    VNC_DEBUG("Wrote wire %p %zd -> %ld\n", data, datalen, ret);

    return vnc_client_io_error(vs, ret, socket_error());

}
