int mem_open ( gx_device * dev ) {
 gx_device_memory * const mdev = ( gx_device_memory * ) dev ;
 if ( mdev -> is_planar ) return_error ( gs_error_rangecheck ) ;
 return gdev_mem_open_scan_lines ( mdev , dev -> height ) ;
 }