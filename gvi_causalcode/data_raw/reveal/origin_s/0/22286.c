static inline int copy_block ( AVCodecContext * avctx , uint8_t * to , uint8_t * from , int offset , int height , int stride ) {
 int i ;
 int width = height ;
 int from_x = offset % WIDTH ;
 int from_y = offset / WIDTH ;
 int overflow = from_x + width - WIDTH ;
 if ( ! from ) {
 return 0 ;
 }
 if ( from_y + height > HEIGHT ) {
 av_log ( avctx , AV_LOG_ERROR , "invalid offset %d during C93 decoding\n" , offset ) ;
 return AVERROR_INVALIDDATA ;
 }
 if ( overflow > 0 ) {
 width -= overflow ;
 for ( i = 0 ;
 i < height ;
 i ++ ) {
 memcpy ( & to [ i * stride + width ] , & from [ ( from_y + i ) * stride ] , overflow ) ;
 }
 }
 for ( i = 0 ;
 i < height ;
 i ++ ) {
 memcpy ( & to [ i * stride ] , & from [ ( from_y + i ) * stride + from_x ] , width ) ;
 }
 return 0 ;
 }