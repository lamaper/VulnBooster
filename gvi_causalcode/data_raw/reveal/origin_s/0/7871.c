const gx_device_memory * gdev_mem_word_device_for_bits ( int bits_per_pixel ) {
 return ( ( uint ) bits_per_pixel > 64 ? ( const gx_device_memory * ) 0 : mem_word_devices [ bits_per_pixel ] ) ;
 }