const gx_device_memory * gdev_mem_device_for_bits ( int bits_per_pixel ) {
 return ( ( uint ) bits_per_pixel > 64 ? & mem_x_device : mem_devices [ bits_per_pixel ] ) ;
 }