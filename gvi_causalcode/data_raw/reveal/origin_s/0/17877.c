int ff_mpeg_update_thread_context ( AVCodecContext * dst , const AVCodecContext * src ) {
 int i , ret ;
 MpegEncContext * s = dst -> priv_data , * s1 = src -> priv_data ;
 if ( dst == src || ! s1 -> context_initialized ) return 0 ;
 if ( ! s -> context_initialized ) {
 memcpy ( s , s1 , sizeof ( MpegEncContext ) ) ;
 s -> avctx = dst ;
 s -> bitstream_buffer = NULL ;
 s -> bitstream_buffer_size = s -> allocated_bitstream_buffer_size = 0 ;
 ff_MPV_common_init ( s ) ;
 }
 if ( s -> height != s1 -> height || s -> width != s1 -> width || s -> context_reinit ) {
 int err ;
 s -> context_reinit = 0 ;
 s -> height = s1 -> height ;
 s -> width = s1 -> width ;
 if ( ( err = ff_MPV_common_frame_size_change ( s ) ) < 0 ) return err ;
 }
 s -> avctx -> coded_height = s1 -> avctx -> coded_height ;
 s -> avctx -> coded_width = s1 -> avctx -> coded_width ;
 s -> avctx -> width = s1 -> avctx -> width ;
 s -> avctx -> height = s1 -> avctx -> height ;
 s -> coded_picture_number = s1 -> coded_picture_number ;
 s -> picture_number = s1 -> picture_number ;
 s -> input_picture_number = s1 -> input_picture_number ;
 for ( i = 0 ;
 i < MAX_PICTURE_COUNT ;
 i ++ ) {
 ff_mpeg_unref_picture ( s , & s -> picture [ i ] ) ;
 if ( s1 -> picture [ i ] . f . data [ 0 ] && ( ret = ff_mpeg_ref_picture ( s , & s -> picture [ i ] , & s1 -> picture [ i ] ) ) < 0 ) return ret ;
 }

 ff_mpeg_unref_picture ( s , & s -> pic ) ;
 if ( s1 -> pic . f . data [ 0 ] ) ret = ff_mpeg_ref_picture ( s , & s -> pic , & s1 -> pic ) ;
 else ret = update_picture_tables ( & s -> pic , & s1 -> pic ) ;
 if ( ret < 0 ) return ret ;
 \ }
 while ( 0 ) UPDATE_PICTURE ( current_picture ) ;
 UPDATE_PICTURE ( last_picture ) ;
 UPDATE_PICTURE ( next_picture ) ;
 s -> last_picture_ptr = REBASE_PICTURE ( s1 -> last_picture_ptr , s , s1 ) ;
 s -> current_picture_ptr = REBASE_PICTURE ( s1 -> current_picture_ptr , s , s1 ) ;
 s -> next_picture_ptr = REBASE_PICTURE ( s1 -> next_picture_ptr , s , s1 ) ;
 s -> next_p_frame_damaged = s1 -> next_p_frame_damaged ;
 s -> workaround_bugs = s1 -> workaround_bugs ;
 memcpy ( & s -> time_increment_bits , & s1 -> time_increment_bits , ( char * ) & s1 -> shape - ( char * ) & s1 -> time_increment_bits ) ;
 s -> max_b_frames = s1 -> max_b_frames ;
 s -> low_delay = s1 -> low_delay ;
 s -> droppable = s1 -> droppable ;
 s -> divx_packed = s1 -> divx_packed ;
 if ( s1 -> bitstream_buffer ) {
 if ( s1 -> bitstream_buffer_size + FF_INPUT_BUFFER_PADDING_SIZE > s -> allocated_bitstream_buffer_size ) av_fast_malloc ( & s -> bitstream_buffer , & s -> allocated_bitstream_buffer_size , s1 -> allocated_bitstream_buffer_size ) ;
 s -> bitstream_buffer_size = s1 -> bitstream_buffer_size ;
 memcpy ( s -> bitstream_buffer , s1 -> bitstream_buffer , s1 -> bitstream_buffer_size ) ;
 memset ( s -> bitstream_buffer + s -> bitstream_buffer_size , 0 , FF_INPUT_BUFFER_PADDING_SIZE ) ;
 }
 if ( ! s -> edge_emu_buffer ) if ( s1 -> linesize ) {
 if ( ff_mpv_frame_size_alloc ( s , s1 -> linesize ) < 0 ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "Failed to allocate context " "scratch buffers.\n" ) ;
 return AVERROR ( ENOMEM ) ;
 }
 }
 else {
 av_log ( s -> avctx , AV_LOG_ERROR , "Context scratch buffers could not " "be allocated due to unknown size.\n" ) ;
 return AVERROR_BUG ;
 }
 memcpy ( & s -> progressive_sequence , & s1 -> progressive_sequence , ( char * ) & s1 -> rtp_mode - ( char * ) & s1 -> progressive_sequence ) ;
 if ( ! s1 -> first_field ) {
 s -> last_pict_type = s1 -> pict_type ;
 if ( s1 -> current_picture_ptr ) s -> last_lambda_for [ s1 -> pict_type ] = s1 -> current_picture_ptr -> f . quality ;
 if ( s1 -> pict_type != AV_PICTURE_TYPE_B ) {
 s -> last_non_b_pict_type = s1 -> pict_type ;
 }
 }
 return 0 ;
 }