static void parse_global_config ( struct VpxEncoderConfig * global , char * * argv ) {
 char * * argi , * * argj ;
 struct arg arg ;
 memset ( global , 0 , sizeof ( * global ) ) ;
 global -> codec = get_vpx_encoder_by_index ( 0 ) ;
 global -> passes = 0 ;
 global -> color_type = I420 ;
 global -> deadline = VPX_DL_GOOD_QUALITY ;
 for ( argi = argj = argv ;
 ( * argj = * argi ) ;
 argi += arg . argv_step ) {
 arg . argv_step = 1 ;
 if ( arg_match ( & arg , & codecarg , argi ) ) {
 global -> codec = get_vpx_encoder_by_name ( arg . val ) ;
 if ( ! global -> codec ) die ( "Error: Unrecognized argument (%s) to --codec\n" , arg . val ) ;
 }
 else if ( arg_match ( & arg , & passes , argi ) ) {
 global -> passes = arg_parse_uint ( & arg ) ;
 if ( global -> passes < 1 || global -> passes > 2 ) die ( "Error: Invalid number of passes (%d)\n" , global -> passes ) ;
 }
 else if ( arg_match ( & arg , & pass_arg , argi ) ) {
 global -> pass = arg_parse_uint ( & arg ) ;
 if ( global -> pass < 1 || global -> pass > 2 ) die ( "Error: Invalid pass selected (%d)\n" , global -> pass ) ;
 }
 else if ( arg_match ( & arg , & usage , argi ) ) global -> usage = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & deadline , argi ) ) global -> deadline = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & best_dl , argi ) ) global -> deadline = VPX_DL_BEST_QUALITY ;
 else if ( arg_match ( & arg , & good_dl , argi ) ) global -> deadline = VPX_DL_GOOD_QUALITY ;
 else if ( arg_match ( & arg , & rt_dl , argi ) ) global -> deadline = VPX_DL_REALTIME ;
 else if ( arg_match ( & arg , & use_yv12 , argi ) ) global -> color_type = YV12 ;
 else if ( arg_match ( & arg , & use_i420 , argi ) ) global -> color_type = I420 ;
 else if ( arg_match ( & arg , & use_i422 , argi ) ) global -> color_type = I422 ;
 else if ( arg_match ( & arg , & use_i444 , argi ) ) global -> color_type = I444 ;
 else if ( arg_match ( & arg , & quietarg , argi ) ) global -> quiet = 1 ;
 else if ( arg_match ( & arg , & verbosearg , argi ) ) global -> verbose = 1 ;
 else if ( arg_match ( & arg , & limit , argi ) ) global -> limit = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & skip , argi ) ) global -> skip_frames = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & psnrarg , argi ) ) global -> show_psnr = 1 ;
 else if ( arg_match ( & arg , & recontest , argi ) ) global -> test_decode = arg_parse_enum_or_int ( & arg ) ;
 else if ( arg_match ( & arg , & framerate , argi ) ) {
 global -> framerate = arg_parse_rational ( & arg ) ;
 validate_positive_rational ( arg . name , & global -> framerate ) ;
 global -> have_framerate = 1 ;
 }
 else if ( arg_match ( & arg , & out_part , argi ) ) global -> out_part = 1 ;
 else if ( arg_match ( & arg , & debugmode , argi ) ) global -> debug = 1 ;
 else if ( arg_match ( & arg , & q_hist_n , argi ) ) global -> show_q_hist_buckets = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & rate_hist_n , argi ) ) global -> show_rate_hist_buckets = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & disable_warnings , argi ) ) global -> disable_warnings = 1 ;
 else if ( arg_match ( & arg , & disable_warning_prompt , argi ) ) global -> disable_warning_prompt = 1 ;
 else if ( arg_match ( & arg , & experimental_bitstream , argi ) ) global -> experimental_bitstream = 1 ;
 else argj ++ ;
 }
 if ( global -> pass ) {
 if ( global -> pass > global -> passes ) {
 warn ( "Assuming --pass=%d implies --passes=%d\n" , global -> pass , global -> pass ) ;
 global -> passes = global -> pass ;
 }
 }
 if ( global -> passes == 0 ) {



 if ( global -> deadline == VPX_DL_REALTIME && global -> passes > 1 ) {
 warn ( "Enforcing one-pass encoding in realtime mode\n" ) ;
 global -> passes = 1 ;
 }
 }