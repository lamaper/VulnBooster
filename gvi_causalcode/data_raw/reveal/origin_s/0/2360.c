static void mp_read_changes_map ( MotionPixelsContext * mp , GetBitContext * gb , int count , int bits_len , int read_color ) {
 uint16_t * pixels ;
 int offset , w , h , color = 0 , x , y , i ;
 while ( count -- ) {
 offset = get_bits_long ( gb , mp -> offset_bits_len ) ;
 w = get_bits ( gb , bits_len ) + 1 ;
 h = get_bits ( gb , bits_len ) + 1 ;
 if ( read_color ) color = get_bits ( gb , 15 ) ;
 x = offset % mp -> avctx -> width ;
 y = offset / mp -> avctx -> width ;
 if ( y >= mp -> avctx -> height ) continue ;
 w = FFMIN ( w , mp -> avctx -> width - x ) ;
 h = FFMIN ( h , mp -> avctx -> height - y ) ;
 pixels = ( uint16_t * ) & mp -> frame . data [ 0 ] [ y * mp -> frame . linesize [ 0 ] + x * 2 ] ;
 while ( h -- ) {
 mp -> changes_map [ offset ] = w ;
 if ( read_color ) for ( i = 0 ;
 i < w ;
 ++ i ) pixels [ i ] = color ;
 offset += mp -> avctx -> width ;
 pixels += mp -> frame . linesize [ 0 ] / 2 ;
 }
 }
 }