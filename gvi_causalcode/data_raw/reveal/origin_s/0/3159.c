static void qtrle_decode_16bpp ( QtrleContext * s , int row_ptr , int lines_to_change ) {
 int rle_code ;
 int pixel_ptr ;
 int row_inc = s -> frame . linesize [ 0 ] ;
 unsigned short rgb16 ;
 unsigned char * rgb = s -> frame . data [ 0 ] ;
 int pixel_limit = s -> frame . linesize [ 0 ] * s -> avctx -> height ;
 while ( lines_to_change -- ) {
 pixel_ptr = row_ptr + ( bytestream2_get_byte ( & s -> g ) - 1 ) * 2 ;
 CHECK_PIXEL_PTR ( 0 ) ;
 while ( ( rle_code = ( signed char ) bytestream2_get_byte ( & s -> g ) ) != - 1 ) {
 if ( rle_code == 0 ) {
 pixel_ptr += ( bytestream2_get_byte ( & s -> g ) - 1 ) * 2 ;
 CHECK_PIXEL_PTR ( 0 ) ;
 }
 else if ( rle_code < 0 ) {
 rle_code = - rle_code ;
 rgb16 = bytestream2_get_be16 ( & s -> g ) ;
 CHECK_PIXEL_PTR ( rle_code * 2 ) ;
 while ( rle_code -- ) {
 * ( unsigned short * ) ( & rgb [ pixel_ptr ] ) = rgb16 ;
 pixel_ptr += 2 ;
 }
 }
 else {
 CHECK_PIXEL_PTR ( rle_code * 2 ) ;
 while ( rle_code -- ) {
 rgb16 = bytestream2_get_be16 ( & s -> g ) ;
 * ( unsigned short * ) ( & rgb [ pixel_ptr ] ) = rgb16 ;
 pixel_ptr += 2 ;
 }
 }
 }
 row_ptr += row_inc ;
 }
 }