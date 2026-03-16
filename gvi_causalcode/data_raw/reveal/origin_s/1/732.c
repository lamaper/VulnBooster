vpx_codec_err_t vpx_svc_encode ( SvcContext * svc_ctx , vpx_codec_ctx_t * codec_ctx , struct vpx_image * rawimg , vpx_codec_pts_t pts , int64_t duration , int deadline ) {
 vpx_codec_err_t res ;
 vpx_codec_iter_t iter ;
 const vpx_codec_cx_pkt_t * cx_pkt ;
 int layer_for_psnr = 0 ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || codec_ctx == NULL || si == NULL ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 svc_log_reset ( svc_ctx ) ;
 si -> rc_stats_buf_used = 0 ;
 si -> layers = svc_ctx -> spatial_layers ;
 if ( si -> encode_frame_count == 0 ) {
 si -> frame_within_gop = 0 ;
 }
 si -> is_keyframe = ( si -> frame_within_gop == 0 ) ;
 if ( rawimg != NULL ) {
 svc_log ( svc_ctx , SVC_LOG_DEBUG , "vpx_svc_encode layers: %d, frame_count: %d, " "frame_within_gop: %d\n" , si -> layers , si -> encode_frame_count , si -> frame_within_gop ) ;
 }
 if ( rawimg != NULL ) {
 for ( si -> layer = 0 ;
 si -> layer < si -> layers ;
 ++ si -> layer ) {
 set_svc_parameters ( svc_ctx , codec_ctx ) ;
 }
 }
 res = vpx_codec_encode ( codec_ctx , rawimg , pts , ( uint32_t ) duration , 0 , deadline ) ;
 if ( res != VPX_CODEC_OK ) {
 return res ;
 }
 iter = NULL ;
 while ( ( cx_pkt = vpx_codec_get_cx_data ( codec_ctx , & iter ) ) ) {
 switch ( cx_pkt -> kind ) {
 case VPX_CODEC_CX_FRAME_PKT : {
 fd_list_add ( & si -> frame_list , fd_create ( cx_pkt -> data . frame . buf , cx_pkt -> data . frame . sz , cx_pkt -> data . frame . flags ) ) ;
 svc_log ( svc_ctx , SVC_LOG_DEBUG , "SVC frame: %d, kf: %d, size: %d, " "pts: %d\n" , si -> frame_received , ( cx_pkt -> data . frame . flags & VPX_FRAME_IS_KEY ) ? 1 : 0 , ( int ) cx_pkt -> data . frame . sz , ( int ) cx_pkt -> data . frame . pts ) ;
 ++ si -> frame_received ;
 layer_for_psnr = 0 ;
 break ;
 }
 case VPX_CODEC_PSNR_PKT : {
 int i ;
 svc_log ( svc_ctx , SVC_LOG_DEBUG , "SVC frame: %d, layer: %d, PSNR(Total/Y/U/V): " "%2.3f %2.3f %2.3f %2.3f \n" , si -> frame_received , layer_for_psnr , cx_pkt -> data . psnr . psnr [ 0 ] , cx_pkt -> data . psnr . psnr [ 1 ] , cx_pkt -> data . psnr . psnr [ 2 ] , cx_pkt -> data . psnr . psnr [ 3 ] ) ;
 svc_log ( svc_ctx , SVC_LOG_DEBUG , "SVC frame: %d, layer: %d, SSE(Total/Y/U/V): " "%2.3f %2.3f %2.3f %2.3f \n" , si -> frame_received , layer_for_psnr , cx_pkt -> data . psnr . sse [ 0 ] , cx_pkt -> data . psnr . sse [ 1 ] , cx_pkt -> data . psnr . sse [ 2 ] , cx_pkt -> data . psnr . sse [ 3 ] ) ;
 for ( i = 0 ;
 i < COMPONENTS ;
 i ++ ) {
 si -> psnr_sum [ layer_for_psnr ] [ i ] += cx_pkt -> data . psnr . psnr [ i ] ;
 si -> sse_sum [ layer_for_psnr ] [ i ] += cx_pkt -> data . psnr . sse [ i ] ;
 }
 ++ layer_for_psnr ;
 break ;
 }
 case VPX_CODEC_STATS_PKT : {
 size_t new_size = si -> rc_stats_buf_used + cx_pkt -> data . twopass_stats . sz ;
 if ( new_size > si -> rc_stats_buf_size ) {
 char * p = ( char * ) realloc ( si -> rc_stats_buf , new_size ) ;
 if ( p == NULL ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "Error allocating stats buf\n" ) ;
 return VPX_CODEC_MEM_ERROR ;
 }
 si -> rc_stats_buf = p ;
 si -> rc_stats_buf_size = new_size ;
 }
 memcpy ( si -> rc_stats_buf + si -> rc_stats_buf_used , cx_pkt -> data . twopass_stats . buf , cx_pkt -> data . twopass_stats . sz ) ;
 si -> rc_stats_buf_used += cx_pkt -> data . twopass_stats . sz ;
 break ;
 }

 int i ;
 for ( i = 0 ;
 i < si -> layers ;
 ++ i ) si -> bytes_sum [ i ] += cx_pkt -> data . layer_sizes [ i ] ;
 break ;
 }

 break ;
 }
 }
 }
 if ( rawimg != NULL ) {
 ++ si -> frame_within_gop ;
 ++ si -> encode_frame_count ;
 }
 return VPX_CODEC_OK ;
 }