int main ( int argc , char * argv [ ] ) {
 int frame_cnt = 0 ;
 FILE * infile = NULL ;
 VpxVideoWriter * writers [ kNumEncoders ] ;
 vpx_codec_ctx_t codec [ kNumEncoders ] ;
 vpx_codec_enc_cfg_t cfg [ kNumEncoders ] ;
 vpx_image_t raw [ kNumEncoders ] ;
 const VpxInterface * const encoder = get_vpx_encoder_by_name ( "vp8" ) ;
 const int arg_deadline = VPX_DL_REALTIME ;
 int i ;
 int width = 0 ;
 int height = 0 ;
 int frame_avail = 0 ;
 int got_data = 0 ;
 int show_psnr = 0 ;
 uint64_t psnr_sse_total [ kNumEncoders ] = {
 0 }
 ;
 uint64_t psnr_samples_total [ kNumEncoders ] = {
 0 }
 ;
 double psnr_totals [ kNumEncoders ] [ 4 ] = {
 {
 0 , 0 }
 }
 ;
 int psnr_count [ kNumEncoders ] = {
 0 }
 ;
 unsigned int target_bitrate [ kNumEncoders ] = {
 1000 , 500 , 100 }
 ;
 const int framerate = 30 ;
 vpx_rational_t dsf [ kNumEncoders ] = {
 {
 2 , 1 }
 , {
 2 , 1 }
 , {
 1 , 1 }
 }
 ;
 exec_name = argv [ 0 ] ;
 if ( ! encoder ) die ( "Unsupported codec." ) ;
 if ( argc != ( 5 + kNumEncoders ) ) die ( "Invalid number of input options." ) ;
 printf ( "Using %s\n" , vpx_codec_iface_name ( encoder -> codec_interface ( ) ) ) ;
 width = strtol ( argv [ 1 ] , NULL , 0 ) ;
 height = strtol ( argv [ 2 ] , NULL , 0 ) ;
 if ( width < 16 || width % 2 || height < 16 || height % 2 ) die ( "Invalid resolution: %ldx%ld" , width , height ) ;
 if ( ! ( infile = fopen ( argv [ 3 ] , "rb" ) ) ) die ( "Failed to open %s for reading" , argv [ 3 ] ) ;
 show_psnr = strtol ( argv [ kNumEncoders + 4 ] , NULL , 0 ) ;
 for ( i = 0 ;
 i < kNumEncoders ;
 ++ i ) {
 vpx_codec_err_t res = vpx_codec_enc_config_default ( encoder -> codec_interface ( ) , & cfg [ i ] , 0 ) ;
 if ( res != VPX_CODEC_OK ) {
 printf ( "Failed to get config: %s\n" , vpx_codec_err_to_string ( res ) ) ;
 return EXIT_FAILURE ;
 }
 }
 cfg [ 0 ] . g_w = width ;
 cfg [ 0 ] . g_h = height ;
 cfg [ 0 ] . g_threads = 1 ;
 cfg [ 0 ] . rc_dropframe_thresh = 30 ;
 cfg [ 0 ] . rc_end_usage = VPX_CBR ;
 cfg [ 0 ] . rc_resize_allowed = 0 ;
 cfg [ 0 ] . rc_min_quantizer = 4 ;
 cfg [ 0 ] . rc_max_quantizer = 56 ;
 cfg [ 0 ] . rc_undershoot_pct = 98 ;
 cfg [ 0 ] . rc_overshoot_pct = 100 ;
 cfg [ 0 ] . rc_buf_initial_sz = 500 ;
 cfg [ 0 ] . rc_buf_optimal_sz = 600 ;
 cfg [ 0 ] . rc_buf_sz = 1000 ;
 cfg [ 0 ] . g_error_resilient = 1 ;
 cfg [ 0 ] . g_lag_in_frames = 0 ;
 cfg [ 0 ] . kf_mode = VPX_KF_AUTO ;
 cfg [ 0 ] . kf_min_dist = 3000 ;
 cfg [ 0 ] . kf_max_dist = 3000 ;
 cfg [ 0 ] . rc_target_bitrate = target_bitrate [ 0 ] ;
 cfg [ 0 ] . g_timebase . num = 1 ;
 cfg [ 0 ] . g_timebase . den = framerate ;
 for ( i = 1 ;
 i < kNumEncoders ;
 ++ i ) {
 cfg [ i ] = cfg [ 0 ] ;
 cfg [ i ] . g_threads = 1 ;
 cfg [ i ] . rc_target_bitrate = target_bitrate [ i ] ;
 {
 unsigned int iw = cfg [ i - 1 ] . g_w * dsf [ i - 1 ] . den + dsf [ i - 1 ] . num - 1 ;
 unsigned int ih = cfg [ i - 1 ] . g_h * dsf [ i - 1 ] . den + dsf [ i - 1 ] . num - 1 ;
 cfg [ i ] . g_w = iw / dsf [ i - 1 ] . num ;
 cfg [ i ] . g_h = ih / dsf [ i - 1 ] . num ;
 }
 if ( ( cfg [ i ] . g_w ) % 2 ) cfg [ i ] . g_w ++ ;
 if ( ( cfg [ i ] . g_h ) % 2 ) cfg [ i ] . g_h ++ ;
 }
 for ( i = 0 ;
 i < kNumEncoders ;
 ++ i ) {
 VpxVideoInfo info = {
 encoder -> fourcc , cfg [ i ] . g_w , cfg [ i ] . g_h , {
 cfg [ i ] . g_timebase . num , cfg [ i ] . g_timebase . den }
 }
 ;
 if ( ! ( writers [ i ] = vpx_video_writer_open ( argv [ i + 4 ] , kContainerIVF , & info ) ) ) die ( "Failed to open %s for writing" , argv [ i + 4 ] ) ;
 }
 for ( i = 0 ;
 i < kNumEncoders ;
 ++ i ) if ( ! vpx_img_alloc ( & raw [ i ] , VPX_IMG_FMT_I420 , cfg [ i ] . g_w , cfg [ i ] . g_h , 32 ) ) die ( "Failed to allocate image" , cfg [ i ] . g_w , cfg [ i ] . g_h ) ;
 if ( vpx_codec_enc_init_multi ( & codec [ 0 ] , encoder -> codec_interface ( ) , & cfg [ 0 ] , kNumEncoders , show_psnr ? VPX_CODEC_USE_PSNR : 0 , & dsf [ 0 ] ) ) die_codec ( & codec [ 0 ] , "Failed to initialize encoder" ) ;
 for ( i = 0 ;
 i < kNumEncoders ;
 i ++ ) {
 if ( vpx_codec_control ( & codec [ i ] , VP8E_SET_CPUUSED , - 6 ) ) die_codec ( & codec [ i ] , "Failed to set cpu_used" ) ;
 if ( vpx_codec_control ( & codec [ i ] , VP8E_SET_STATIC_THRESHOLD , 1 ) ) die_codec ( & codec [ i ] , "Failed to set static threshold" ) ;
 if ( vpx_codec_control ( & codec [ 0 ] , VP8E_SET_NOISE_SENSITIVITY , i == 0 ) ) die_codec ( & codec [ 0 ] , "Failed to set noise_sensitivity" ) ;
 }
 frame_avail = 1 ;
 got_data = 0 ;
 while ( frame_avail || got_data ) {
 vpx_codec_iter_t iter [ kNumEncoders ] = {
 NULL }
 ;
 const vpx_codec_cx_pkt_t * pkt [ kNumEncoders ] ;
 frame_avail = vpx_img_read ( & raw [ 0 ] , infile ) ;
 if ( frame_avail ) {
 for ( i = 1 ;
 i < kNumEncoders ;
 ++ i ) {
 vpx_image_t * const prev = & raw [ i - 1 ] ;
 I420Scale ( prev -> planes [ VPX_PLANE_Y ] , prev -> stride [ VPX_PLANE_Y ] , prev -> planes [ VPX_PLANE_U ] , prev -> stride [ VPX_PLANE_U ] , prev -> planes [ VPX_PLANE_V ] , prev -> stride [ VPX_PLANE_V ] , prev -> d_w , prev -> d_h , raw [ i ] . planes [ VPX_PLANE_Y ] , raw [ i ] . stride [ VPX_PLANE_Y ] , raw [ i ] . planes [ VPX_PLANE_U ] , raw [ i ] . stride [ VPX_PLANE_U ] , raw [ i ] . planes [ VPX_PLANE_V ] , raw [ i ] . stride [ VPX_PLANE_V ] , raw [ i ] . d_w , raw [ i ] . d_h , 1 ) ;
 }
 }
 if ( vpx_codec_encode ( & codec [ 0 ] , frame_avail ? & raw [ 0 ] : NULL , frame_cnt , 1 , 0 , arg_deadline ) ) {
 die_codec ( & codec [ 0 ] , "Failed to encode frame" ) ;
 }
 for ( i = kNumEncoders - 1 ;
 i >= 0 ;
 i -- ) {
 got_data = 0 ;
 while ( ( pkt [ i ] = vpx_codec_get_cx_data ( & codec [ i ] , & iter [ i ] ) ) ) {
 got_data = 1 ;
 switch ( pkt [ i ] -> kind ) {
 case VPX_CODEC_CX_FRAME_PKT : vpx_video_writer_write_frame ( writers [ i ] , pkt [ i ] -> data . frame . buf , pkt [ i ] -> data . frame . sz , frame_cnt - 1 ) ;
 break ;
 case VPX_CODEC_PSNR_PKT : if ( show_psnr ) {
 int j ;
 psnr_sse_total [ i ] += pkt [ i ] -> data . psnr . sse [ 0 ] ;
 psnr_samples_total [ i ] += pkt [ i ] -> data . psnr . samples [ 0 ] ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) psnr_totals [ i ] [ j ] += pkt [ i ] -> data . psnr . psnr [ j ] ;
 psnr_count [ i ] ++ ;
 }
 break ;
 default : break ;
 }
 printf ( pkt [ i ] -> kind == VPX_CODEC_CX_FRAME_PKT && ( pkt [ i ] -> data . frame . flags & VPX_FRAME_IS_KEY ) ? "K" : "." ) ;
 fflush ( stdout ) ;
 }
 }
 frame_cnt ++ ;
 }
 printf ( "\n" ) ;
 fclose ( infile ) ;
 printf ( "Processed %d frames.\n" , frame_cnt - 1 ) ;
 for ( i = 0 ;
 i < kNumEncoders ;
 ++ i ) {
 if ( show_psnr && psnr_count [ i ] > 0 ) {
 int j ;
 double ovpsnr = sse_to_psnr ( psnr_samples_total [ i ] , 255.0 , psnr_sse_total [ i ] ) ;
 fprintf ( stderr , "\n ENC%d PSNR (Overall/Avg/Y/U/V)" , i ) ;
 fprintf ( stderr , " %.3lf" , ovpsnr ) ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) fprintf ( stderr , " %.3lf" , psnr_totals [ i ] [ j ] / psnr_count [ i ] ) ;
 }
 if ( vpx_codec_destroy ( & codec [ i ] ) ) die_codec ( & codec [ i ] , "Failed to destroy codec" ) ;
 vpx_img_free ( & raw [ i ] ) ;
 vpx_video_writer_close ( writers [ i ] ) ;
 }
 printf ( "\n" ) ;
 return EXIT_SUCCESS ;
 }