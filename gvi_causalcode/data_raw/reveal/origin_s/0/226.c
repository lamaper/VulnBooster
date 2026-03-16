static void upsample_5_4 ( float * out , const float * in , int o_size ) {
 const float * in0 = in - UPS_FIR_SIZE + 1 ;
 int i , j , k ;
 int int_part = 0 , frac_part ;
 i = 0 ;
 for ( j = 0 ;
 j < o_size / 5 ;
 j ++ ) {
 out [ i ] = in [ int_part ] ;
 frac_part = 4 ;
 i ++ ;
 for ( k = 1 ;
 k < 5 ;
 k ++ ) {
 out [ i ] = avpriv_scalarproduct_float_c ( in0 + int_part , upsample_fir [ 4 - frac_part ] , UPS_MEM_SIZE ) ;
 int_part ++ ;
 frac_part -- ;
 i ++ ;
 }
 }
 }