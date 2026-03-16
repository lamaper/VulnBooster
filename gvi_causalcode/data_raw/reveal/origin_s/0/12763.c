static void guestfwd_read ( void * opaque , const uint8_t * buf , int size ) {
 struct GuestFwd * fwd = opaque ;
 slirp_socket_recv ( fwd -> slirp , fwd -> server , fwd -> port , buf , size ) ;
 }