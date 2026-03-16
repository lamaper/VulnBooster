static int decode_frame ( AVCodecContext * avctx , void * data , int * got_frame , AVPacket * pkt ) {
 BinkContext * const c = avctx -> priv_data ;
 AVFrame * frame = data ;
 GetBitContext gb ;
 int plane , plane_idx , ret ;
 int bits_count = pkt -> size << 3 ;
 if ( c -> version > 'b' ) {
 if ( ( ret = ff_get_buffer ( avctx , frame , AV_GET_BUFFER_FLAG_REF ) ) < 0 ) {
 av_log ( avctx , AV_LOG_ERROR , "get_buffer() failed\n" ) ;
 return ret ;
 }
 }
 else {
 if ( ( ret = ff_reget_buffer ( avctx , c -> last ) ) < 0 ) {
 av_log ( avctx , AV_LOG_ERROR , "reget_buffer() failed\n" ) ;
 return ret ;
 }
 if ( ( ret = av_frame_ref ( frame , c -> last ) ) < 0 ) return ret ;
 }
 init_get_bits ( & gb , pkt -> data , bits_count ) ;
 if ( c -> has_alpha ) {
 if ( c -> version >= 'i' ) skip_bits_long ( & gb , 32 ) ;
 if ( ( ret = bink_decode_plane ( c , frame , & gb , 3 , 0 ) ) < 0 ) return ret ;
 }
 if ( c -> version >= 'i' ) skip_bits_long ( & gb , 32 ) ;
 for ( plane = 0 ;
 plane < 3 ;
 plane ++ ) {
 plane_idx = ( ! plane || ! c -> swap_planes ) ? plane : ( plane ^ 3 ) ;
 if ( c -> version > 'b' ) {
 if ( ( ret = bink_decode_plane ( c , frame , & gb , plane_idx , ! ! plane ) ) < 0 ) return ret ;
 }
 else {
 if ( ( ret = binkb_decode_plane ( c , frame , & gb , plane_idx , ! avctx -> frame_number , ! ! plane ) ) < 0 ) return ret ;
 }
 if ( get_bits_count ( & gb ) >= bits_count ) break ;
 }
 emms_c ( ) ;
 if ( c -> version > 'b' ) {
 av_frame_unref ( c -> last ) ;
 if ( ( ret = av_frame_ref ( c -> last , frame ) ) < 0 ) return ret ;
 }
 * got_frame = 1 ;
 return pkt -> size ;
 }