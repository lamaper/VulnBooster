static void qtrle_decode_1bpp ( QtrleContext * s , int row_ptr , int lines_to_change ) {
 int rle_code ;
 int pixel_ptr ;
 int row_inc = s -> frame . linesize [ 0 ] ;
 unsigned char pi0 , pi1 ;
 unsigned char * rgb = s -> frame . data [ 0 ] ;
 int pixel_limit = s -> frame . linesize [ 0 ] * s -> avctx -> height ;
 int skip ;
 row_ptr -= row_inc ;
 pixel_ptr = row_ptr ;
 lines_to_change ++ ;
 while ( lines_to_change ) {
 skip = bytestream2_get_byte ( & s -> g ) ;
 rle_code = ( signed char ) bytestream2_get_byte ( & s -> g ) ;
 if ( rle_code == 0 ) break ;
 if ( skip & 0x80 ) {
 lines_to_change -- ;
 row_ptr += row_inc ;
 pixel_ptr = row_ptr + 2 * ( skip & 0x7f ) ;
 }
 else pixel_ptr += 2 * skip ;
 CHECK_PIXEL_PTR ( 0 ) ;
 if ( rle_code < 0 ) {
 rle_code = - rle_code ;
 pi0 = bytestream2_get_byte ( & s -> g ) ;
 pi1 = bytestream2_get_byte ( & s -> g ) ;
 CHECK_PIXEL_PTR ( rle_code * 2 ) ;
 while ( rle_code -- ) {
 rgb [ pixel_ptr ++ ] = pi0 ;
 rgb [ pixel_ptr ++ ] = pi1 ;
 }
 }
 else {
 rle_code *= 2 ;
 CHECK_PIXEL_PTR ( rle_code ) ;
 while ( rle_code -- ) rgb [ pixel_ptr ++ ] = bytestream2_get_byte ( & s -> g ) ;
 }
 }
 }