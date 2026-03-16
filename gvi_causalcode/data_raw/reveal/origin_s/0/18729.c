void vp9_model_rd_from_var_lapndz ( unsigned int var , unsigned int n , unsigned int qstep , int * rate , int64_t * dist ) {
 if ( var == 0 ) {
 * rate = 0 ;
 * dist = 0 ;
 }
 else {
 int d_q10 , r_q10 ;
 static const uint32_t MAX_XSQ_Q10 = 245727 ;
 const uint64_t xsq_q10_64 = ( ( ( ( uint64_t ) qstep * qstep * n ) << 10 ) + ( var >> 1 ) ) / var ;
 const int xsq_q10 = ( int ) MIN ( xsq_q10_64 , MAX_XSQ_Q10 ) ;
 model_rd_norm ( xsq_q10 , & r_q10 , & d_q10 ) ;
 * rate = ( n * r_q10 + 2 ) >> 2 ;
 * dist = ( var * ( int64_t ) d_q10 + 512 ) >> 10 ;
 }
 }