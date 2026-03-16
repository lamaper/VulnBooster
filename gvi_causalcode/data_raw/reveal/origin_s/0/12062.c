unsigned int vp9_mse16x16_c ( const uint8_t * src , int src_stride , const uint8_t * ref , int ref_stride , unsigned int * sse ) {
 int sum ;
 variance ( src , src_stride , ref , ref_stride , 16 , 16 , sse , & sum ) ;
 return * sse ;
 }