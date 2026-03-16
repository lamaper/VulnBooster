MV32 vp9_scale_mv ( const MV * mv , int x , int y , const struct scale_factors * sf ) {
 const int x_off_q4 = scaled_x ( x << SUBPEL_BITS , sf ) & SUBPEL_MASK ;
 const int y_off_q4 = scaled_y ( y << SUBPEL_BITS , sf ) & SUBPEL_MASK ;
 const MV32 res = {
 scaled_y ( mv -> row , sf ) + y_off_q4 , scaled_x ( mv -> col , sf ) + x_off_q4 }
 ;
 return res ;
 }