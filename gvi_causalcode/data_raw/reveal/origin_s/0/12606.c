void vp9_get16x16var_c ( const uint8_t * src_ptr , int source_stride , const uint8_t * ref_ptr , int ref_stride , unsigned int * sse , int * sum ) {
 variance ( src_ptr , source_stride , ref_ptr , ref_stride , 16 , 16 , sse , sum ) ;
 }