static inline void vc1_b_mc ( VC1Context * v , int dmv_x [ 2 ] , int dmv_y [ 2 ] , int direct , int mode ) {
 if ( v -> use_ic ) {
 v -> mv_mode2 = v -> mv_mode ;
 v -> mv_mode = MV_PMODE_INTENSITY_COMP ;
 }
 if ( direct ) {
 vc1_mc_1mv ( v , 0 ) ;
 vc1_interp_mc ( v ) ;
 if ( v -> use_ic ) v -> mv_mode = v -> mv_mode2 ;
 return ;
 }
 if ( mode == BMV_TYPE_INTERPOLATED ) {
 vc1_mc_1mv ( v , 0 ) ;
 vc1_interp_mc ( v ) ;
 if ( v -> use_ic ) v -> mv_mode = v -> mv_mode2 ;
 return ;
 }
 if ( v -> use_ic && ( mode == BMV_TYPE_BACKWARD ) ) v -> mv_mode = v -> mv_mode2 ;
 vc1_mc_1mv ( v , ( mode == BMV_TYPE_BACKWARD ) ) ;
 if ( v -> use_ic ) v -> mv_mode = v -> mv_mode2 ;
 }