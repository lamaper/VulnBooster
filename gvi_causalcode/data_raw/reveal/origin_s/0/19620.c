void vp8_subtract_b_c ( BLOCK * be , BLOCKD * bd , int pitch ) {
 unsigned char * src_ptr = ( * ( be -> base_src ) + be -> src ) ;
 short * diff_ptr = be -> src_diff ;
 unsigned char * pred_ptr = bd -> predictor ;
 int src_stride = be -> src_stride ;
 int r , c ;
 for ( r = 0 ;
 r < 4 ;
 r ++ ) {
 for ( c = 0 ;
 c < 4 ;
 c ++ ) {
 diff_ptr [ c ] = src_ptr [ c ] - pred_ptr [ c ] ;
 }
 diff_ptr += pitch ;
 pred_ptr += pitch ;
 src_ptr += src_stride ;
 }
 }