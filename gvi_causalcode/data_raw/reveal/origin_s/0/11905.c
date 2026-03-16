int main_loop ( int argc , const char * * argv_ ) {
 vpx_codec_ctx_t decoder ;
 char * fn = NULL ;
 int i ;
 uint8_t * buf = NULL ;
 size_t bytes_in_buffer = 0 , buffer_size = 0 ;
 FILE * infile ;
 int frame_in = 0 , frame_out = 0 , flipuv = 0 , noblit = 0 ;
 int do_md5 = 0 , progress = 0 ;
 int stop_after = 0 , postproc = 0 , summary = 0 , quiet = 1 ;
 int arg_skip = 0 ;
 int ec_enabled = 0 ;
 int keep_going = 0 ;
 const VpxInterface * interface = NULL ;
 const VpxInterface * fourcc_interface = NULL ;
 uint64_t dx_time = 0 ;
 struct arg arg ;
 char * * argv , * * argi , * * argj ;
 int single_file ;
 int use_y4m = 1 ;
 int opt_yv12 = 0 ;
 int opt_i420 = 0 ;
 vpx_codec_dec_cfg_t cfg = {
 0 , 0 , 0 }
 ;


 0 }
 ;
 int vp8_dbg_color_ref_frame = 0 ;
 int vp8_dbg_color_mb_modes = 0 ;
 int vp8_dbg_color_b_modes = 0 ;
 int vp8_dbg_display_mv = 0 ;

 int dec_flags = 0 ;
 int do_scale = 0 ;
 vpx_image_t * scaled_img = NULL ;


 int num_external_frame_buffers = 0 ;
 struct ExternalFrameBufferList ext_fb_list = {
 0 , NULL }
 ;
 const char * outfile_pattern = NULL ;
 char outfile_name [ PATH_MAX ] = {
 0 }
 ;
 FILE * outfile = NULL ;
 MD5Context md5_ctx ;
 unsigned char md5_digest [ 16 ] ;
 struct VpxDecInputContext input = {
 NULL , NULL }
 ;
 struct VpxInputContext vpx_input_ctx ;

 memset ( & ( webm_ctx ) , 0 , sizeof ( webm_ctx ) ) ;
 input . webm_ctx = & webm_ctx ;

 exec_name = argv_ [ 0 ] ;
 argv = argv_dup ( argc - 1 , argv_ + 1 ) ;
 for ( argi = argj = argv ;
 ( * argj = * argi ) ;
 argi += arg . argv_step ) {
 memset ( & arg , 0 , sizeof ( arg ) ) ;
 arg . argv_step = 1 ;
 if ( arg_match ( & arg , & codecarg , argi ) ) {
 interface = get_vpx_decoder_by_name ( arg . val ) ;
 if ( ! interface ) die ( "Error: Unrecognized argument (%s) to --codec\n" , arg . val ) ;
 }
 else if ( arg_match ( & arg , & looparg , argi ) ) {
 }
 else if ( arg_match ( & arg , & outputfile , argi ) ) outfile_pattern = arg . val ;
 else if ( arg_match ( & arg , & use_yv12 , argi ) ) {
 use_y4m = 0 ;
 flipuv = 1 ;
 opt_yv12 = 1 ;


 else if ( arg_match ( & arg , & use_i420 , argi ) ) {
 use_y4m = 0 ;
 flipuv = 0 ;
 opt_i420 = 1 ;
 }
 else if ( arg_match ( & arg , & rawvideo , argi ) ) {
 use_y4m = 0 ;
 }
 else if ( arg_match ( & arg , & flipuvarg , argi ) ) flipuv = 1 ;
 else if ( arg_match ( & arg , & noblitarg , argi ) ) noblit = 1 ;
 else if ( arg_match ( & arg , & progressarg , argi ) ) progress = 1 ;
 else if ( arg_match ( & arg , & limitarg , argi ) ) stop_after = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & skiparg , argi ) ) arg_skip = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & postprocarg , argi ) ) postproc = 1 ;
 else if ( arg_match ( & arg , & md5arg , argi ) ) do_md5 = 1 ;
 else if ( arg_match ( & arg , & summaryarg , argi ) ) summary = 1 ;
 else if ( arg_match ( & arg , & threadsarg , argi ) ) cfg . threads = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & verbosearg , argi ) ) quiet = 0 ;
 else if ( arg_match ( & arg , & scalearg , argi ) ) do_scale = 1 ;
 else if ( arg_match ( & arg , & fb_arg , argi ) ) num_external_frame_buffers = arg_parse_uint ( & arg ) ;
 else if ( arg_match ( & arg , & continuearg , argi ) ) keep_going = 1 ;

 output_bit_depth = arg_parse_uint ( & arg ) ;
 }

 postproc = 1 ;
 vp8_pp_cfg . post_proc_flag |= VP8_ADDNOISE ;
 vp8_pp_cfg . noise_level = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & demacroblock_level , argi ) ) {
 postproc = 1 ;
 vp8_pp_cfg . post_proc_flag |= VP8_DEMACROBLOCK ;
 vp8_pp_cfg . deblocking_level = arg_parse_uint ( & arg ) ;
 }
 else if ( arg_match ( & arg , & deblock , argi ) ) {
 postproc = 1 ;
 vp8_pp_cfg . post_proc_flag |= VP8_DEBLOCK ;
 }
 else if ( arg_match ( & arg , & mfqe , argi ) ) {
 postproc = 1 ;
 vp8_pp_cfg . post_proc_flag |= VP8_MFQE ;
 }
 else if ( arg_match ( & arg , & pp_debug_info , argi ) ) {
 unsigned int level = arg_parse_uint ( & arg ) ;
 postproc = 1 ;
 vp8_pp_cfg . post_proc_flag &= ~ 0x7 ;
 if ( level ) vp8_pp_cfg . post_proc_flag |= level ;
 }
 else if ( arg_match ( & arg , & pp_disp_ref_frame , argi ) ) {
 unsigned int flags = arg_parse_int ( & arg ) ;
 if ( flags ) {
 postproc = 1 ;
 vp8_dbg_color_ref_frame = flags ;
 }
 }
 else if ( arg_match ( & arg , & pp_disp_mb_modes , argi ) ) {
 unsigned int flags = arg_parse_int ( & arg ) ;
 if ( flags ) {
 postproc = 1 ;
 vp8_dbg_color_mb_modes = flags ;
 }
 }
 else if ( arg_match ( & arg , & pp_disp_b_modes , argi ) ) {
 unsigned int flags = arg_parse_int ( & arg ) ;
 if ( flags ) {
 postproc = 1 ;
 vp8_dbg_color_b_modes = flags ;
 }
 }
 else if ( arg_match ( & arg , & pp_disp_mvs , argi ) ) {
 unsigned int flags = arg_parse_int ( & arg ) ;
 if ( flags ) {
 postproc = 1 ;
 vp8_dbg_display_mv = flags ;
 }
 }
 else if ( arg_match ( & arg , & error_concealment , argi ) ) {
 ec_enabled = 1 ;
 }

 }
 for ( argi = argv ;
 * argi ;
 argi ++ ) if ( argi [ 0 ] [ 0 ] == '-' && strlen ( argi [ 0 ] ) > 1 ) die ( "Error: Unrecognized option %s\n" , * argi ) ;
 fn = argv [ 0 ] ;
 if ( ! fn ) usage_exit ( ) ;
 infile = strcmp ( fn , "-" ) ? fopen ( fn , "rb" ) : set_binary_mode ( stdin ) ;
 if ( ! infile ) {
 fprintf ( stderr , "Failed to open file '%s'" , strcmp ( fn , "-" ) ? fn : "stdin" ) ;
 return EXIT_FAILURE ;
 }

 fprintf ( stderr , "Not dumping raw video to your terminal. Use '-o -' to " "override.\n" ) ;
 return EXIT_FAILURE ;
 }

 if ( file_is_ivf ( input . vpx_input_ctx ) ) input . vpx_input_ctx -> file_type = FILE_TYPE_IVF ;


 else {
 fprintf ( stderr , "Unrecognized input file type.\n" ) ;


 }
 outfile_pattern = outfile_pattern ? outfile_pattern : "-" ;
 single_file = is_single_file ( outfile_pattern ) ;
 if ( ! noblit && single_file ) {
 generate_filename ( outfile_pattern , outfile_name , PATH_MAX , vpx_input_ctx . width , vpx_input_ctx . height , 0 ) ;
 if ( do_md5 ) MD5Init ( & md5_ctx ) ;
 else outfile = open_outfile ( outfile_name ) ;
 }
 if ( use_y4m && ! noblit ) {
 if ( ! single_file ) {
 fprintf ( stderr , "YUV4MPEG2 not supported with output patterns," " try --i420 or --yv12.\n" ) ;
 return EXIT_FAILURE ;
 }

 if ( webm_guess_framerate ( input . webm_ctx , input . vpx_input_ctx ) ) {
 fprintf ( stderr , "Failed to guess framerate -- error parsing " "webm file?\n" ) ;
 return EXIT_FAILURE ;
 }
 }

 fourcc_interface = get_vpx_decoder_by_fourcc ( vpx_input_ctx . fourcc ) ;
 if ( interface && fourcc_interface && interface != fourcc_interface ) warn ( "Header indicates codec: %s\n" , fourcc_interface -> name ) ;
 else interface = fourcc_interface ;
 if ( ! interface ) interface = get_vpx_decoder_by_index ( 0 ) ;
 dec_flags = ( postproc ? VPX_CODEC_USE_POSTPROC : 0 ) | ( ec_enabled ? VPX_CODEC_USE_ERROR_CONCEALMENT : 0 ) ;
 if ( vpx_codec_dec_init ( & decoder , interface -> codec_interface ( ) , & cfg , dec_flags ) ) {
 fprintf ( stderr , "Failed to initialize decoder: %s\n" , vpx_codec_error ( & decoder ) ) ;
 return EXIT_FAILURE ;
 }
 if ( ! quiet ) fprintf ( stderr , "%s\n" , decoder . name ) ;

 fprintf ( stderr , "Failed to configure postproc: %s\n" , vpx_codec_error ( & decoder ) ) ;
 return EXIT_FAILURE ;
 }
 if ( vp8_dbg_color_ref_frame && vpx_codec_control ( & decoder , VP8_SET_DBG_COLOR_REF_FRAME , vp8_dbg_color_ref_frame ) ) {
 fprintf ( stderr , "Failed to configure reference block visualizer: %s\n" , vpx_codec_error ( & decoder ) ) ;
 return EXIT_FAILURE ;
 }
 if ( vp8_dbg_color_mb_modes && vpx_codec_control ( & decoder , VP8_SET_DBG_COLOR_MB_MODES , vp8_dbg_color_mb_modes ) ) {
 fprintf ( stderr , "Failed to configure macro block visualizer: %s\n" , vpx_codec_error ( & decoder ) ) ;
 return EXIT_FAILURE ;
 }
 if ( vp8_dbg_color_b_modes && vpx_codec_control ( & decoder , VP8_SET_DBG_COLOR_B_MODES , vp8_dbg_color_b_modes ) ) {
 fprintf ( stderr , "Failed to configure block visualizer: %s\n" , vpx_codec_error ( & decoder ) ) ;
 return EXIT_FAILURE ;
 }
 if ( vp8_dbg_display_mv && vpx_codec_control ( & decoder , VP8_SET_DBG_DISPLAY_MV , vp8_dbg_display_mv ) ) {
 fprintf ( stderr , "Failed to configure motion vector visualizer: %s\n" , vpx_codec_error ( & decoder ) ) ;
 return EXIT_FAILURE ;
 }

 while ( arg_skip ) {
 if ( read_frame ( & input , & buf , & bytes_in_buffer , & buffer_size ) ) break ;
 arg_skip -- ;
 }
 if ( num_external_frame_buffers > 0 ) {
 ext_fb_list . num_external_frame_buffers = num_external_frame_buffers ;
 ext_fb_list . ext_fb = ( struct ExternalFrameBuffer * ) calloc ( num_external_frame_buffers , sizeof ( * ext_fb_list . ext_fb ) ) ;
 if ( vpx_codec_set_frame_buffer_functions ( & decoder , get_vp9_frame_buffer , release_vp9_frame_buffer , & ext_fb_list ) ) {
 fprintf ( stderr , "Failed to configure external frame buffers: %s\n" , vpx_codec_error ( & decoder ) ) ;
 return EXIT_FAILURE ;
 }
 }
 frame_avail = 1 ;
 got_data = 0 ;
 while ( frame_avail || got_data ) {
 vpx_codec_iter_t iter = NULL ;
 vpx_image_t * img ;
 struct vpx_usec_timer timer ;
 int corrupted ;
 frame_avail = 0 ;
 if ( ! stop_after || frame_in < stop_after ) {
 if ( ! read_frame ( & input , & buf , & bytes_in_buffer , & buffer_size ) ) {
 frame_avail = 1 ;
 frame_in ++ ;
 vpx_usec_timer_start ( & timer ) ;
 if ( vpx_codec_decode ( & decoder , buf , ( unsigned int ) bytes_in_buffer , NULL , 0 ) ) {
 const char * detail = vpx_codec_error_detail ( & decoder ) ;
 warn ( "Failed to decode frame %d: %s" , frame_in , vpx_codec_error ( & decoder ) ) ;
 if ( detail ) warn ( "Additional information: %s" , detail ) ;
 if ( ! keep_going ) goto fail ;
 }
 vpx_usec_timer_mark ( & timer ) ;
 dx_time += vpx_usec_timer_elapsed ( & timer ) ;
 }
 }
 vpx_usec_timer_start ( & timer ) ;
 got_data = 0 ;
 if ( ( img = vpx_codec_get_frame ( & decoder , & iter ) ) ) {
 ++ frame_out ;
 got_data = 1 ;
 }
 vpx_usec_timer_mark ( & timer ) ;
 dx_time += ( unsigned int ) vpx_usec_timer_elapsed ( & timer ) ;
 if ( vpx_codec_control ( & decoder , VP8D_GET_FRAME_CORRUPTED , & corrupted ) ) {
 warn ( "Failed VP8_GET_FRAME_CORRUPTED: %s" , vpx_codec_error ( & decoder ) ) ;
 goto fail ;
 }
 frames_corrupted += corrupted ;
 if ( progress ) show_progress ( frame_in , frame_out , dx_time ) ;
 if ( ! noblit && img ) {
 const int PLANES_YUV [ ] = {
 VPX_PLANE_Y , VPX_PLANE_U , VPX_PLANE_V }
 ;
 const int PLANES_YVU [ ] = {
 VPX_PLANE_Y , VPX_PLANE_V , VPX_PLANE_U }
 ;
 const int * planes = flipuv ? PLANES_YVU : PLANES_YUV ;
 if ( do_scale ) {
 if ( frame_out == 1 ) {
 int display_width = vpx_input_ctx . width ;
 int display_height = vpx_input_ctx . height ;
 if ( ! display_width || ! display_height ) {
 int display_size [ 2 ] ;
 if ( vpx_codec_control ( & decoder , VP9D_GET_DISPLAY_SIZE , display_size ) ) {
 display_width = img -> d_w ;
 display_height = img -> d_h ;
 }
 else {
 display_width = display_size [ 0 ] ;
 display_height = display_size [ 1 ] ;
 }
 }
 scaled_img = vpx_img_alloc ( NULL , img -> fmt , display_width , display_height , 16 ) ;
 scaled_img -> bit_depth = img -> bit_depth ;
 }
 if ( img -> d_w != scaled_img -> d_w || img -> d_h != scaled_img -> d_h ) {

 img = scaled_img ;

 return EXIT_FAILURE ;

 }

 output_bit_depth = img -> bit_depth ;
 }
 if ( output_bit_depth != img -> bit_depth ) {
 if ( ! img_shifted ) {
 if ( output_bit_depth == 8 ) {
 img_shifted = vpx_img_alloc ( NULL , img -> fmt - VPX_IMG_FMT_HIGHBITDEPTH , img -> d_w , img -> d_h , 16 ) ;
 }
 else {
 img_shifted = vpx_img_alloc ( NULL , img -> fmt | VPX_IMG_FMT_HIGHBITDEPTH , img -> d_w , img -> d_h , 16 ) ;
 }
 img_shifted -> bit_depth = output_bit_depth ;
 }
 if ( output_bit_depth > img -> bit_depth ) {
 img_upshift ( img_shifted , img , output_bit_depth - img -> bit_depth ) ;
 }
 else {
 img_downshift ( img_shifted , img , img -> bit_depth - output_bit_depth ) ;
 }
 img = img_shifted ;
 }

 if ( use_y4m ) {
 char buf [ Y4M_BUFFER_SIZE ] = {
 0 }
 ;
 size_t len = 0 ;
 if ( frame_out == 1 ) {
 len = y4m_write_file_header ( buf , sizeof ( buf ) , vpx_input_ctx . width , vpx_input_ctx . height , & vpx_input_ctx . framerate , img -> fmt , img -> bit_depth ) ;
 if ( do_md5 ) {
 MD5Update ( & md5_ctx , ( md5byte * ) buf , ( unsigned int ) len ) ;
 }
 else {
 fputs ( buf , outfile ) ;
 }
 }
 len = y4m_write_frame_header ( buf , sizeof ( buf ) ) ;
 if ( do_md5 ) {
 MD5Update ( & md5_ctx , ( md5byte * ) buf , ( unsigned int ) len ) ;
 }
 else {
 fputs ( buf , outfile ) ;
 }
 }
 else {
 if ( frame_out == 1 ) {
 if ( opt_i420 ) {
 if ( img -> fmt != VPX_IMG_FMT_I420 && img -> fmt != VPX_IMG_FMT_I42016 ) {
 fprintf ( stderr , "Cannot produce i420 output for bit-stream.\n" ) ;
 goto fail ;
 }
 }
 if ( opt_yv12 ) {
 if ( ( img -> fmt != VPX_IMG_FMT_I420 && img -> fmt != VPX_IMG_FMT_YV12 ) || img -> bit_depth != 8 ) {
 fprintf ( stderr , "Cannot produce yv12 output for bit-stream.\n" ) ;
 goto fail ;
 }
 }
 }
 }
 if ( do_md5 ) {
 update_image_md5 ( img , planes , & md5_ctx ) ;
 }
 else {
 write_image_file ( img , planes , outfile ) ;
 }
 }
 else {
 generate_filename ( outfile_pattern , outfile_name , PATH_MAX , img -> d_w , img -> d_h , frame_in ) ;
 if ( do_md5 ) {
 MD5Init ( & md5_ctx ) ;
 update_image_md5 ( img , planes , & md5_ctx ) ;
 MD5Final ( md5_digest , & md5_ctx ) ;
 print_md5 ( md5_digest , outfile_name ) ;
 }
 else {
 outfile = open_outfile ( outfile_name ) ;
 write_image_file ( img , planes , outfile ) ;
 fclose ( outfile ) ;
 }
 }
 }
 if ( stop_after && frame_in >= stop_after ) break ;
 }
 if ( summary || progress ) {
 show_progress ( frame_in , frame_out , dx_time ) ;
 fprintf ( stderr , "\n" ) ;
 }
 if ( frames_corrupted ) fprintf ( stderr , "WARNING: %d frames corrupted.\n" , frames_corrupted ) ;
 fail : if ( vpx_codec_destroy ( & decoder ) ) {
 fprintf ( stderr , "Failed to destroy decoder: %s\n" , vpx_codec_error ( & decoder ) ) ;
 return EXIT_FAILURE ;
 }
 if ( ! noblit && single_file ) {
 if ( do_md5 ) {
 MD5Final ( md5_digest , & md5_ctx ) ;
 print_md5 ( md5_digest , outfile_name ) ;
 }
 else {
 fclose ( outfile ) ;
 }
 }


 if ( scaled_img ) vpx_img_free ( scaled_img ) ;


 i < ext_fb_list . num_external_frame_buffers ;
 ++ i ) {
 free ( ext_fb_list . ext_fb [ i ] . data ) ;
 }
 free ( ext_fb_list . ext_fb ) ;
 fclose ( infile ) ;
 free ( argv ) ;
 return frames_corrupted ? EXIT_FAILURE : EXIT_SUCCESS ;
 }