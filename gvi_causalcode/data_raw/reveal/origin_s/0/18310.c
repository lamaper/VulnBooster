static void qtrle_decode_32bpp ( QtrleContext * s , int row_ptr , int lines_to_change ) {
 int rle_code ;
 int pixel_ptr ;
 int row_inc = s -> frame . linesize [ 0 ] ;
 unsigned int argb ;
 unsigned char * rgb = s -> frame . data [ 0 ] ;
 int pixel_limit = s -> frame . linesize [ 0 ] * s -> avctx -> height ;
 while ( lines_to_change -- ) {
 pixel_ptr = row_ptr + ( bytestream2_get_byte ( & s -> g ) - 1 ) * 4 ;
 CHECK_PIXEL_PTR ( 0 ) ;
 while ( ( rle_code = ( signed char ) bytestream2_get_byte ( & s -> g ) ) != - 1 ) {
 if ( rle_code == 0 ) {
 pixel_ptr += ( bytestream2_get_byte ( & s -> g ) - 1 ) * 4 ;
 CHECK_PIXEL_PTR ( 0 ) ;
 }
 else if ( rle_code < 0 ) {
 rle_code = - rle_code ;
 argb = bytestream2_get_be32 ( & s -> g ) ;
 CHECK_PIXEL_PTR ( rle_code * 4 ) ;
 while ( rle_code -- ) {
 AV_WN32A ( rgb + pixel_ptr , argb ) ;
 pixel_ptr += 4 ;
 }
 }
 else {
 CHECK_PIXEL_PTR ( rle_code * 4 ) ;
 while ( rle_code -- ) {
 argb = bytestream2_get_be32 ( & s -> g ) ;
 AV_WN32A ( rgb + pixel_ptr , argb ) ;
 pixel_ptr += 4 ;
 }
 }
 }
 row_ptr += row_inc ;
 }
 }