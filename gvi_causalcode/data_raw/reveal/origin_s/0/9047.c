int ber_flatten ( BerElement * ber , struct berval * * bvPtr ) {
 struct berval * bv ;
 int rc ;
 assert ( bvPtr != NULL ) ;
 if ( bvPtr == NULL ) {
 return - 1 ;
 }
 bv = ber_memalloc_x ( sizeof ( struct berval ) , ber -> ber_memctx ) ;
 if ( bv == NULL ) {
 return - 1 ;
 }
 rc = ber_flatten2 ( ber , bv , 1 ) ;
 if ( rc == - 1 ) {
 ber_memfree_x ( bv , ber -> ber_memctx ) ;
 }
 else {
 * bvPtr = bv ;
 }
 return rc ;
 }