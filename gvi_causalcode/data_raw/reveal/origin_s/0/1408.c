static int get_qzbin_factor ( int q , vpx_bit_depth_t bit_depth ) {
 const int quant = vp9_dc_quant ( q , 0 , bit_depth ) ;

 case VPX_BITS_8 : return q == 0 ? 64 : ( quant < 148 ? 84 : 80 ) ;
 case VPX_BITS_10 : return q == 0 ? 64 : ( quant < 592 ? 84 : 80 ) ;
 case VPX_BITS_12 : return q == 0 ? 64 : ( quant < 2368 ? 84 : 80 ) ;
 default : assert ( 0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12" ) ;
 return - 1 ;
 }

 return q == 0 ? 64 : ( quant < 148 ? 84 : 80 ) ;
