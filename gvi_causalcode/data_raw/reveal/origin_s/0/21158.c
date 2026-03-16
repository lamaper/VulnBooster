int ber_realloc ( BerElement * ber , ber_len_t len ) {
 ber_len_t total , offset , sos_offset ;
 char * buf ;
 assert ( ber != NULL ) ;
 assert ( LBER_VALID ( ber ) ) ;
 if ( ++ len == 0 ) {
 return ( - 1 ) ;
 }
 total = ber_pvt_ber_total ( ber ) ;


 ber_len_t have = ( total + ( LBER_EXBUFSIZE - 1 ) ) / LBER_EXBUFSIZ ;
 ber_len_t need = ( len + ( LBER_EXBUFSIZ - 1 ) ) / LBER_EXBUFSIZ ;
 total = ( have + need ) * LBER_EXBUFSIZ ;
 }


 return ( - 1 ) ;
 }
 buf = ber -> ber_buf ;
 offset = ber -> ber_ptr - buf ;
 sos_offset = ber -> ber_sos_ptr ? ber -> ber_sos_ptr - buf : 0 ;
 buf = ( char * ) ber_memrealloc_x ( buf , total , ber -> ber_memctx ) ;
 if ( buf == NULL ) {
 return ( - 1 ) ;
 }
 ber -> ber_buf = buf ;
 ber -> ber_end = buf + total ;
 ber -> ber_ptr = buf + offset ;
 if ( sos_offset ) ber -> ber_sos_ptr = buf + sos_offset ;
 return ( 0 ) ;
 }