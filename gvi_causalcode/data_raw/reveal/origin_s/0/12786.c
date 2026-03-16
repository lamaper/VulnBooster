BerElement * ber_dup ( BerElement * ber ) {
 BerElement * new ;
 assert ( ber != NULL ) ;
 assert ( LBER_VALID ( ber ) ) ;
 if ( ( new = ber_alloc_t ( ber -> ber_options ) ) == NULL ) {
 return NULL ;
 }
 * new = * ber ;
 assert ( LBER_VALID ( new ) ) ;
 return ( new ) ;
 }