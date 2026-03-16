static ssize_t net_slirp_receive ( NetClientState * nc , const uint8_t * buf , size_t size ) {
 SlirpState * s = DO_UPCAST ( SlirpState , nc , nc ) ;
 slirp_input ( s -> slirp , buf , size ) ;
 return size ;
 }