BerElement * ber_alloc_t ( int options ) {
 BerElement * ber ;
 ber = ( BerElement * ) LBER_CALLOC ( 1 , sizeof ( BerElement ) ) ;
 if ( ber == NULL ) {
 return NULL ;
 }
 ber -> ber_valid = LBER_VALID_BERELEMENT ;
 ber -> ber_tag = LBER_DEFAULT ;
 ber -> ber_options = options ;
 ber -> ber_debug = ber_int_debug ;
 assert ( LBER_VALID ( ber ) ) ;
 return ber ;
 }