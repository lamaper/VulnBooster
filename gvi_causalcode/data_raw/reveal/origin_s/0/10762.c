void vp8cx_frame_init_quantizer ( VP8_COMP * cpi ) {
 cpi -> mb . zbin_mode_boost = 0 ;
 vp8cx_mb_init_quantizer ( cpi , & cpi -> mb , 0 ) ;
 }