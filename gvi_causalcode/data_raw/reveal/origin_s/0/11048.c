void ber_init2 ( BerElement * ber , struct berval * bv , int options ) {
 assert ( ber != NULL ) ;
 ( void ) memset ( ( char * ) ber , '\0' , sizeof ( BerElement ) ) ;
 ber -> ber_valid = LBER_VALID_BERELEMENT ;
 ber -> ber_tag = LBER_DEFAULT ;
 ber -> ber_options = ( char ) options ;
 ber -> ber_debug = ber_int_debug ;
 if ( bv != NULL ) {
 ber -> ber_buf = bv -> bv_val ;
 ber -> ber_ptr = ber -> ber_buf ;
 ber -> ber_end = ber -> ber_buf + bv -> bv_len ;
 }
 assert ( LBER_VALID ( ber ) ) ;
 }