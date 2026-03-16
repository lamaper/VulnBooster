static int compare_tile_buffers ( const void * a , const void * b ) {
 const TileBuffer * const buf1 = ( const TileBuffer * ) a ;
 const TileBuffer * const buf2 = ( const TileBuffer * ) b ;
 if ( buf1 -> size < buf2 -> size ) {
 return 1 ;
 }
 else if ( buf1 -> size == buf2 -> size ) {
 return 0 ;
 }
 else {
 return - 1 ;
 }
 }