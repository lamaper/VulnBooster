ber_slen_t ber_skip_data ( BerElement * ber , ber_len_t len ) {
 ber_len_t actuallen , nleft ;
 assert ( ber != NULL ) ;
 assert ( LBER_VALID ( ber ) ) ;
 nleft = ber_pvt_ber_remaining ( ber ) ;
 actuallen = nleft < len ? nleft : len ;
 ber -> ber_ptr += actuallen ;
 ber -> ber_tag = * ( unsigned char * ) ber -> ber_ptr ;
 return ( ( ber_slen_t ) actuallen ) ;
 }