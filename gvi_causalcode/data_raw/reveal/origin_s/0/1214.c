int gdev_mem_open_scan_lines ( gx_device_memory * mdev , int setup_height ) {
 bool line_pointers_adjacent = true ;
 ulong size ;
 if ( setup_height < 0 || setup_height > mdev -> height ) return_error ( gs_error_rangecheck ) ;
 if ( mdev -> bitmap_memory != 0 ) {
 int align ;
 if ( gdev_mem_bitmap_size ( mdev , & size ) < 0 ) return_error ( gs_error_VMerror ) ;
 if ( ( uint ) size != size ) return_error ( gs_error_limitcheck ) ;
 mdev -> base = gs_alloc_bytes ( mdev -> bitmap_memory , ( uint ) size , "mem_open" ) ;
 if ( mdev -> base == 0 ) return_error ( gs_error_VMerror ) ;


 mdev -> base += ( - ( int ) ( intptr_t ) mdev -> base ) & ( align - 1 ) ;
 mdev -> foreign_bits = false ;
 }
 else if ( mdev -> line_pointer_memory != 0 ) {
 mdev -> line_ptrs = ( byte * * ) gs_alloc_byte_array ( mdev -> line_pointer_memory , mdev -> height , sizeof ( byte * ) * ( mdev -> is_planar ? mdev -> color_info . num_components : 1 ) , "gdev_mem_open_scan_lines" ) ;
 if ( mdev -> line_ptrs == 0 ) return_error ( gs_error_VMerror ) ;
 mdev -> foreign_line_pointers = false ;
 line_pointers_adjacent = false ;
 }
 if ( line_pointers_adjacent ) {
 int code ;
 if ( mdev -> base == 0 ) return_error ( gs_error_rangecheck ) ;
 code = gdev_mem_bits_size ( mdev , mdev -> width , mdev -> height , & size ) ;
 if ( code < 0 ) return code ;
 mdev -> line_ptrs = ( byte * * ) ( mdev -> base + size ) ;
 }
 mdev -> raster = gx_device_raster ( ( gx_device * ) mdev , 1 ) ;
 return gdev_mem_set_line_ptrs ( mdev , NULL , 0 , NULL , setup_height ) ;
 }