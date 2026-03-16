void vp9_init_me_luts ( ) {
 init_me_luts_bd ( sad_per_bit16lut_8 , sad_per_bit4lut_8 , QINDEX_RANGE , VPX_BITS_8 ) ;

 init_me_luts_bd ( sad_per_bit16lut_12 , sad_per_bit4lut_12 , QINDEX_RANGE , VPX_BITS_12 ) ;
