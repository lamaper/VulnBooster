void vp9_initialize_me_consts ( VP9_COMP * cpi , int qindex ) {

 case VPX_BITS_8 : cpi -> mb . sadperbit16 = sad_per_bit16lut_8 [ qindex ] ;
 cpi -> mb . sadperbit4 = sad_per_bit4lut_8 [ qindex ] ;
 break ;
 case VPX_BITS_10 : cpi -> mb . sadperbit16 = sad_per_bit16lut_10 [ qindex ] ;
 cpi -> mb . sadperbit4 = sad_per_bit4lut_10 [ qindex ] ;
 break ;
 case VPX_BITS_12 : cpi -> mb . sadperbit16 = sad_per_bit16lut_12 [ qindex ] ;
 cpi -> mb . sadperbit4 = sad_per_bit4lut_12 [ qindex ] ;
 break ;
 default : assert ( 0 && "bit_depth should be VPX_BITS_8, VPX_BITS_10 or VPX_BITS_12" ) ;
 }

 cpi -> mb . sadperbit4 = sad_per_bit4lut_8 [ qindex ] ;
