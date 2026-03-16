int mem_word_get_bits_rectangle ( gx_device * dev , const gs_int_rect * prect , gs_get_bits_params_t * params , gs_int_rect * * unread ) {
 gx_device_memory * const mdev = ( gx_device_memory * ) dev ;
 byte * src ;
 uint dev_raster = gx_device_raster ( dev , 1 ) ;
 int x = prect -> p . x ;
 int w = prect -> q . x - x ;
 int y = prect -> p . y ;
 int h = prect -> q . y - y ;
 int bit_x , bit_w ;
 int code ;
 fit_fill_xywh ( dev , x , y , w , h ) ;
 if ( w <= 0 || h <= 0 ) {
 x = y = w = h = 0 ;
 }
 bit_x = x * dev -> color_info . depth ;
 bit_w = w * dev -> color_info . depth ;
 src = scan_line_base ( mdev , y ) ;
 mem_swap_byte_rect ( src , dev_raster , bit_x , bit_w , h , false ) ;
 code = mem_get_bits_rectangle ( dev , prect , params , unread ) ;
 mem_swap_byte_rect ( src , dev_raster , bit_x , bit_w , h , false ) ;
 return code ;
 }