BerElement * ber_init ( struct berval * bv ) {
 BerElement * ber ;
 assert ( bv != NULL ) ;
 if ( bv == NULL ) {
 return NULL ;
 }
 ber = ber_alloc_t ( 0 ) ;
 if ( ber == NULL ) {
 return NULL ;
 }
 if ( ( ( ber_len_t ) ber_write ( ber , bv -> bv_val , bv -> bv_len , 0 ) ) != bv -> bv_len ) {
 ber_free ( ber , 1 ) ;
 return NULL ;
 }
 ber_reset ( ber , 1 ) ;
 return ber ;
 }