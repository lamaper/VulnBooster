double vp9_convert_qindex_to_q ( int qindex , vpx_bit_depth_t bit_depth ) {

 case VPX_BITS_8 : return vp9_ac_quant ( qindex , 0 , bit_depth ) / 4.0 ;
 case VPX_BITS_10 : return vp9_ac_quant ( qindex , 0 , bit_depth ) / 16.0 ;
 case VPX_BITS_12 : return vp9_ac_quant ( qindex , 0 , bit_depth ) / 64.0 ;
 default : assert ( 0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12" ) ;
 return - 1.0 ;
 }

