static int mxpeg_decode_mxm ( MXpegDecodeContext * s , const uint8_t * buf_ptr , int buf_size ) {
 unsigned bitmask_size , mb_count ;
 int i ;
 s -> mb_width = AV_RL16 ( buf_ptr + 4 ) ;
 s -> mb_height = AV_RL16 ( buf_ptr + 6 ) ;
 mb_count = s -> mb_width * s -> mb_height ;
 bitmask_size = ( mb_count + 7 ) >> 3 ;
 if ( bitmask_size > buf_size - 12 ) {
 av_log ( s -> jpg . avctx , AV_LOG_ERROR , "MXM bitmask is not complete\n" ) ;
 return AVERROR ( EINVAL ) ;
 }
 if ( s -> bitmask_size != bitmask_size ) {
 av_freep ( & s -> mxm_bitmask ) ;
 s -> mxm_bitmask = av_malloc ( bitmask_size ) ;
 if ( ! s -> mxm_bitmask ) {
 av_log ( s -> jpg . avctx , AV_LOG_ERROR , "MXM bitmask memory allocation error\n" ) ;
 return AVERROR ( ENOMEM ) ;
 }
 av_freep ( & s -> completion_bitmask ) ;
 s -> completion_bitmask = av_mallocz ( bitmask_size ) ;
 if ( ! s -> completion_bitmask ) {
 av_log ( s -> jpg . avctx , AV_LOG_ERROR , "Completion bitmask memory allocation error\n" ) ;
 return AVERROR ( ENOMEM ) ;
 }
 s -> bitmask_size = bitmask_size ;
 }
 memcpy ( s -> mxm_bitmask , buf_ptr + 12 , bitmask_size ) ;
 s -> got_mxm_bitmask = 1 ;
 if ( ! s -> has_complete_frame ) {
 uint8_t completion_check = 0xFF ;
 for ( i = 0 ;
 i < bitmask_size ;
 ++ i ) {
 s -> completion_bitmask [ i ] |= s -> mxm_bitmask [ i ] ;
 completion_check &= s -> completion_bitmask [ i ] ;
 }
 s -> has_complete_frame = ! ( completion_check ^ 0xFF ) ;
 }
 return 0 ;
 }