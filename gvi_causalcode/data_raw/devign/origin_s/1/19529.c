void net_cleanup(void)

{


    VLANState *vlan;



     

    for(vlan = first_vlan; vlan != NULL; vlan = vlan->next) {

        VLANClientState *vc;



        for(vc = vlan->first_client; vc != NULL; vc = vc->next) {

            if (vc->fd_read == tap_receive) {

                TAPState *s = vc->opaque;



                if (s->down_script[0])

                    launch_script(s->down_script, s->down_script_arg, s->fd);

            }


            if (vc->fd_read == vde_from_qemu) {

                VDEState *s = vc->opaque;

                vde_close(s->vde);

            }


        }

    }


}
