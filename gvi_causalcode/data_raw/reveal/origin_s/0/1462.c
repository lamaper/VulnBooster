void vp9_get8x8var_c ( const uint8_t * src_ptr , int source_stride , const uint8_t * ref_ptr , int ref_stride , unsigned int * sse , int * sum ) {
 variance ( src_ptr , source_stride , ref_ptr , ref_stride , 8 , 8 , sse , sum ) ;
 }