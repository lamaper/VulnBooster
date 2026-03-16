int gdev_mem_max_height ( const gx_device_memory * dev , int width , ulong size , bool page_uses_transparency ) {
 int height ;
 ulong max_height ;
 ulong data_size ;
 if ( page_uses_transparency ) {
 max_height = size / ( bitmap_raster_pad_align ( width * dev -> color_info . depth + ESTIMATED_PDF14_ROW_SPACE ( width , dev -> color_info . num_components ) , dev -> pad , dev -> log2_align_mod ) + sizeof ( byte * ) * ( dev -> is_planar ? dev -> color_info . num_components : 1 ) ) ;
 height = ( int ) min ( max_height , max_int ) ;
 }
 else {
 max_height = size / ( bitmap_raster_pad_align ( width * dev -> color_info . depth , dev -> pad , dev -> log2_align_mod ) + sizeof ( byte * ) * ( dev -> is_planar ? dev -> color_info . num_components : 1 ) ) ;
 height = ( int ) min ( max_height , max_int ) ;
 do {
 gdev_mem_data_size ( dev , width , height , & data_size ) ;
 if ( data_size <= size ) break ;
 -- height ;
 }
 while ( data_size > size ) ;
 }
 return height ;
 }