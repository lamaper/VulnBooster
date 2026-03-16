void net_cleanup(void)

{

    VLANState *vlan;


     

    for(vlan = first_vlan; vlan != NULL; vlan = vlan->next) {

        VLANClientState *vc;



        for(vc = vlan->first_client; vc != NULL; vc = vc->next) {

            if (vc->fd_read == tap_receive) {

                char ifname[64];

                TAPState *s = vc->opaque;



                if (strcmp(vc->model, "tap") == 0 &&

                    sscanf(vc->info_str, "ifname=%63s ", ifname) == 1 &&

                    s->down_script[0])

                    launch_script(s->down_script, ifname, s->fd);

            }


            if (vc->fd_read == vde_from_qemu) {

                VDEState *s = vc->opaque;

                vde_close(s->vde);

            }


        }

    }


}
