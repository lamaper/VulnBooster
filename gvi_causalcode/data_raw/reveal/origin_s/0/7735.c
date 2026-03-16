static int parse_stream_params ( struct VpxEncoderConfig * global , struct stream_state * stream , char * * argv ) {
 char * * argi , * * argj ;
 struct arg arg ;
 static const arg_def_t * * ctrl_args = no_args ;
 static const int * ctrl_args_map = NULL ;
 struct stream_config * config = & stream -> config ;
 int eos_mark_found = 0 ;



 else if ( strcmp ( global -> codec -> name , "vp8" ) == 0 ) {
 ctrl_args = vp8_args ;
 ctrl_args_map = vp8_arg_ctrl_map ;

 else if ( strcmp ( global -> codec -> name , "vp9" ) == 0 ) {
 ctrl_args = vp9_args ;
 ctrl_args_map = vp9_arg_ctrl_map ;

 for ( argi = argj = argv ;
 ( * argj = * argi ) ;
 argi += arg . argv_step ) {
 arg . argv_step = 1 ;
 if ( eos_mark_found ) {
 argj ++ ;
 continue ;
 }
 else if ( ! strcmp ( * argj , "--" ) ) {
 eos_mark_found = 1 ;
 continue ;
 }
 if ( 0 ) {
 }
 else if ( arg_match ( & arg , & outputfile , argi ) ) {
 config -> out_fn = arg . val ;
 }
 else if ( arg_match ( & arg , & fpf_name , argi ) ) {
 config -> stats_fn = arg . val ;

 else if ( arg_match ( & arg , & fpmbf_name , argi ) ) {
 config -> fpmb_stats_fn = arg . val ;

 else if ( arg_match ( & arg , & use_ivf , argi ) ) {
 config -> write_webm = 0 ;
 }
 else if ( arg_match ( & arg , & threads , argi ) ) {
 config -> cfg . g_threads = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & profile , argi ) ) {
 config -> cfg . g_profile = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & width , argi ) ) {
 config -> cfg . g_w = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & height , argi ) ) {
 config -> cfg . g_h = arg_parse_uint ( & arg ) ;

 else if ( arg_match ( & arg , & bitdeptharg , argi ) ) {
 config -> cfg . g_bit_depth = arg_parse_enum_or_int ( & arg ) ;
 }
 else if ( arg_match ( & arg , & inbitdeptharg , argi ) ) {
 config -> cfg . g_input_bit_depth = arg_parse_uint ( & arg ) ;

 else if ( arg_match ( & arg , & stereo_mode , argi ) ) {
 config -> stereo_fmt = arg_parse_enum_or_int ( & arg ) ;

 else if ( arg_match ( & arg , & timebase , argi ) ) {
 config -> cfg . g_timebase = arg_parse_rational ( & arg ) ;
 validate_positive_rational ( arg . name , & config -> cfg . g_timebase ) ;
 }
 else if ( arg_match ( & arg , & error_resilient , argi ) ) {
 config -> cfg . g_error_resilient = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & lag_in_frames , argi ) ) {
 config -> cfg . g_lag_in_frames = arg_parse_uint ( & arg ) ;
 if ( global -> deadline == VPX_DL_REALTIME && config -> cfg . g_lag_in_frames != 0 ) {
 warn ( "non-zero %s option ignored in realtime mode.\n" , arg . name ) ;
 config -> cfg . g_lag_in_frames = 0 ;
 }
 }
 else if ( arg_match ( & arg , & dropframe_thresh , argi ) ) {
 config -> cfg . rc_dropframe_thresh = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & resize_allowed , argi ) ) {
 config -> cfg . rc_resize_allowed = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & resize_width , argi ) ) {
 config -> cfg . rc_scaled_width = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & resize_height , argi ) ) {
 config -> cfg . rc_scaled_height = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & resize_up_thresh , argi ) ) {
 config -> cfg . rc_resize_up_thresh = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & resize_down_thresh , argi ) ) {
 config -> cfg . rc_resize_down_thresh = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & end_usage , argi ) ) {
 config -> cfg . rc_end_usage = arg_parse_enum_or_int ( & arg ) ;
 }
 else if ( arg_match ( & arg , & target_bitrate , argi ) ) {
 config -> cfg . rc_target_bitrate = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & min_quantizer , argi ) ) {
 config -> cfg . rc_min_quantizer = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & max_quantizer , argi ) ) {
 config -> cfg . rc_max_quantizer = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & undershoot_pct , argi ) ) {
 config -> cfg . rc_undershoot_pct = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & overshoot_pct , argi ) ) {
 config -> cfg . rc_overshoot_pct = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & buf_sz , argi ) ) {
 config -> cfg . rc_buf_sz = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & buf_initial_sz , argi ) ) {
 config -> cfg . rc_buf_initial_sz = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & buf_optimal_sz , argi ) ) {
 config -> cfg . rc_buf_optimal_sz = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & bias_pct , argi ) ) {
 config -> cfg . rc_2pass_vbr_bias_pct = arg_parse_uint ( & arg ) ;
 if ( global -> passes < 2 ) warn ( "option %s ignored in one-pass mode.\n" , arg . name ) ;
 }
 else if ( arg_match ( & arg , & minsection_pct , argi ) ) {
 config -> cfg . rc_2pass_vbr_minsection_pct = arg_parse_uint ( & arg ) ;
 if ( global -> passes < 2 ) warn ( "option %s ignored in one-pass mode.\n" , arg . name ) ;
 }
 else if ( arg_match ( & arg , & maxsection_pct , argi ) ) {
 config -> cfg . rc_2pass_vbr_maxsection_pct = arg_parse_uint ( & arg ) ;
 if ( global -> passes < 2 ) warn ( "option %s ignored in one-pass mode.\n" , arg . name ) ;
 }
 else if ( arg_match ( & arg , & kf_min_dist , argi ) ) {
 config -> cfg . kf_min_dist = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & kf_max_dist , argi ) ) {
 config -> cfg . kf_max_dist = arg_parse_uint ( & arg ) ;
 config -> have_kf_max_dist = 1 ;
 }
 else if ( arg_match ( & arg , & kf_disabled , argi ) ) {
 config -> cfg . kf_mode = VPX_KF_DISABLED ;

 else if ( arg_match ( & arg , & test16bitinternalarg , argi ) ) {
 if ( strcmp ( global -> codec -> name , "vp9" ) == 0 ) {
 test_16bit_internal = 1 ;
 }

 else {
 int i , match = 0 ;
 for ( i = 0 ;
 ctrl_args [ i ] ;
 i ++ ) {
 if ( arg_match ( & arg , ctrl_args [ i ] , argi ) ) {
 int j ;
 match = 1 ;
 for ( j = 0 ;
 j < config -> arg_ctrl_cnt ;
 j ++ ) if ( ctrl_args_map != NULL && config -> arg_ctrls [ j ] [ 0 ] == ctrl_args_map [ i ] ) break ;
 assert ( j < ( int ) ARG_CTRL_CNT_MAX ) ;
 if ( ctrl_args_map != NULL && j < ( int ) ARG_CTRL_CNT_MAX ) {
 config -> arg_ctrls [ j ] [ 0 ] = ctrl_args_map [ i ] ;
 config -> arg_ctrls [ j ] [ 1 ] = arg_parse_enum_or_int ( & arg ) ;
 if ( j == config -> arg_ctrl_cnt ) config -> arg_ctrl_cnt ++ ;
 }
 }
 }
 if ( ! match ) argj ++ ;
 }
 }

 config -> use_16bit_internal = test_16bit_internal | ( config -> cfg . g_profile > 1 ) ;
 }

 }