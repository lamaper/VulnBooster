void vp9_free_internal_frame_buffers ( InternalFrameBufferList * list ) {
 int i ;
 assert ( list != NULL ) ;
 for ( i = 0 ;
 i < list -> num_internal_frame_buffers ;
 ++ i ) {
 vpx_free ( list -> int_fb [ i ] . data ) ;
 list -> int_fb [ i ] . data = NULL ;
 }
 vpx_free ( list -> int_fb ) ;
 list -> int_fb = NULL ;
 }