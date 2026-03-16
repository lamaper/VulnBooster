void vp9_build_inter_predictor ( const uint8_t * src , int src_stride , uint8_t * dst , int dst_stride , const MV * src_mv , const struct scale_factors * sf , int w , int h , int ref , const InterpKernel * kernel , enum mv_precision precision , int x , int y ) {
 const int is_q4 = precision == MV_PRECISION_Q4 ;
 const MV mv_q4 = {
 is_q4 ? src_mv -> row : src_mv -> row * 2 , is_q4 ? src_mv -> col : src_mv -> col * 2 }
 ;
 MV32 mv = vp9_scale_mv ( & mv_q4 , x , y , sf ) ;
 const int subpel_x = mv . col & SUBPEL_MASK ;
 const int subpel_y = mv . row & SUBPEL_MASK ;
 src += ( mv . row >> SUBPEL_BITS ) * src_stride + ( mv . col >> SUBPEL_BITS ) ;
 inter_predictor ( src , src_stride , dst , dst_stride , subpel_x , subpel_y , sf , w , h , ref , kernel , sf -> x_step_q4 , sf -> y_step_q4 ) ;
 }