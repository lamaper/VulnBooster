int main ( int argc , const char * * argv_ ) {
 int pass ;
 vpx_image_t raw ;

 int allocated_raw_shift = 0 ;
 int use_16bit_internal = 0 ;
 int input_shift = 0 ;

 struct VpxInputContext input ;
 struct VpxEncoderConfig global ;
 struct stream_state * streams = NULL ;
 char * * argv , * * argi ;
 uint64_t cx_time = 0 ;
 int stream_cnt = 0 ;
 int res = 0 ;
 memset ( & input , 0 , sizeof ( input ) ) ;
 exec_name = argv_ [ 0 ] ;
 if ( argc < 3 ) usage_exit ( ) ;
 input . framerate . numerator = 30 ;
 input . framerate . denominator = 1 ;
 input . only_i420 = 1 ;
 input . bit_depth = 0 ;
 argv = argv_dup ( argc - 1 , argv_ + 1 ) ;
 parse_global_config ( & global , argv ) ;
 switch ( global . color_type ) {
 case I420 : input . fmt = VPX_IMG_FMT_I420 ;
 break ;
 case I422 : input . fmt = VPX_IMG_FMT_I422 ;
 break ;
 case I444 : input . fmt = VPX_IMG_FMT_I444 ;
 break ;
 case YV12 : input . fmt = VPX_IMG_FMT_YV12 ;
 break ;
 }
 {
 struct stream_state * stream = NULL ;
 do {
 stream = new_stream ( & global , stream ) ;
 stream_cnt ++ ;
 if ( ! streams ) streams = stream ;
 }
 while ( parse_stream_params ( & global , stream , argv ) ) ;
 }
 for ( argi = argv ;
 * argi ;
 argi ++ ) if ( argi [ 0 ] [ 0 ] == '-' && argi [ 0 ] [ 1 ] ) die ( "Error: Unrecognized option %s\n" , * argi ) ;
 FOREACH_STREAM ( check_encoder_config ( global . disable_warning_prompt , & global , & stream -> config . cfg ) ;
 ) ;
 input . filename = argv [ 0 ] ;
 if ( ! input . filename ) usage_exit ( ) ;
 if ( global . codec -> fourcc == VP9_FOURCC ) input . only_i420 = 0 ;
 for ( pass = global . pass ? global . pass - 1 : 0 ;
 pass < global . passes ;
 pass ++ ) {
 int frames_in = 0 , seen_frames = 0 ;
 int64_t estimated_time_left = - 1 ;
 int64_t average_rate = - 1 ;
 int64_t lagged_count = 0 ;
 open_input_file ( & input ) ;
 if ( ! input . width || ! input . height ) FOREACH_STREAM ( {
 if ( stream -> config . cfg . g_w && stream -> config . cfg . g_h ) {
 input . width = stream -> config . cfg . g_w ;
 input . height = stream -> config . cfg . g_h ;
 break ;
 }
 }
 ) ;
 if ( ! input . width || ! input . height ) fatal ( "Specify stream dimensions with --width (-w) " " and --height (-h)" ) ;
 if ( ! input . bit_depth ) {
 FOREACH_STREAM ( {
 if ( stream -> config . cfg . g_input_bit_depth ) input . bit_depth = stream -> config . cfg . g_input_bit_depth ;
 else input . bit_depth = stream -> config . cfg . g_input_bit_depth = ( int ) stream -> config . cfg . g_bit_depth ;
 }
 ) ;
 if ( input . bit_depth > 8 ) input . fmt |= VPX_IMG_FMT_HIGHBITDEPTH ;
 }
 else {
 FOREACH_STREAM ( {
 stream -> config . cfg . g_input_bit_depth = input . bit_depth ;
 }
 ) ;
 }
 FOREACH_STREAM ( set_stream_dimensions ( stream , input . width , input . height ) ) ;
 FOREACH_STREAM ( validate_stream_config ( stream , & global ) ) ;
 if ( global . pass && global . passes == 2 ) FOREACH_STREAM ( {
 if ( ! stream -> config . stats_fn ) die ( "Stream %d: Must specify --fpf when --pass=%d" " and --passes=2\n" , stream -> index , global . pass ) ;
 }
 ) ;

 stream -> config . write_webm = 0 ;
 warn ( "vpxenc was compiled without WebM container support." "Producing IVF output" ) ;
 }
 ) ;

 global . framerate . num = input . framerate . numerator ;
 global . framerate . den = input . framerate . denominator ;
 }
 FOREACH_STREAM ( set_default_kf_interval ( stream , & global ) ) ;
 if ( global . verbose && pass == 0 ) FOREACH_STREAM ( show_stream_config ( stream , & global , & input ) ) ;
 if ( pass == ( global . pass ? global . pass - 1 : 0 ) ) {
 if ( input . file_type == FILE_TYPE_Y4M ) memset ( & raw , 0 , sizeof ( raw ) ) ;
 else vpx_img_alloc ( & raw , input . fmt , input . width , input . height , 32 ) ;
 FOREACH_STREAM ( stream -> rate_hist = init_rate_histogram ( & stream -> config . cfg , & global . framerate ) ) ;
 }
 FOREACH_STREAM ( setup_pass ( stream , & global , pass ) ) ;
 FOREACH_STREAM ( open_output_file ( stream , & global ) ) ;
 FOREACH_STREAM ( initialize_encoder ( stream , & global ) ) ;

 FOREACH_STREAM ( {
 if ( stream -> config . use_16bit_internal ) {
 use_16bit_internal = 1 ;
 }
 if ( stream -> config . cfg . g_profile == 0 ) {
 input_shift = 0 ;
 }
 else {
 input_shift = ( int ) stream -> config . cfg . g_bit_depth - stream -> config . cfg . g_input_bit_depth ;
 }
 }
 ) ;
 }

 got_data = 0 ;
 while ( frame_avail || got_data ) {
 struct vpx_usec_timer timer ;
 if ( ! global . limit || frames_in < global . limit ) {
 frame_avail = read_frame ( & input , & raw ) ;
 if ( frame_avail ) frames_in ++ ;
 seen_frames = frames_in > global . skip_frames ? frames_in - global . skip_frames : 0 ;
 if ( ! global . quiet ) {
 float fps = usec_to_fps ( cx_time , seen_frames ) ;
 fprintf ( stderr , "\rPass %d/%d " , pass + 1 , global . passes ) ;
 if ( stream_cnt == 1 ) fprintf ( stderr , "frame %4d/%-4d %7" PRId64 "B " , frames_in , streams -> frames_out , ( int64_t ) streams -> nbytes ) ;
 else fprintf ( stderr , "frame %4d " , frames_in ) ;
 fprintf ( stderr , "%7" PRId64 " %s %.2f %s " , cx_time > 9999999 ? cx_time / 1000 : cx_time , cx_time > 9999999 ? "ms" : "us" , fps >= 1.0 ? fps : fps * 60 , fps >= 1.0 ? "fps" : "fpm" ) ;
 print_time ( "ETA" , estimated_time_left ) ;
 }
 }
 else frame_avail = 0 ;
 if ( frames_in > global . skip_frames ) {

 if ( input_shift || ( use_16bit_internal && input . bit_depth == 8 ) ) {
 assert ( use_16bit_internal ) ;
 if ( ! allocated_raw_shift ) {
 vpx_img_alloc ( & raw_shift , raw . fmt | VPX_IMG_FMT_HIGHBITDEPTH , input . width , input . height , 32 ) ;
 allocated_raw_shift = 1 ;
 }
 img_upshift ( & raw_shift , & raw , input_shift ) ;
 frame_to_encode = & raw_shift ;
 }
 else {
 frame_to_encode = & raw ;
 }
 vpx_usec_timer_start ( & timer ) ;
 if ( use_16bit_internal ) {
 assert ( frame_to_encode -> fmt & VPX_IMG_FMT_HIGHBITDEPTH ) ;
 FOREACH_STREAM ( {
 if ( stream -> config . use_16bit_internal ) encode_frame ( stream , & global , frame_avail ? frame_to_encode : NULL , frames_in ) ;
 else assert ( 0 ) ;
 }
 ) ;
 }
 else {
 assert ( ( frame_to_encode -> fmt & VPX_IMG_FMT_HIGHBITDEPTH ) == 0 ) ;
 FOREACH_STREAM ( encode_frame ( stream , & global , frame_avail ? frame_to_encode : NULL , frames_in ) ) ;
 }

 FOREACH_STREAM ( encode_frame ( stream , & global , frame_avail ? & raw : NULL , frames_in ) ) ;

 cx_time += vpx_usec_timer_elapsed ( & timer ) ;
 FOREACH_STREAM ( update_quantizer_histogram ( stream ) ) ;
 got_data = 0 ;
 FOREACH_STREAM ( get_cx_data ( stream , & global , & got_data ) ) ;
 if ( ! got_data && input . length && streams != NULL && ! streams -> frames_out ) {
 lagged_count = global . limit ? seen_frames : ftello ( input . file ) ;
 }
 else if ( input . length ) {
 int64_t remaining ;
 int64_t rate ;
 if ( global . limit ) {
 const int64_t frame_in_lagged = ( seen_frames - lagged_count ) * 1000 ;
 rate = cx_time ? frame_in_lagged * ( int64_t ) 1000000 / cx_time : 0 ;
 remaining = 1000 * ( global . limit - global . skip_frames - seen_frames + lagged_count ) ;
 }
 else {
 const int64_t input_pos = ftello ( input . file ) ;
 const int64_t input_pos_lagged = input_pos - lagged_count ;
 const int64_t limit = input . length ;
 rate = cx_time ? input_pos_lagged * ( int64_t ) 1000000 / cx_time : 0 ;
 remaining = limit - input_pos + lagged_count ;
 }
 average_rate = ( average_rate <= 0 ) ? rate : ( average_rate * 7 + rate ) / 8 ;
 estimated_time_left = average_rate ? remaining / average_rate : - 1 ;
 }
 if ( got_data && global . test_decode != TEST_DECODE_OFF ) FOREACH_STREAM ( test_decode ( stream , global . test_decode , global . codec ) ) ;
 }
 fflush ( stdout ) ;
 if ( ! global . quiet ) fprintf ( stderr , "\033[K" ) ;
 }
 if ( stream_cnt > 1 ) fprintf ( stderr , "\n" ) ;
 if ( ! global . quiet ) FOREACH_STREAM ( fprintf ( stderr , "\rPass %d/%d frame %4d/%-4d %7" PRId64 "B %7lub/f %7" PRId64 "b/s" " %7" PRId64 " %s (%.2f fps)\033[K\n" , pass + 1 , global . passes , frames_in , stream -> frames_out , ( int64_t ) stream -> nbytes , seen_frames ? ( unsigned long ) ( stream -> nbytes * 8 / seen_frames ) : 0 , seen_frames ? ( int64_t ) stream -> nbytes * 8 * ( int64_t ) global . framerate . num / global . framerate . den / seen_frames : 0 , stream -> cx_time > 9999999 ? stream -> cx_time / 1000 : stream -> cx_time , stream -> cx_time > 9999999 ? "ms" : "us" , usec_to_fps ( stream -> cx_time , seen_frames ) ) ;
 ) ;
 if ( global . show_psnr ) FOREACH_STREAM ( show_psnr ( stream ) ) ;
 FOREACH_STREAM ( vpx_codec_destroy ( & stream -> encoder ) ) ;
 if ( global . test_decode != TEST_DECODE_OFF ) {
 FOREACH_STREAM ( vpx_codec_destroy ( & stream -> decoder ) ) ;
 }
 close_input_file ( & input ) ;
 if ( global . test_decode == TEST_DECODE_FATAL ) {
 FOREACH_STREAM ( res |= stream -> mismatch_seen ) ;
 }
 FOREACH_STREAM ( close_output_file ( stream , global . codec -> fourcc ) ) ;
 FOREACH_STREAM ( stats_close ( & stream -> stats , global . passes - 1 ) ) ;


 }
 if ( global . show_q_hist_buckets ) FOREACH_STREAM ( show_q_histogram ( stream -> counts , global . show_q_hist_buckets ) ) ;
 if ( global . show_rate_hist_buckets ) FOREACH_STREAM ( show_rate_histogram ( stream -> rate_hist , & stream -> config . cfg , global . show_rate_hist_buckets ) ) ;
 FOREACH_STREAM ( destroy_rate_histogram ( stream -> rate_hist ) ) ;

 FILE * f = fopen ( "opsnr.stt" , "a" ) ;
 if ( stream -> mismatch_seen ) {
 fprintf ( f , "First mismatch occurred in frame %d\n" , stream -> mismatch_seen ) ;
 }
 else {
 fprintf ( f , "No mismatch detected in recon buffers\n" ) ;
 }
 fclose ( f ) ;
 }
 ) ;


 free ( argv ) ;
 free ( streams ) ;
 return res ? EXIT_FAILURE : EXIT_SUCCESS ;
 }