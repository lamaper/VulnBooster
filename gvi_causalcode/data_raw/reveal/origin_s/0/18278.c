static int decode_frame ( AVCodecContext * avctx , void * data , int * got_frame , AVPacket * avpkt ) {
 MDECContext * const a = avctx -> priv_data ;
 const uint8_t * buf = avpkt -> data ;
 int buf_size = avpkt -> size ;
 ThreadFrame frame = {
 . f = data }
 ;
 int i , ret ;
 if ( ( ret = ff_thread_get_buffer ( avctx , & frame , 0 ) ) < 0 ) {
 av_log ( avctx , AV_LOG_ERROR , "get_buffer() failed\n" ) ;
 return ret ;
 }
 frame . f -> pict_type = AV_PICTURE_TYPE_I ;
 frame . f -> key_frame = 1 ;
 av_fast_malloc ( & a -> bitstream_buffer , & a -> bitstream_buffer_size , buf_size + FF_INPUT_BUFFER_PADDING_SIZE ) ;
 if ( ! a -> bitstream_buffer ) return AVERROR ( ENOMEM ) ;
 for ( i = 0 ;
 i < buf_size ;
 i += 2 ) {
 a -> bitstream_buffer [ i ] = buf [ i + 1 ] ;
 a -> bitstream_buffer [ i + 1 ] = buf [ i ] ;
 }
 init_get_bits ( & a -> gb , a -> bitstream_buffer , buf_size * 8 ) ;
 skip_bits ( & a -> gb , 32 ) ;
 a -> qscale = get_bits ( & a -> gb , 16 ) ;
 a -> version = get_bits ( & a -> gb , 16 ) ;
 a -> last_dc [ 0 ] = a -> last_dc [ 1 ] = a -> last_dc [ 2 ] = 128 ;
 for ( a -> mb_x = 0 ;
 a -> mb_x < a -> mb_width ;
 a -> mb_x ++ ) {
 for ( a -> mb_y = 0 ;
 a -> mb_y < a -> mb_height ;
 a -> mb_y ++ ) {
 if ( ( ret = decode_mb ( a , a -> block ) ) < 0 ) return ret ;
 idct_put ( a , frame . f , a -> mb_x , a -> mb_y ) ;
 }
 }
 * got_frame = 1 ;
 return ( get_bits_count ( & a -> gb ) + 31 ) / 32 * 4 ;
 }