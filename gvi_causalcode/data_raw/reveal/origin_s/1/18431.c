void vp9_initialize_me_consts ( VP9_COMP * cpi , int qindex ) {
 cpi -> mb . sadperbit16 = sad_per_bit16lut [ qindex ] ;
 cpi -> mb . sadperbit4 = sad_per_bit4lut [ qindex ] ;
 }