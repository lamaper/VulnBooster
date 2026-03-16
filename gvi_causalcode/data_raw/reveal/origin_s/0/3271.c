void vp9_frame_init_quantizer ( VP9_COMP * cpi ) {
 cpi -> zbin_mode_boost = 0 ;
 vp9_init_plane_quantizers ( cpi , & cpi -> mb ) ;
 }