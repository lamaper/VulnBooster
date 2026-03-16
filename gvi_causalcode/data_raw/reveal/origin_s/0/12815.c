int ber_flatten2 ( BerElement * ber , struct berval * bv , int alloc ) {
 assert ( bv != NULL ) ;
 if ( bv == NULL ) {
 return - 1 ;
 }
 if ( ber == NULL ) {
 bv -> bv_val = NULL ;
 bv -> bv_len = 0 ;
 }
 else if ( ber -> ber_sos_ptr != NULL ) {
 return - 1 ;
 }
 else {
 ber_len_t len = ber_pvt_ber_write ( ber ) ;
 if ( alloc ) {
 bv -> bv_val = ( char * ) ber_memalloc_x ( len + 1 , ber -> ber_memctx ) ;
 if ( bv -> bv_val == NULL ) {
 return - 1 ;
 }
 AC_MEMCPY ( bv -> bv_val , ber -> ber_buf , len ) ;
 bv -> bv_val [ len ] = '\0' ;
 }
 else if ( ber -> ber_buf != NULL ) {
 bv -> bv_val = ber -> ber_buf ;
 bv -> bv_val [ len ] = '\0' ;
 }
 else {
 bv -> bv_val = "" ;
 }
 bv -> bv_len = len ;
 }
 return 0 ;
 }