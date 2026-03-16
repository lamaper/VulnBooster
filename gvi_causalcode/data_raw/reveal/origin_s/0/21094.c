unsigned int vp9_sad ## m ## x ## n ## _avg_c ( const uint8_t * src , int src_stride , const uint8_t * ref , int ref_stride , const uint8_t * second_pred ) {
 uint8_t comp_pred [ m * n ] ;
 vp9_comp_avg_pred ( comp_pred , second_pred , m , n , ref , ref_stride ) ;
 return sad ( src , src_stride , comp_pred , m , m , n ) ;
 \ }

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
 sadMxN ( 64 , 64 )