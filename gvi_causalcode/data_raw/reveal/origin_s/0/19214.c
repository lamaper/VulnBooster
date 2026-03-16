int vp9_set_internal_size ( VP9_COMP * cpi , VPX_SCALING horiz_mode , VPX_SCALING vert_mode ) {
 VP9_COMMON * cm = & cpi -> common ;
 int hr = 0 , hs = 0 , vr = 0 , vs = 0 ;
 if ( horiz_mode > ONETWO || vert_mode > ONETWO ) return - 1 ;
 Scale2Ratio ( horiz_mode , & hr , & hs ) ;
 Scale2Ratio ( vert_mode , & vr , & vs ) ;
 cm -> width = ( hs - 1 + cpi -> oxcf . width * hr ) / hs ;
 cm -> height = ( vs - 1 + cpi -> oxcf . height * vr ) / vs ;
 assert ( cm -> width <= cpi -> initial_width ) ;
 assert ( cm -> height <= cpi -> initial_height ) ;
 update_frame_size ( cpi ) ;
 return 0 ;
 }