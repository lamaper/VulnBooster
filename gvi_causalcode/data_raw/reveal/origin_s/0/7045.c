static int read_rgb24_component_line ( CLLCContext * ctx , GetBitContext * gb , int * top_left , VLC * vlc , uint8_t * outbuf ) {
 uint8_t * dst ;
 int pred , code ;
 int i ;
 OPEN_READER ( bits , gb ) ;
 dst = outbuf ;
 pred = * top_left ;
 for ( i = 0 ;
 i < ctx -> avctx -> width ;
 i ++ ) {
 UPDATE_CACHE ( bits , gb ) ;
 GET_VLC ( code , bits , gb , vlc -> table , 7 , 2 ) ;
 pred += code ;
 dst [ 0 ] = pred ;
 dst += 3 ;
 }
 CLOSE_READER ( bits , gb ) ;
 * top_left = dst [ - 3 * ctx -> avctx -> width ] ;
 return 0 ;
 }