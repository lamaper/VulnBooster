static void parse_command_line ( int argc , const char * * argv_ , AppInput * app_input , SvcContext * svc_ctx , vpx_codec_enc_cfg_t * enc_cfg ) {
 struct arg arg = {
 0 }
 ;
 char * * argv = NULL ;
 char * * argi = NULL ;
 char * * argj = NULL ;
 vpx_codec_err_t res ;
 int passes = 0 ;
 int pass = 0 ;
 const char * fpf_file_name = NULL ;
 unsigned int min_bitrate = 0 ;
 unsigned int max_bitrate = 0 ;
 char string_options [ 1024 ] = {
 0 }
 ;
 svc_ctx -> log_level = SVC_LOG_DEBUG ;
 svc_ctx -> spatial_layers = default_spatial_layers ;
 svc_ctx -> temporal_layers = default_temporal_layers ;
 res = vpx_codec_enc_config_default ( vpx_codec_vp9_cx ( ) , enc_cfg , 0 ) ;
 if ( res ) {
 die ( "Failed to get config: %s\n" , vpx_codec_err_to_string ( res ) ) ;
 }
 enc_cfg -> g_w = default_width ;
 enc_cfg -> g_h = default_height ;
 enc_cfg -> g_timebase . num = default_timebase_num ;
 enc_cfg -> g_timebase . den = default_timebase_den ;
 enc_cfg -> rc_target_bitrate = default_bitrate ;
 enc_cfg -> kf_min_dist = default_kf_dist ;
 enc_cfg -> kf_max_dist = default_kf_dist ;
 enc_cfg -> rc_end_usage = VPX_CQ ;
 app_input -> frames_to_code = default_frames_to_code ;
 app_input -> frames_to_skip = default_frames_to_skip ;
 argv = argv_dup ( argc - 1 , argv_ + 1 ) ;
 for ( argi = argj = argv ;
 ( * argj = * argi ) ;
 argi += arg . argv_step ) {
 arg . argv_step = 1 ;
 if ( arg_match ( & arg , & frames_arg , argi ) ) {
 app_input -> frames_to_code = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & width_arg , argi ) ) {
 enc_cfg -> g_w = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & height_arg , argi ) ) {
 enc_cfg -> g_h = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & timebase_arg , argi ) ) {
 enc_cfg -> g_timebase = arg_parse_rational ( & arg ) ;
 }
 else if ( arg_match ( & arg , & bitrate_arg , argi ) ) {
 enc_cfg -> rc_target_bitrate = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & skip_frames_arg , argi ) ) {
 app_input -> frames_to_skip = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & spatial_layers_arg , argi ) ) {
 svc_ctx -> spatial_layers = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & temporal_layers_arg , argi ) ) {
 svc_ctx -> temporal_layers = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & kf_dist_arg , argi ) ) {
 enc_cfg -> kf_min_dist = arg_parse_uint ( & arg ) ;
 enc_cfg -> kf_max_dist = enc_cfg -> kf_min_dist ;
 }
 else if ( arg_match ( & arg , & scale_factors_arg , argi ) ) {
 snprintf ( string_options , 1024 , "%s scale-factors=%s" , string_options , arg . val ) ;
 }
 else if ( arg_match ( & arg , & passes_arg , argi ) ) {
 passes = arg_parse_uint ( & arg ) ;
 if ( passes < 1 || passes > 2 ) {
 die ( "Error: Invalid number of passes (%d)\n" , passes ) ;
 }
 }
 else if ( arg_match ( & arg , & pass_arg , argi ) ) {
 pass = arg_parse_uint ( & arg ) ;
 if ( pass < 1 || pass > 2 ) {
 die ( "Error: Invalid pass selected (%d)\n" , pass ) ;
 }
 }
 else if ( arg_match ( & arg , & fpf_name_arg , argi ) ) {
 fpf_file_name = arg . val ;
 }
 else if ( arg_match ( & arg , & min_q_arg , argi ) ) {
 snprintf ( string_options , 1024 , "%s min-quantizers=%s" , string_options , arg . val ) ;
 }
 else if ( arg_match ( & arg , & max_q_arg , argi ) ) {
 snprintf ( string_options , 1024 , "%s max-quantizers=%s" , string_options , arg . val ) ;
 }
 else if ( arg_match ( & arg , & min_bitrate_arg , argi ) ) {
 min_bitrate = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & max_bitrate_arg , argi ) ) {
 max_bitrate = arg_parse_uint ( & arg ) ;
 }
 else {
 ++ argj ;
 }
 }
 if ( strlen ( string_options ) > 0 ) vpx_svc_set_options ( svc_ctx , string_options + 1 ) ;
 if ( passes == 0 || passes == 1 ) {
 if ( pass ) {
 fprintf ( stderr , "pass is ignored since there's only one pass\n" ) ;
 }
 enc_cfg -> g_pass = VPX_RC_ONE_PASS ;
 }
 else {
 if ( pass == 0 ) {
 die ( "pass must be specified when passes is 2\n" ) ;
 }
 if ( fpf_file_name == NULL ) {
 die ( "fpf must be specified when passes is 2\n" ) ;
 }
 if ( pass == 1 ) {
 enc_cfg -> g_pass = VPX_RC_FIRST_PASS ;
 if ( ! stats_open_file ( & app_input -> rc_stats , fpf_file_name , 0 ) ) {
 fatal ( "Failed to open statistics store" ) ;
 }
 }
 else {
 enc_cfg -> g_pass = VPX_RC_LAST_PASS ;
 if ( ! stats_open_file ( & app_input -> rc_stats , fpf_file_name , 1 ) ) {
 fatal ( "Failed to open statistics store" ) ;
 }
 enc_cfg -> rc_twopass_stats_in = stats_get ( & app_input -> rc_stats ) ;
 }
 app_input -> passes = passes ;
 app_input -> pass = pass ;
 }
 if ( enc_cfg -> rc_target_bitrate > 0 ) {
 if ( min_bitrate > 0 ) {
 enc_cfg -> rc_2pass_vbr_minsection_pct = min_bitrate * 100 / enc_cfg -> rc_target_bitrate ;
 }
 if ( max_bitrate > 0 ) {
 enc_cfg -> rc_2pass_vbr_maxsection_pct = max_bitrate * 100 / enc_cfg -> rc_target_bitrate ;
 }
 }
 for ( argi = argv ;
 * argi ;
 ++ argi ) if ( argi [ 0 ] [ 0 ] == '-' && strlen ( argi [ 0 ] ) > 1 ) die ( "Error: Unrecognized option %s\n" , * argi ) ;
 if ( argv [ 0 ] == NULL || argv [ 1 ] == 0 ) {
 usage_exit ( ) ;
 }
 app_input -> input_filename = argv [ 0 ] ;
 app_input -> output_filename = argv [ 1 ] ;
 free ( argv ) ;
 if ( enc_cfg -> g_w < 16 || enc_cfg -> g_w % 2 || enc_cfg -> g_h < 16 || enc_cfg -> g_h % 2 ) die ( "Invalid resolution: %d x %d\n" , enc_cfg -> g_w , enc_cfg -> g_h ) ;
 printf ( "Codec %s\nframes: %d, skip: %d\n" "layers: %d\n" "width %d, height: %d,\n" "num: %d, den: %d, bitrate: %d,\n" "gop size: %d\n" , vpx_codec_iface_name ( vpx_codec_vp9_cx ( ) ) , app_input -> frames_to_code , app_input -> frames_to_skip , svc_ctx -> spatial_layers , enc_cfg -> g_w , enc_cfg -> g_h , enc_cfg -> g_timebase . num , enc_cfg -> g_timebase . den , enc_cfg -> rc_target_bitrate , enc_cfg -> kf_max_dist ) ;
 }