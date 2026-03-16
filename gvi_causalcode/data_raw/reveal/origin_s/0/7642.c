static int is_background ( const VP9_COMP * cpi , const TileInfo * const tile , int mi_row , int mi_col ) {
 const int row8x8_remaining = tile -> mi_row_end - mi_row ;
 const int col8x8_remaining = tile -> mi_col_end - mi_col ;
 const int x = mi_col * MI_SIZE ;
 const int y = mi_row * MI_SIZE ;
 const int src_stride = cpi -> Source -> y_stride ;
 const uint8_t * const src = & cpi -> Source -> y_buffer [ y * src_stride + x ] ;
 const int pre_stride = cpi -> Last_Source -> y_stride ;
 const uint8_t * const pre = & cpi -> Last_Source -> y_buffer [ y * pre_stride + x ] ;
 int this_sad = 0 ;
 int threshold = 0 ;
 if ( row8x8_remaining >= MI_BLOCK_SIZE && col8x8_remaining >= MI_BLOCK_SIZE ) {
 this_sad = cpi -> fn_ptr [ BLOCK_64X64 ] . sdf ( src , src_stride , pre , pre_stride ) ;
 threshold = ( 1 << 12 ) ;
 }
 else {
 int r , c ;
 for ( r = 0 ;
 r < row8x8_remaining ;
 r += 2 ) for ( c = 0 ;
 c < col8x8_remaining ;
 c += 2 ) this_sad += cpi -> fn_ptr [ BLOCK_16X16 ] . sdf ( src , src_stride , pre , pre_stride ) ;
 threshold = ( row8x8_remaining * col8x8_remaining ) << 6 ;
 }
 return this_sad < 2 * threshold ;
 }