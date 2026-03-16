static void png_handle_row ( PNGDecContext * s ) {
 uint8_t * ptr , * last_row ;
 int got_line ;
 if ( ! s -> interlace_type ) {
 ptr = s -> image_buf + s -> image_linesize * s -> y ;
 if ( s -> color_type == PNG_COLOR_TYPE_RGB_ALPHA ) {
 png_filter_row ( & s -> dsp , s -> tmp_row , s -> crow_buf [ 0 ] , s -> crow_buf + 1 , s -> last_row , s -> row_size , s -> bpp ) ;
 convert_to_rgb32 ( ptr , s -> tmp_row , s -> width , s -> filter_type == PNG_FILTER_TYPE_LOCO ) ;
 FFSWAP ( uint8_t * , s -> last_row , s -> tmp_row ) ;
 }
 else {
 if ( s -> y == 0 ) last_row = s -> last_row ;
 else last_row = ptr - s -> image_linesize ;
 png_filter_row ( & s -> dsp , ptr , s -> crow_buf [ 0 ] , s -> crow_buf + 1 , last_row , s -> row_size , s -> bpp ) ;
 }
 if ( s -> filter_type == PNG_FILTER_TYPE_LOCO && s -> color_type == PNG_COLOR_TYPE_RGB && s -> y > 0 ) deloco_rgb24 ( ptr - s -> image_linesize , s -> row_size ) ;
 s -> y ++ ;
 if ( s -> y == s -> height ) {
 s -> state |= PNG_ALLIMAGE ;
 if ( s -> filter_type == PNG_FILTER_TYPE_LOCO && s -> color_type == PNG_COLOR_TYPE_RGB ) deloco_rgb24 ( ptr , s -> row_size ) ;
 }
 }
 else {
 got_line = 0 ;
 for ( ;
 ;
 ) {
 ptr = s -> image_buf + s -> image_linesize * s -> y ;
 if ( ( ff_png_pass_ymask [ s -> pass ] << ( s -> y & 7 ) ) & 0x80 ) {
 if ( got_line ) break ;
 png_filter_row ( & s -> dsp , s -> tmp_row , s -> crow_buf [ 0 ] , s -> crow_buf + 1 , s -> last_row , s -> pass_row_size , s -> bpp ) ;
 FFSWAP ( uint8_t * , s -> last_row , s -> tmp_row ) ;
 got_line = 1 ;
 }
 if ( ( png_pass_dsp_ymask [ s -> pass ] << ( s -> y & 7 ) ) & 0x80 ) {
 png_put_interlaced_row ( ptr , s -> width , s -> bits_per_pixel , s -> pass , s -> color_type , s -> last_row ) ;
 }
 s -> y ++ ;
 if ( s -> y == s -> height ) {
 for ( ;
 ;
 ) {
 if ( s -> pass == NB_PASSES - 1 ) {
 s -> state |= PNG_ALLIMAGE ;
 goto the_end ;
 }
 else {
 s -> pass ++ ;
 s -> y = 0 ;
 s -> pass_row_size = ff_png_pass_row_size ( s -> pass , s -> bits_per_pixel , s -> width ) ;
 s -> crow_size = s -> pass_row_size + 1 ;
 if ( s -> pass_row_size != 0 ) break ;
 }
 }
 }
 }
 the_end : ;
 }
 }