static void png_put_interlaced_row ( uint8_t * dst , int width , int bits_per_pixel , int pass , int color_type , const uint8_t * src ) {
 int x , mask , dsp_mask , j , src_x , b , bpp ;
 uint8_t * d ;
 const uint8_t * s ;
 mask = ff_png_pass_mask [ pass ] ;
 dsp_mask = png_pass_dsp_mask [ pass ] ;
 switch ( bits_per_pixel ) {
 case 1 : if ( pass == 0 ) memset ( dst , 0 , ( width + 7 ) >> 3 ) ;
 src_x = 0 ;
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 j = ( x & 7 ) ;
 if ( ( dsp_mask << j ) & 0x80 ) {
 b = ( src [ src_x >> 3 ] >> ( 7 - ( src_x & 7 ) ) ) & 1 ;
 dst [ x >> 3 ] |= b << ( 7 - j ) ;
 }
 if ( ( mask << j ) & 0x80 ) src_x ++ ;
 }
 break ;
 default : bpp = bits_per_pixel >> 3 ;
 d = dst ;
 s = src ;
 if ( color_type == PNG_COLOR_TYPE_RGB_ALPHA ) {
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 j = x & 7 ;
 if ( ( dsp_mask << j ) & 0x80 ) {
 * ( uint32_t * ) d = ( s [ 3 ] << 24 ) | ( s [ 0 ] << 16 ) | ( s [ 1 ] << 8 ) | s [ 2 ] ;
 }
 d += bpp ;
 if ( ( mask << j ) & 0x80 ) s += bpp ;
 }
 }
 else {
 for ( x = 0 ;
 x < width ;
 x ++ ) {
 j = x & 7 ;
 if ( ( dsp_mask << j ) & 0x80 ) {
 memcpy ( d , s , bpp ) ;
 }
 d += bpp ;
 if ( ( mask << j ) & 0x80 ) s += bpp ;
 }
 }
 break ;
 }
 }