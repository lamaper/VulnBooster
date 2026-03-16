static int decode_rle ( AVCodecContext * avctx , AVSubtitle * sub , int rect , const uint8_t * buf , unsigned int buf_size ) {
 const uint8_t * rle_bitmap_end ;
 int pixel_count , line_count ;
 rle_bitmap_end = buf + buf_size ;
 sub -> rects [ rect ] -> pict . data [ 0 ] = av_malloc ( sub -> rects [ rect ] -> w * sub -> rects [ rect ] -> h ) ;
 if ( ! sub -> rects [ rect ] -> pict . data [ 0 ] ) return - 1 ;
 pixel_count = 0 ;
 line_count = 0 ;
 while ( buf < rle_bitmap_end && line_count < sub -> rects [ rect ] -> h ) {
 uint8_t flags , color ;
 int run ;
 color = bytestream_get_byte ( & buf ) ;
 run = 1 ;
 if ( color == 0x00 ) {
 flags = bytestream_get_byte ( & buf ) ;
 run = flags & 0x3f ;
 if ( flags & 0x40 ) run = ( run << 8 ) + bytestream_get_byte ( & buf ) ;
 color = flags & 0x80 ? bytestream_get_byte ( & buf ) : 0 ;
 }
 if ( run > 0 && pixel_count + run <= sub -> rects [ rect ] -> w * sub -> rects [ rect ] -> h ) {
 memset ( sub -> rects [ rect ] -> pict . data [ 0 ] + pixel_count , color , run ) ;
 pixel_count += run ;
 }
 else if ( ! run ) {
 if ( pixel_count % sub -> rects [ rect ] -> w > 0 ) av_log ( avctx , AV_LOG_ERROR , "Decoded %d pixels, when line should be %d pixels\n" , pixel_count % sub -> rects [ rect ] -> w , sub -> rects [ rect ] -> w ) ;
 line_count ++ ;
 }
 }
 if ( pixel_count < sub -> rects [ rect ] -> w * sub -> rects [ rect ] -> h ) {
 av_log ( avctx , AV_LOG_ERROR , "Insufficient RLE data for subtitle\n" ) ;
 return - 1 ;
 }
 av_dlog ( avctx , "Pixel Count = %d, Area = %d\n" , pixel_count , sub -> rects [ rect ] -> w * sub -> rects [ rect ] -> h ) ;
 return 0 ;
 }