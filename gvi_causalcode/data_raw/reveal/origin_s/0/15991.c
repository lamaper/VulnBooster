int mem_mapped_map_color_rgb ( gx_device * dev , gx_color_index color , gx_color_value prgb [ 3 ] ) {
 gx_device_memory * const mdev = ( gx_device_memory * ) dev ;
 const byte * pptr = mdev -> palette . data + ( int ) color * 3 ;
 prgb [ 0 ] = gx_color_value_from_byte ( pptr [ 0 ] ) ;
 prgb [ 1 ] = gx_color_value_from_byte ( pptr [ 1 ] ) ;
 prgb [ 2 ] = gx_color_value_from_byte ( pptr [ 2 ] ) ;
 return 0 ;
 }