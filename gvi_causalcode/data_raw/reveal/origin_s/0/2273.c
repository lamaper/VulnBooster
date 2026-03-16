static vpx_codec_err_t encoder_encode ( vpx_codec_alg_priv_t * ctx , const vpx_image_t * img , vpx_codec_pts_t pts , unsigned long duration , vpx_enc_frame_flags_t flags , unsigned long deadline ) {
 vpx_codec_err_t res = VPX_CODEC_OK ;
 VP9_COMP * const cpi = ctx -> cpi ;
 const vpx_rational_t * const timebase = & ctx -> cfg . g_timebase ;
 if ( img != NULL ) {
 res = validate_img ( ctx , img ) ;
 if ( res == VPX_CODEC_OK && cpi != NULL && ctx -> cx_data == NULL ) {
 ctx -> cx_data_sz = ctx -> cfg . g_w * ctx -> cfg . g_h * get_image_bps ( img ) / 8 * ( cpi -> multi_arf_allowed ? 8 : 2 ) ;
 if ( ctx -> cx_data_sz < 4096 ) ctx -> cx_data_sz = 4096 ;
 ctx -> cx_data = ( unsigned char * ) malloc ( ctx -> cx_data_sz ) ;
 if ( ctx -> cx_data == NULL ) {
 return VPX_CODEC_MEM_ERROR ;
 }
 }
 }
 pick_quickcompress_mode ( ctx , duration , deadline ) ;
 vpx_codec_pkt_list_init ( & ctx -> pkt_list ) ;
 if ( ( ( flags & VP8_EFLAG_NO_UPD_GF ) && ( flags & VP8_EFLAG_FORCE_GF ) ) || ( ( flags & VP8_EFLAG_NO_UPD_ARF ) && ( flags & VP8_EFLAG_FORCE_ARF ) ) ) {
 ctx -> base . err_detail = "Conflicting flags." ;
 return VPX_CODEC_INVALID_PARAM ;
 }
 vp9_apply_encoding_flags ( cpi , flags ) ;
 if ( ctx -> cfg . kf_mode == VPX_KF_AUTO && ctx -> cfg . kf_min_dist == ctx -> cfg . kf_max_dist ) {
 if ( ++ ctx -> fixed_kf_cntr > ctx -> cfg . kf_min_dist ) {
 flags |= VPX_EFLAG_FORCE_KF ;
 ctx -> fixed_kf_cntr = 1 ;
 }
 }
 if ( res == VPX_CODEC_OK && cpi != NULL ) {
 unsigned int lib_flags = 0 ;
 YV12_BUFFER_CONFIG sd ;
 int64_t dst_time_stamp = timebase_units_to_ticks ( timebase , pts ) ;
 int64_t dst_end_time_stamp = timebase_units_to_ticks ( timebase , pts + duration ) ;
 size_t size , cx_data_sz ;
 unsigned char * cx_data ;
 if ( ctx -> base . init_flags & VPX_CODEC_USE_PSNR ) cpi -> b_calculate_psnr = 1 ;
 if ( img != NULL ) {
 res = image2yuvconfig ( img , & sd ) ;
 if ( vp9_receive_raw_frame ( cpi , flags , & sd , dst_time_stamp , dst_end_time_stamp ) ) {
 res = update_error_state ( ctx , & cpi -> common . error ) ;
 }
 }
 cx_data = ctx -> cx_data ;
 cx_data_sz = ctx -> cx_data_sz ;
 if ( ctx -> pending_cx_data ) {
 memmove ( cx_data , ctx -> pending_cx_data , ctx -> pending_cx_data_sz ) ;
 ctx -> pending_cx_data = cx_data ;
 cx_data += ctx -> pending_cx_data_sz ;
 cx_data_sz -= ctx -> pending_cx_data_sz ;
 if ( cx_data_sz < ctx -> cx_data_sz / 2 ) {
 ctx -> base . err_detail = "Compressed data buffer too small" ;
 return VPX_CODEC_ERROR ;
 }
 }
 while ( cx_data_sz >= ctx -> cx_data_sz / 2 && - 1 != vp9_get_compressed_data ( cpi , & lib_flags , & size , cx_data , & dst_time_stamp , & dst_end_time_stamp , ! img ) ) {
 if ( size ) {
 vpx_codec_cx_pkt_t pkt ;


 if ( ctx -> pending_cx_data == 0 ) ctx -> pending_cx_data = cx_data ;
 ctx -> pending_cx_data_sz += size ;
 ctx -> pending_frame_sizes [ ctx -> pending_frame_count ++ ] = size ;
 ctx -> pending_frame_magnitude |= size ;
 cx_data += size ;
 cx_data_sz -= size ;
 continue ;
 }
 pkt . kind = VPX_CODEC_CX_FRAME_PKT ;
 pkt . data . frame . pts = ticks_to_timebase_units ( timebase , dst_time_stamp ) ;
 pkt . data . frame . duration = ( unsigned long ) ticks_to_timebase_units ( timebase , dst_end_time_stamp - dst_time_stamp ) ;
 pkt . data . frame . flags = get_frame_pkt_flags ( cpi , lib_flags ) ;
 if ( ctx -> pending_cx_data ) {
 ctx -> pending_frame_sizes [ ctx -> pending_frame_count ++ ] = size ;
 ctx -> pending_frame_magnitude |= size ;
 ctx -> pending_cx_data_sz += size ;
 size += write_superframe_index ( ctx ) ;
 pkt . data . frame . buf = ctx -> pending_cx_data ;
 pkt . data . frame . sz = ctx -> pending_cx_data_sz ;
 ctx -> pending_cx_data = NULL ;
 ctx -> pending_cx_data_sz = 0 ;
 ctx -> pending_frame_count = 0 ;
 ctx -> pending_frame_magnitude = 0 ;
 }
 else {
 pkt . data . frame . buf = cx_data ;
 pkt . data . frame . sz = size ;
 }
 pkt . data . frame . partition_id = - 1 ;
 vpx_codec_pkt_list_add ( & ctx -> pkt_list . head , & pkt ) ;
 cx_data += size ;
 cx_data_sz -= size ;

 vpx_codec_cx_pkt_t pkt_sizes , pkt_psnr ;
 int i ;
 vp9_zero ( pkt_sizes ) ;
 vp9_zero ( pkt_psnr ) ;
 pkt_sizes . kind = VPX_CODEC_SPATIAL_SVC_LAYER_SIZES ;
 pkt_psnr . kind = VPX_CODEC_SPATIAL_SVC_LAYER_PSNR ;
 for ( i = 0 ;
 i < cpi -> svc . number_spatial_layers ;
 ++ i ) {
 LAYER_CONTEXT * lc = & cpi -> svc . layer_context [ i ] ;
 pkt_sizes . data . layer_sizes [ i ] = lc -> layer_size ;
 pkt_psnr . data . layer_psnr [ i ] = lc -> psnr_pkt ;
 lc -> layer_size = 0 ;
 }
 vpx_codec_pkt_list_add ( & ctx -> pkt_list . head , & pkt_sizes ) ;
 vpx_codec_pkt_list_add ( & ctx -> pkt_list . head , & pkt_psnr ) ;
 }

 }
 }
 return res ;
 }