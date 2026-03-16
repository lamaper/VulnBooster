void vp9_sad ## m ## x ## n ## x4d_c ( const uint8_t * src , int src_stride , const uint8_t * const refs [ ] , int ref_stride , unsigned int * sads ) {
 int i ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) sads [ i ] = vp9_sad ## m ## x ## n ## _c ( src , src_stride , refs [ i ] , ref_stride ) ;
 \ }
 sadMxN ( 64 , 64 ) sadMxNxK ( 64 , 64 , 3 ) sadMxNxK ( 64 , 64 , 8 ) sadMxNx4D ( 64 , 64 ) sadMxN ( 64 , 32 ) sadMxNx4D ( 64 , 32 ) sadMxN ( 32 , 64 ) sadMxNx4D ( 32 , 64 ) sadMxN ( 32 , 32 ) sadMxNxK ( 32 , 32 , 3 ) sadMxNxK ( 32 , 32 , 8 ) sadMxNx4D ( 32 , 32 ) sadMxN ( 32 , 16 ) sadMxNx4D ( 32 , 16 ) sadMxN ( 16 , 32 ) sadMxNx4D ( 16 , 32 ) sadMxN ( 16 , 16 ) sadMxNxK ( 16 , 16 , 3 ) sadMxNxK ( 16 , 16 , 8 ) sadMxNx4D ( 16 , 16 ) sadMxN ( 16 , 8 ) sadMxNxK ( 16 , 8 , 3 ) sadMxNxK ( 16 , 8 , 8 ) sadMxNx4D ( 16 , 8 ) sadMxN ( 8 , 16 ) sadMxNxK ( 8 , 16 , 3 ) sadMxNxK ( 8 , 16 , 8 ) sadMxNx4D ( 8 , 16 ) sadMxN ( 8 , 8 ) sadMxNxK ( 8 , 8 , 3 ) sadMxNxK ( 8 , 8 , 8 ) sadMxNx4D ( 8 , 8 ) sadMxN ( 8 , 4 ) sadMxNxK ( 8 , 4 , 8 ) sadMxNx4D ( 8 , 4 ) sadMxN ( 4 , 8 ) sadMxNxK ( 4 , 8 , 8 ) sadMxNx4D ( 4 , 8 ) sadMxN ( 4 , 4 ) sadMxNxK ( 4 , 4 , 3 ) sadMxNxK ( 4 , 4 , 8 ) sadMxNx4D ( 4 , 4 )