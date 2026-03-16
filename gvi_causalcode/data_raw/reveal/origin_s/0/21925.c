unsigned int vp9_sub_pixel_avg_variance ## W ## x ## H ## _c ( const uint8_t * src , int src_stride , int xoffset , int yoffset , const uint8_t * dst , int dst_stride , unsigned int * sse , const uint8_t * second_pred ) {
 uint16_t fdata3 [ ( H + 1 ) * W ] ;
 uint8_t temp2 [ H * W ] ;
 DECLARE_ALIGNED_ARRAY ( 16 , uint8_t , temp3 , H * W ) ;
 var_filter_block2d_bil_first_pass ( src , fdata3 , src_stride , 1 , H + 1 , W , BILINEAR_FILTERS_2TAP ( xoffset ) ) ;
 var_filter_block2d_bil_second_pass ( fdata3 , temp2 , W , W , H , W , BILINEAR_FILTERS_2TAP ( yoffset ) ) ;
 vp9_comp_avg_pred ( temp3 , second_pred , W , H , temp2 , W ) ;
 return vp9_variance ## W ## x ## H ## _c ( temp3 , W , dst , dst_stride , sse ) ;
 \ }
 void vp9_get16x16var_c ( const uint8_t * src_ptr , int source_stride , const uint8_t * ref_ptr , int ref_stride , unsigned int * sse , int * sum ) {
 variance ( src_ptr , source_stride , ref_ptr , ref_stride , 16 , 16 , sse , sum ) ;
 }
 void vp9_get8x8var_c ( const uint8_t * src_ptr , int source_stride , const uint8_t * ref_ptr , int ref_stride , unsigned int * sse , int * sum ) {
 variance ( src_ptr , source_stride , ref_ptr , ref_stride , 8 , 8 , sse , sum ) ;
 }
 unsigned int vp9_mse16x16_c ( const uint8_t * src , int src_stride , const uint8_t * ref , int ref_stride , unsigned int * sse ) {
 int sum ;
 variance ( src , src_stride , ref , ref_stride , 16 , 16 , sse , & sum ) ;
 return * sse ;
 }
 unsigned int vp9_mse16x8_c ( const uint8_t * src , int src_stride , const uint8_t * ref , int ref_stride , unsigned int * sse ) {
 int sum ;
 variance ( src , src_stride , ref , ref_stride , 16 , 8 , sse , & sum ) ;
 return * sse ;
 }
 unsigned int vp9_mse8x16_c ( const uint8_t * src , int src_stride , const uint8_t * ref , int ref_stride , unsigned int * sse ) {
 int sum ;
 variance ( src , src_stride , ref , ref_stride , 8 , 16 , sse , & sum ) ;
 return * sse ;
 }
 unsigned int vp9_mse8x8_c ( const uint8_t * src , int src_stride , const uint8_t * ref , int ref_stride , unsigned int * sse ) {
 int sum ;
 variance ( src , src_stride , ref , ref_stride , 8 , 8 , sse , & sum ) ;
 return * sse ;
 }
 VAR ( 4 , 4 ) SUBPIX_VAR ( 4 , 4 ) SUBPIX_AVG_VAR ( 4 , 4 ) VAR ( 4 , 8 ) SUBPIX_VAR ( 4 , 8 ) SUBPIX_AVG_VAR ( 4 , 8 ) VAR ( 8 , 4 ) SUBPIX_VAR ( 8 , 4 ) SUBPIX_AVG_VAR ( 8 , 4 ) VAR ( 8 , 8 ) SUBPIX_VAR ( 8 , 8 ) SUBPIX_AVG_VAR ( 8 , 8 ) VAR ( 8 , 16 ) SUBPIX_VAR ( 8 , 16 ) SUBPIX_AVG_VAR ( 8 , 16 ) VAR ( 16 , 8 ) SUBPIX_VAR ( 16 , 8 ) SUBPIX_AVG_VAR ( 16 , 8 ) VAR ( 16 , 16 ) SUBPIX_VAR ( 16 , 16 ) SUBPIX_AVG_VAR ( 16 , 16 ) VAR ( 16 , 32 ) SUBPIX_VAR ( 16 , 32 ) SUBPIX_AVG_VAR ( 16 , 32 ) VAR ( 32 , 16 ) SUBPIX_VAR ( 32 , 16 ) SUBPIX_AVG_VAR ( 32 , 16 ) VAR ( 32 , 32 ) SUBPIX_VAR ( 32 , 32 ) SUBPIX_AVG_VAR ( 32 , 32 )