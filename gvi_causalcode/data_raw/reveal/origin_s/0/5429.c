int vp9_receive_raw_frame ( VP9_COMP * cpi , unsigned int frame_flags , YV12_BUFFER_CONFIG * sd , int64_t time_stamp , int64_t end_time ) {
 VP9_COMMON * cm = & cpi -> common ;
 struct vpx_usec_timer timer ;
 int res = 0 ;
 const int subsampling_x = sd -> uv_width < sd -> y_width ;
 const int subsampling_y = sd -> uv_height < sd -> y_height ;
 check_initial_width ( cpi , subsampling_x , subsampling_y ) ;
 vpx_usec_timer_start ( & timer ) ;
 if ( vp9_lookahead_push ( cpi -> lookahead , sd , time_stamp , end_time , frame_flags ) ) res = - 1 ;
 vpx_usec_timer_mark ( & timer ) ;
 cpi -> time_receive_data += vpx_usec_timer_elapsed ( & timer ) ;
 if ( ( cm -> profile == PROFILE_0 || cm -> profile == PROFILE_2 ) && ( subsampling_x != 1 || subsampling_y != 1 ) ) {
 vpx_internal_error ( & cm -> error , VPX_CODEC_INVALID_PARAM , "Non-4:2:0 color space requires profile 1 or 3" ) ;
 res = - 1 ;
 }
 if ( ( cm -> profile == PROFILE_1 || cm -> profile == PROFILE_3 ) && ( subsampling_x == 1 && subsampling_y == 1 ) ) {
 vpx_internal_error ( & cm -> error , VPX_CODEC_INVALID_PARAM , "4:2:0 color space requires profile 0 or 2" ) ;
 res = - 1 ;
 }
 return res ;
 }