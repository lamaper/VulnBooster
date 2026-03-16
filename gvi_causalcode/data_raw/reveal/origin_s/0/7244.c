static int nbd_can_accept ( void ) {
 return state == RUNNING && nb_fds < shared ;
 }