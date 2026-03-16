static int guestfwd_can_read ( void * opaque ) {
 struct GuestFwd * fwd = opaque ;
 return slirp_socket_can_recv ( fwd -> slirp , fwd -> server , fwd -> port ) ;
 }