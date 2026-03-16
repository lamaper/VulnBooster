bool gs_device_is_memory ( const gx_device * dev ) {
 int bits_per_pixel = dev -> color_info . depth ;
 const gx_device_memory * mdproto ;
 mdproto = gdev_mem_device_for_bits ( bits_per_pixel ) ;
 if ( mdproto != 0 && dev_proc ( dev , draw_thin_line ) == dev_proc ( mdproto , draw_thin_line ) ) return true ;
 mdproto = gdev_mem_word_device_for_bits ( bits_per_pixel ) ;
 return ( mdproto != 0 && dev_proc ( dev , draw_thin_line ) == dev_proc ( mdproto , draw_thin_line ) ) ;
 }