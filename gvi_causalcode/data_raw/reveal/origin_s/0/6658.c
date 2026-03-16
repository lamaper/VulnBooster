static void scope_chunk_free ( void * key , void * data ) {
 ID2 * p1 , * p2 ;
 for ( p1 = data ;
 p1 ;
 p1 = p2 ) {
 p2 = p1 [ 0 ] . mval . mv_data ;
 ber_memfree_x ( p1 , NULL ) ;
 }
 }