void slirp_output ( void * opaque , const uint8_t * pkt , int pkt_len ) {
 SlirpState * s = opaque ;
 qemu_send_packet ( & s -> nc , pkt , pkt_len ) ;
 }