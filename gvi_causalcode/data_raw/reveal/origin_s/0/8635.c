void ff_MPV_frame_end ( MpegEncContext * s ) {
 int i ;
 if ( CONFIG_MPEG_XVMC_DECODER && s -> avctx -> xvmc_acceleration ) {
 ff_xvmc_field_end ( s ) ;
 }
 else if ( ( s -> er . error_count || s -> encoding ) && ! s -> avctx -> hwaccel && ! ( s -> avctx -> codec -> capabilities & CODEC_CAP_HWACCEL_VDPAU ) && s -> unrestricted_mv && s -> current_picture . reference && ! s -> intra_only && ! ( s -> flags & CODEC_FLAG_EMU_EDGE ) ) {
 const AVPixFmtDescriptor * desc = av_pix_fmt_desc_get ( s -> avctx -> pix_fmt ) ;
 int hshift = desc -> log2_chroma_w ;
 int vshift = desc -> log2_chroma_h ;
 s -> dsp . draw_edges ( s -> current_picture . f . data [ 0 ] , s -> linesize , s -> h_edge_pos , s -> v_edge_pos , EDGE_WIDTH , EDGE_WIDTH , EDGE_TOP | EDGE_BOTTOM ) ;
 s -> dsp . draw_edges ( s -> current_picture . f . data [ 1 ] , s -> uvlinesize , s -> h_edge_pos >> hshift , s -> v_edge_pos >> vshift , EDGE_WIDTH >> hshift , EDGE_WIDTH >> vshift , EDGE_TOP | EDGE_BOTTOM ) ;
 s -> dsp . draw_edges ( s -> current_picture . f . data [ 2 ] , s -> uvlinesize , s -> h_edge_pos >> hshift , s -> v_edge_pos >> vshift , EDGE_WIDTH >> hshift , EDGE_WIDTH >> vshift , EDGE_TOP | EDGE_BOTTOM ) ;
 }
 emms_c ( ) ;
 s -> last_pict_type = s -> pict_type ;
 s -> last_lambda_for [ s -> pict_type ] = s -> current_picture_ptr -> f . quality ;
 if ( s -> pict_type != AV_PICTURE_TYPE_B ) {
 s -> last_non_b_pict_type = s -> pict_type ;
 }

 i < MAX_PICTURE_COUNT ;
 i ++ ) {
 if ( s -> picture [ i ] . f . data [ 0 ] == s -> current_picture . f . data [ 0 ] ) {
 s -> picture [ i ] = s -> current_picture ;
 break ;
 }
 }
 assert ( i < MAX_PICTURE_COUNT ) ;

 for ( i = 0 ;
 i < MAX_PICTURE_COUNT ;
 i ++ ) {
 if ( ! s -> picture [ i ] . reference ) ff_mpeg_unref_picture ( s , & s -> picture [ i ] ) ;
 }
 }

 memset ( & s -> next_picture , 0 , sizeof ( Picture ) ) ;
 memset ( & s -> current_picture , 0 , sizeof ( Picture ) ) ;

 if ( s -> codec_id != AV_CODEC_ID_H264 && s -> current_picture . reference ) ff_thread_report_progress ( & s -> current_picture_ptr -> tf , INT_MAX , 0 ) ;
 }