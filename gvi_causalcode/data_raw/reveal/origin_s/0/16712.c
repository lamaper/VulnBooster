ber_slen_t ber_read ( BerElement * ber , char * buf , ber_len_t len ) {
 ber_len_t actuallen , nleft ;
 assert ( ber != NULL ) ;
 assert ( buf != NULL ) ;
 assert ( LBER_VALID ( ber ) ) ;
 nleft = ber_pvt_ber_remaining ( ber ) ;
 actuallen = nleft < len ? nleft : len ;
 AC_MEMCPY ( buf , ber -> ber_ptr , actuallen ) ;
 ber -> ber_ptr += actuallen ;
 return ( ( ber_slen_t ) actuallen ) ;
 }