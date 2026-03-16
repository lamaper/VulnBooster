static int mxpeg_decode_app ( MXpegDecodeContext * s , const uint8_t * buf_ptr , int buf_size ) {
 int len ;
 if ( buf_size < 2 ) return 0 ;
 len = AV_RB16 ( buf_ptr ) ;
 skip_bits ( & s -> jpg . gb , 8 * FFMIN ( len , buf_size ) ) ;
 return 0 ;
 }