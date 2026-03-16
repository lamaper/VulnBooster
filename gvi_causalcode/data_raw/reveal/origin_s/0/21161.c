static void img_buf_free ( void * memblk ) {
 if ( memblk ) {
 void * addr = ( void * ) ( ( ( size_t * ) memblk ) [ - 1 ] ) ;
 free ( addr ) ;
 }
 }