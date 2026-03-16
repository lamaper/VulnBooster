picture_t * DecodeVideo ( decoder_t * p_dec , block_t * * pp_block ) {
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 AVCodecContext * p_context = p_sys -> p_context ;
 int b_drawpicture ;
 block_t * p_block ;
 if ( ! pp_block ) return NULL ;
 if ( ! p_context -> extradata_size && p_dec -> fmt_in . i_extra ) {
 ffmpeg_InitCodec ( p_dec ) ;
 if ( p_sys -> b_delayed_open ) {
 if ( ffmpeg_OpenCodec ( p_dec ) ) msg_Err ( p_dec , "cannot open codec (%s)" , p_sys -> psz_namecodec ) ;
 }
 }
 p_block = * pp_block ;
 if ( ! p_block && ! ( p_sys -> p_codec -> capabilities & CODEC_CAP_DELAY ) ) return NULL ;
 if ( p_sys -> b_delayed_open ) {
 if ( p_block ) block_Release ( p_block ) ;
 return NULL ;
 }
 if ( p_block ) {
 if ( p_block -> i_flags & ( BLOCK_FLAG_DISCONTINUITY | BLOCK_FLAG_CORRUPTED ) ) {
 p_sys -> i_pts = VLC_TS_INVALID ;
 p_sys -> i_late_frames = 0 ;
 post_mt ( p_sys ) ;
 if ( p_block -> i_flags & BLOCK_FLAG_DISCONTINUITY ) avcodec_flush_buffers ( p_context ) ;
 wait_mt ( p_sys ) ;
 block_Release ( p_block ) ;
 return NULL ;
 }
 if ( p_block -> i_flags & BLOCK_FLAG_PREROLL ) {
 p_sys -> i_late_frames = 0 ;
 }
 }
 if ( ! p_dec -> b_pace_control && ( p_sys -> i_late_frames > 0 ) && ( mdate ( ) - p_sys -> i_late_frames_start > INT64_C ( 5000000 ) ) ) {
 if ( p_sys -> i_pts > VLC_TS_INVALID ) {
 p_sys -> i_pts = VLC_TS_INVALID ;
 }
 if ( p_block ) block_Release ( p_block ) ;
 p_sys -> i_late_frames -- ;
 msg_Err ( p_dec , "more than 5 seconds of late video -> " "dropping frame (computer too slow ?)" ) ;
 return NULL ;
 }
 if ( ! p_dec -> b_pace_control && p_sys -> b_hurry_up && ( p_sys -> i_late_frames > 4 ) ) {
 b_drawpicture = 0 ;
 if ( p_sys -> i_late_frames < 12 ) {
 p_context -> skip_frame = ( p_sys -> i_skip_frame <= AVDISCARD_NONREF ) ? AVDISCARD_NONREF : p_sys -> i_skip_frame ;
 }
 else {
 p_sys -> i_late_frames -- ;
 if ( p_block ) block_Release ( p_block ) ;
 msg_Warn ( p_dec , "More than 4 late frames, dropping frame" ) ;
 return NULL ;
 }
 }
 else {
 if ( p_sys -> b_hurry_up ) p_context -> skip_frame = p_sys -> i_skip_frame ;
 if ( ! p_block || ! ( p_block -> i_flags & BLOCK_FLAG_PREROLL ) ) b_drawpicture = 1 ;
 else b_drawpicture = 0 ;
 }
 if ( p_context -> width <= 0 || p_context -> height <= 0 ) {
 if ( p_sys -> b_hurry_up ) p_context -> skip_frame = p_sys -> i_skip_frame ;
 }
 else if ( ! b_drawpicture ) {


 if ( p_block && p_block -> i_buffer > 0 ) {
 p_sys -> b_flush = ( p_block -> i_flags & BLOCK_FLAG_END_OF_SEQUENCE ) != 0 ;
 p_block = block_Realloc ( p_block , 0 , p_block -> i_buffer + FF_INPUT_BUFFER_PADDING_SIZE ) ;
 if ( ! p_block ) return NULL ;
 p_block -> i_buffer -= FF_INPUT_BUFFER_PADDING_SIZE ;
 * pp_block = p_block ;
 memset ( p_block -> p_buffer + p_block -> i_buffer , 0 , FF_INPUT_BUFFER_PADDING_SIZE ) ;
 }
 while ( ! p_block || p_block -> i_buffer > 0 || p_sys -> b_flush ) {
 int i_used , b_gotpicture ;
 picture_t * p_pic ;
 AVPacket pkt ;
 post_mt ( p_sys ) ;
 av_init_packet ( & pkt ) ;
 if ( p_block && p_block -> i_buffer > 0 ) {
 pkt . data = p_block -> p_buffer ;
 pkt . size = p_block -> i_buffer ;
 pkt . pts = p_block -> i_pts ;
 pkt . dts = p_block -> i_dts ;
 }
 else {
 pkt . data = NULL ;
 pkt . size = 0 ;
 }

 uint8_t * pal = av_packet_new_side_data ( & pkt , AV_PKT_DATA_PALETTE , AVPALETTE_SIZE ) ;
 if ( pal ) {
 memcpy ( pal , p_dec -> fmt_in . video . p_palette -> palette , AVPALETTE_SIZE ) ;
 p_sys -> palette_sent = true ;
 }
 }

 p_block -> i_pts = p_block -> i_dts = VLC_TS_INVALID ;
 }
 i_used = avcodec_decode_video2 ( p_context , p_sys -> p_ff_pic , & b_gotpicture , & pkt ) ;
 wait_mt ( p_sys ) ;
 if ( p_sys -> b_flush ) p_sys -> b_first_frame = true ;
 if ( p_block ) {
 if ( p_block -> i_buffer <= 0 ) p_sys -> b_flush = false ;
 if ( i_used < 0 ) {
 if ( b_drawpicture ) msg_Warn ( p_dec , "cannot decode one frame (%zu bytes)" , p_block -> i_buffer ) ;
 block_Release ( p_block ) ;
 return NULL ;
 }
 else if ( ( unsigned ) i_used > p_block -> i_buffer || p_context -> thread_count > 1 ) {
 i_used = p_block -> i_buffer ;
 }
 p_block -> i_buffer -= i_used ;
 p_block -> p_buffer += i_used ;
 }
 if ( ! b_gotpicture ) {
 if ( i_used == 0 ) break ;
 continue ;
 }

 video_palette_t * p_palette ;
 p_palette = p_dec -> fmt_out . video . p_palette = malloc ( sizeof ( video_palette_t ) ) ;
 if ( ! p_palette ) {
 if ( p_block ) block_Release ( p_block ) ;
 return NULL ;
 }
 static_assert ( sizeof ( p_palette -> palette ) == AVPALETTE_SIZE , "Palette size mismatch between vlc and libavutil" ) ;
 memcpy ( p_palette -> palette , p_sys -> p_ff_pic -> data [ 1 ] , AVPALETTE_SIZE ) ;
 p_palette -> i_entries = AVPALETTE_COUNT ;
 }

 p_sys -> b_has_b_frames = true ;
 }
 mtime_t i_pts = p_sys -> p_ff_pic -> pkt_pts ;
 if ( i_pts <= VLC_TS_INVALID ) i_pts = p_sys -> p_ff_pic -> pkt_dts ;
 if ( i_pts <= VLC_TS_INVALID ) i_pts = p_sys -> i_pts ;
 if ( i_pts > VLC_TS_INVALID ) p_sys -> i_pts = i_pts ;
 if ( p_sys -> i_pts > VLC_TS_INVALID ) {
 if ( p_dec -> fmt_in . video . i_frame_rate > 0 && p_dec -> fmt_in . video . i_frame_rate_base > 0 ) {
 p_sys -> i_pts += INT64_C ( 1000000 ) * ( 2 + p_sys -> p_ff_pic -> repeat_pict ) * p_dec -> fmt_in . video . i_frame_rate_base / ( 2 * p_dec -> fmt_in . video . i_frame_rate ) ;
 }
 else if ( p_context -> time_base . den > 0 ) {
 int i_tick = p_context -> ticks_per_frame ;
 if ( i_tick <= 0 ) i_tick = 1 ;
 p_sys -> i_pts += INT64_C ( 1000000 ) * ( 2 + p_sys -> p_ff_pic -> repeat_pict ) * i_tick * p_context -> time_base . num / ( 2 * p_context -> time_base . den ) ;
 }
 }
 mtime_t i_display_date = 0 ;
 if ( ! p_block || ! ( p_block -> i_flags & BLOCK_FLAG_PREROLL ) ) i_display_date = decoder_GetDisplayDate ( p_dec , i_pts ) ;
 if ( i_display_date > 0 && i_display_date <= mdate ( ) ) {
 p_sys -> i_late_frames ++ ;
 if ( p_sys -> i_late_frames == 1 ) p_sys -> i_late_frames_start = mdate ( ) ;
 }
 else {
 p_sys -> i_late_frames = 0 ;
 }
 if ( ! b_drawpicture || ( ! p_sys -> p_va && ! p_sys -> p_ff_pic -> linesize [ 0 ] ) ) continue ;
 if ( p_sys -> p_va != NULL || p_sys -> p_ff_pic -> opaque == NULL ) {
 p_pic = ffmpeg_NewPictBuf ( p_dec , p_context ) ;
 if ( ! p_pic ) {
 if ( p_block ) block_Release ( p_block ) ;
 return NULL ;
 }
 ffmpeg_CopyPicture ( p_dec , p_pic , p_sys -> p_ff_pic ) ;
 }
 else {
 p_pic = ( picture_t * ) p_sys -> p_ff_pic -> opaque ;
 decoder_LinkPicture ( p_dec , p_pic ) ;
 }
 if ( ! p_dec -> fmt_in . video . i_sar_num || ! p_dec -> fmt_in . video . i_sar_den ) {
 p_dec -> fmt_out . video . i_sar_num = p_context -> sample_aspect_ratio . num ;
 p_dec -> fmt_out . video . i_sar_den = p_context -> sample_aspect_ratio . den ;
 if ( ! p_dec -> fmt_out . video . i_sar_num || ! p_dec -> fmt_out . video . i_sar_den ) {
 p_dec -> fmt_out . video . i_sar_num = 1 ;
 p_dec -> fmt_out . video . i_sar_den = 1 ;
 }
 }
 if ( i_pts > VLC_TS_INVALID ) {
 p_pic -> date = i_pts ;
 if ( p_sys -> b_first_frame ) {
 p_sys -> b_first_frame = false ;
 p_pic -> b_force = true ;
 }
 p_pic -> i_nb_fields = 2 + p_sys -> p_ff_pic -> repeat_pict ;
 p_pic -> b_progressive = ! p_sys -> p_ff_pic -> interlaced_frame ;
 p_pic -> b_top_field_first = p_sys -> p_ff_pic -> top_field_first ;
 return p_pic ;
 }
 else {
 decoder_DeletePicture ( p_dec , p_pic ) ;
 }
 }
 if ( p_block ) block_Release ( p_block ) ;
 return NULL ;
 }