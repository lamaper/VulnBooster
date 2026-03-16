static int mxpeg_decode_com ( MXpegDecodeContext * s , const uint8_t * buf_ptr , int buf_size ) {
 int len , ret = 0 ;
 if ( buf_size < 2 ) return 0 ;
 len = AV_RB16 ( buf_ptr ) ;
 if ( len > 14 && len <= buf_size && ! strncmp ( buf_ptr + 2 , "MXM" , 3 ) ) {
 ret = mxpeg_decode_mxm ( s , buf_ptr + 2 , len - 2 ) ;
 }
 skip_bits ( & s -> jpg . gb , 8 * FFMIN ( len , buf_size ) ) ;
 return ret ;
 }