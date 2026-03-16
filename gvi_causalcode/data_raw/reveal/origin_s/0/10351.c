int vp8_set_internal_size ( VP8_COMP * cpi , VPX_SCALING horiz_mode , VPX_SCALING vert_mode ) {
 if ( horiz_mode <= ONETWO ) cpi -> common . horiz_scale = horiz_mode ;
 else return - 1 ;
 if ( vert_mode <= ONETWO ) cpi -> common . vert_scale = vert_mode ;
 else return - 1 ;
 return 0 ;
 }