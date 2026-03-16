int gdev_mem_data_size ( const gx_device_memory * dev , int width , int height , ulong * psize ) {
 ulong bits_size ;
 ulong line_ptrs_size = gdev_mem_line_ptrs_size ( dev , width , height ) ;
 if ( gdev_mem_bits_size ( dev , width , height , & bits_size ) < 0 || bits_size > max_ulong - line_ptrs_size ) return_error ( gs_error_VMerror ) ;
 * psize = bits_size + line_ptrs_size ;
 return 0 ;
 }