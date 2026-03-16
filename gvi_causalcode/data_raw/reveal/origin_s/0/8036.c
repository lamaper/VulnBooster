void vp9_sad ## m ## x ## n ## x ## k ## _c ( const uint8_t * src , int src_stride , const uint8_t * ref , int ref_stride , unsigned int * sads ) {
 int i ;
 for ( i = 0 ;
 i < k ;
 ++ i ) sads [ i ] = vp9_sad ## m ## x ## n ## _c ( src , src_stride , & ref [ i ] , ref_stride ) ;
 \ }

 int i ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) sads [ i ] = vp9_sad ## m ## x ## n ## _c ( src , src_stride , refs [ i ] , ref_stride ) ;
 \ }
 sadMxN ( 64 , 64 ) sadMxNxK ( 64 , 64 , 3 ) sadMxNxK ( 64 , 64 , 8 )