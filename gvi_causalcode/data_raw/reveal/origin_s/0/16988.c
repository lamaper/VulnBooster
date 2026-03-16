int vp9_compute_rd_mult ( const VP9_COMP * cpi , int qindex ) {
 const int q = vp9_dc_quant ( qindex , 0 , cpi -> common . bit_depth ) ;

 switch ( cpi -> common . bit_depth ) {
 case VPX_BITS_8 : rdmult = 88 * q * q / 24 ;
 break ;
 case VPX_BITS_10 : rdmult = ROUND_POWER_OF_TWO ( 88 * q * q / 24 , 4 ) ;
 break ;
 case VPX_BITS_12 : rdmult = ROUND_POWER_OF_TWO ( 88 * q * q / 24 , 8 ) ;
 break ;
 default : assert ( 0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12" ) ;
 return - 1 ;
 }


 const GF_GROUP * const gf_group = & cpi -> twopass . gf_group ;
 const FRAME_UPDATE_TYPE frame_type = gf_group -> update_type [ gf_group -> index ] ;
 const int boost_index = MIN ( 15 , ( cpi -> rc . gfu_boost / 100 ) ) ;
 rdmult = ( rdmult * rd_frame_type_factor [ frame_type ] ) >> 7 ;
 rdmult += ( ( rdmult * rd_boost_factor [ boost_index ] ) >> 7 ) ;
 }
 return rdmult ;
 }