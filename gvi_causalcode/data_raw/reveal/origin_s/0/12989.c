static void encode_frame ( struct stream_state * stream , struct VpxEncoderConfig * global , struct vpx_image * img , unsigned int frames_in ) {
 vpx_codec_pts_t frame_start , next_frame_start ;
 struct vpx_codec_enc_cfg * cfg = & stream -> config . cfg ;
 struct vpx_usec_timer timer ;
 frame_start = ( cfg -> g_timebase . den * ( int64_t ) ( frames_in - 1 ) * global -> framerate . den ) / cfg -> g_timebase . num / global -> framerate . num ;
 next_frame_start = ( cfg -> g_timebase . den * ( int64_t ) ( frames_in ) * global -> framerate . den ) / cfg -> g_timebase . num / global -> framerate . num ;

 if ( ( img -> fmt & VPX_IMG_FMT_HIGHBITDEPTH ) && ( img -> d_w != cfg -> g_w || img -> d_h != cfg -> g_h ) ) {
 if ( img -> fmt != VPX_IMG_FMT_I42016 ) {
 fprintf ( stderr , "%s can only scale 4:2:0 inputs\n" , exec_name ) ;
 exit ( EXIT_FAILURE ) ;
 }

 stream -> img = vpx_img_alloc ( NULL , VPX_IMG_FMT_I42016 , cfg -> g_w , cfg -> g_h , 16 ) ;
 }
 I420Scale_16 ( ( uint16 * ) img -> planes [ VPX_PLANE_Y ] , img -> stride [ VPX_PLANE_Y ] / 2 , ( uint16 * ) img -> planes [ VPX_PLANE_U ] , img -> stride [ VPX_PLANE_U ] / 2 , ( uint16 * ) img -> planes [ VPX_PLANE_V ] , img -> stride [ VPX_PLANE_V ] / 2 , img -> d_w , img -> d_h , ( uint16 * ) stream -> img -> planes [ VPX_PLANE_Y ] , stream -> img -> stride [ VPX_PLANE_Y ] / 2 , ( uint16 * ) stream -> img -> planes [ VPX_PLANE_U ] , stream -> img -> stride [ VPX_PLANE_U ] / 2 , ( uint16 * ) stream -> img -> planes [ VPX_PLANE_V ] , stream -> img -> stride [ VPX_PLANE_V ] / 2 , stream -> img -> d_w , stream -> img -> d_h , kFilterBox ) ;
 img = stream -> img ;

 ctx_exit_on_error ( & stream -> encoder , "Stream %d: Failed to encode frame.\n" "Scaling disabled in this configuration. \n" "To enable, configure with --enable-libyuv\n" , stream -> index ) ;

 }

 if ( img -> fmt != VPX_IMG_FMT_I420 && img -> fmt != VPX_IMG_FMT_YV12 ) {
 fprintf ( stderr , "%s can only scale 4:2:0 8bpp inputs\n" , exec_name ) ;
 exit ( EXIT_FAILURE ) ;
 }

 I420Scale ( img -> planes [ VPX_PLANE_Y ] , img -> stride [ VPX_PLANE_Y ] , img -> planes [ VPX_PLANE_U ] , img -> stride [ VPX_PLANE_U ] , img -> planes [ VPX_PLANE_V ] , img -> stride [ VPX_PLANE_V ] , img -> d_w , img -> d_h , stream -> img -> planes [ VPX_PLANE_Y ] , stream -> img -> stride [ VPX_PLANE_Y ] , stream -> img -> planes [ VPX_PLANE_U ] , stream -> img -> stride [ VPX_PLANE_U ] , stream -> img -> planes [ VPX_PLANE_V ] , stream -> img -> stride [ VPX_PLANE_V ] , stream -> img -> d_w , stream -> img -> d_h , kFilterBox ) ;
 img = stream -> img ;

 ctx_exit_on_error ( & stream -> encoder , "Stream %d: Failed to encode frame.\n" "Scaling disabled in this configuration. \n" "To enable, configure with --enable-libyuv\n" , stream -> index ) ;

 vpx_usec_timer_start ( & timer ) ;
 vpx_codec_encode ( & stream -> encoder , img , frame_start , ( unsigned long ) ( next_frame_start - frame_start ) , 0 , global -> deadline ) ;
 vpx_usec_timer_mark ( & timer ) ;
 stream -> cx_time += vpx_usec_timer_elapsed ( & timer ) ;
 ctx_exit_on_error ( & stream -> encoder , "Stream %d: Failed to encode frame" , stream -> index ) ;
 }