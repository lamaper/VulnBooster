void vp9_subtract_block_c ( int rows , int cols , int16_t * diff , ptrdiff_t diff_stride , const uint8_t * src , ptrdiff_t src_stride , const uint8_t * pred , ptrdiff_t pred_stride ) {
 int r , c ;
 for ( r = 0 ;
 r < rows ;
 r ++ ) {
 for ( c = 0 ;
 c < cols ;
 c ++ ) diff [ c ] = src [ c ] - pred [ c ] ;
 diff += diff_stride ;
 pred += pred_stride ;
 src += src_stride ;
 }
 }