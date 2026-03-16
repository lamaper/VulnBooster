static void get_tile_buffers ( VP9Decoder * pbi , const uint8_t * data , const uint8_t * data_end , int tile_cols , int tile_rows , TileBuffer ( * tile_buffers ) [ 1 << 6 ] ) {
 int r , c ;
 for ( r = 0 ;
 r < tile_rows ;
 ++ r ) {
 for ( c = 0 ;
 c < tile_cols ;
 ++ c ) {
 const int is_last = ( r == tile_rows - 1 ) && ( c == tile_cols - 1 ) ;
 TileBuffer * const buf = & tile_buffers [ r ] [ c ] ;
 buf -> col = c ;
 get_tile_buffer ( data_end , is_last , & pbi -> common . error , & data , pbi -> decrypt_cb , pbi -> decrypt_state , buf ) ;
 }
 }
 }