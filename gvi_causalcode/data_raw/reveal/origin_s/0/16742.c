static int png_decode_idat ( PNGDecContext * s , int length ) {
 int ret ;
 s -> zstream . avail_in = FFMIN ( length , bytestream2_get_bytes_left ( & s -> gb ) ) ;
 s -> zstream . next_in = s -> gb . buffer ;
 bytestream2_skip ( & s -> gb , length ) ;
 while ( s -> zstream . avail_in > 0 ) {
 ret = inflate ( & s -> zstream , Z_PARTIAL_FLUSH ) ;
 if ( ret != Z_OK && ret != Z_STREAM_END ) {
 return - 1 ;
 }
 if ( s -> zstream . avail_out == 0 ) {
 if ( ! ( s -> state & PNG_ALLIMAGE ) ) {
 png_handle_row ( s ) ;
 }
 s -> zstream . avail_out = s -> crow_size ;
 s -> zstream . next_out = s -> crow_buf ;
 }
 }
 return 0 ;
 }