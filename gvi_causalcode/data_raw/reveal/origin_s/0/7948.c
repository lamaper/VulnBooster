static void mpeg_decode_user_data ( AVCodecContext * avctx , const uint8_t * p , int buf_size ) {
 const uint8_t * buf_end = p + buf_size ;
 if ( buf_end - p >= 5 && p [ 0 ] == 'D' && p [ 1 ] == 'T' && p [ 2 ] == 'G' && p [ 3 ] == '1' ) {
 int flags = p [ 4 ] ;
 p += 5 ;
 if ( flags & 0x80 ) {
 p += 2 ;
 }
 if ( flags & 0x40 ) {
 if ( buf_end - p < 1 ) return ;
 avctx -> dtg_active_format = p [ 0 ] & 0x0f ;
 }
 }
 }