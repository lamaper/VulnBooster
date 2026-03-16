static void vnc_client_write_locked(void *opaque)

{

    VncState *vs = opaque;


    if (vs->sasl.conn &&

        vs->sasl.runSSF &&

        !vs->sasl.waitWriteSSF) {

        vnc_client_write_sasl(vs);

    } else


    {


        if (vs->encode_ws) {

            vnc_client_write_ws(vs);

        } else


        {

            vnc_client_write_plain(vs);

        }

    }

}
