static int compute_rd_thresh_factor ( int qindex , vpx_bit_depth_t bit_depth ) {
 double q ;

 case VPX_BITS_8 : q = vp9_dc_quant ( qindex , 0 , VPX_BITS_8 ) / 4.0 ;
 break ;
 case VPX_BITS_10 : q = vp9_dc_quant ( qindex , 0 , VPX_BITS_10 ) / 16.0 ;
 break ;
 case VPX_BITS_12 : q = vp9_dc_quant ( qindex , 0 , VPX_BITS_12 ) / 64.0 ;
 break ;
 default : assert ( 0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12" ) ;
 return - 1 ;
 }

 q = vp9_dc_quant ( qindex , 0 , VPX_BITS_8 ) / 4.0 ;

 }