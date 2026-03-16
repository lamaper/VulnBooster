int main ( int argc , const char * * argv ) {
 AppInput app_input = {
 0 }
 ;
 VpxVideoWriter * writer = NULL ;
 VpxVideoInfo info = {
 0 }
 ;
 vpx_codec_ctx_t codec ;
 vpx_codec_enc_cfg_t enc_cfg ;
 SvcContext svc_ctx ;
 uint32_t i ;
 uint32_t frame_cnt = 0 ;
 vpx_image_t raw ;
 vpx_codec_err_t res ;
 int pts = 0 ;
 int frame_duration = 1 ;
 FILE * infile = NULL ;
 int end_of_stream = 0 ;
 int frames_received = 0 ;
 memset ( & svc_ctx , 0 , sizeof ( svc_ctx ) ) ;
 svc_ctx . log_print = 1 ;
 exec_name = argv [ 0 ] ;
 parse_command_line ( argc , argv , & app_input , & svc_ctx , & enc_cfg ) ;
 if ( ! vpx_img_alloc ( & raw , VPX_IMG_FMT_I420 , enc_cfg . g_w , enc_cfg . g_h , 32 ) ) die ( "Failed to allocate image %dx%d\n" , enc_cfg . g_w , enc_cfg . g_h ) ;
 if ( ! ( infile = fopen ( app_input . input_filename , "rb" ) ) ) die ( "Failed to open %s for reading\n" , app_input . input_filename ) ;
 if ( vpx_svc_init ( & svc_ctx , & codec , vpx_codec_vp9_cx ( ) , & enc_cfg ) != VPX_CODEC_OK ) die ( "Failed to initialize encoder\n" ) ;
 info . codec_fourcc = VP9_FOURCC ;
 info . time_base . numerator = enc_cfg . g_timebase . num ;
 info . time_base . denominator = enc_cfg . g_timebase . den ;
 if ( ! ( app_input . passes == 2 && app_input . pass == 1 ) ) {
 writer = vpx_video_writer_open ( app_input . output_filename , kContainerIVF , & info ) ;
 if ( ! writer ) die ( "Failed to open %s for writing\n" , app_input . output_filename ) ;
 }
 for ( i = 0 ;
 i < app_input . frames_to_skip ;
 ++ i ) vpx_img_read ( & raw , infile ) ;
 while ( ! end_of_stream ) {
 vpx_codec_iter_t iter = NULL ;
 const vpx_codec_cx_pkt_t * cx_pkt ;
 if ( frame_cnt >= app_input . frames_to_code || ! vpx_img_read ( & raw , infile ) ) {
 end_of_stream = 1 ;
 }
 res = vpx_svc_encode ( & svc_ctx , & codec , ( end_of_stream ? NULL : & raw ) , pts , frame_duration , VPX_DL_GOOD_QUALITY ) ;
 printf ( "%s" , vpx_svc_get_message ( & svc_ctx ) ) ;
 if ( res != VPX_CODEC_OK ) {
 die_codec ( & codec , "Failed to encode frame" ) ;
 }
 while ( ( cx_pkt = vpx_codec_get_cx_data ( & codec , & iter ) ) != NULL ) {
 switch ( cx_pkt -> kind ) {
 case VPX_CODEC_CX_FRAME_PKT : {
 if ( cx_pkt -> data . frame . sz > 0 ) vpx_video_writer_write_frame ( writer , cx_pkt -> data . frame . buf , cx_pkt -> data . frame . sz , cx_pkt -> data . frame . pts ) ;
 printf ( "SVC frame: %d, kf: %d, size: %d, pts: %d\n" , frames_received , ! ! ( cx_pkt -> data . frame . flags & VPX_FRAME_IS_KEY ) , ( int ) cx_pkt -> data . frame . sz , ( int ) cx_pkt -> data . frame . pts ) ;
 ++ frames_received ;
 break ;
 }
 case VPX_CODEC_STATS_PKT : {
 stats_write ( & app_input . rc_stats , cx_pkt -> data . twopass_stats . buf , cx_pkt -> data . twopass_stats . sz ) ;
 break ;
 }
 default : {
 break ;
 }
 }
 }
 if ( ! end_of_stream ) {
 ++ frame_cnt ;
 pts += frame_duration ;
 }
 }
 printf ( "Processed %d frames\n" , frame_cnt ) ;
 fclose ( infile ) ;
 if ( vpx_codec_destroy ( & codec ) ) die_codec ( & codec , "Failed to destroy codec" ) ;
 if ( app_input . passes == 2 ) stats_close ( & app_input . rc_stats , 1 ) ;
 if ( writer ) {
 vpx_video_writer_close ( writer ) ;
 }
 vpx_img_free ( & raw ) ;
 printf ( "%s" , vpx_svc_dump_statistics ( & svc_ctx ) ) ;
 vpx_svc_release ( & svc_ctx ) ;
 return EXIT_SUCCESS ;
 }