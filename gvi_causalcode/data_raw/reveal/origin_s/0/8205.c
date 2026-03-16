ulong gdev_mem_line_ptrs_size ( const gx_device_memory * dev , int width , int height ) {
 return ( ulong ) height * sizeof ( byte * ) * ( dev -> is_planar ? dev -> color_info . num_components : 1 ) ;
 }