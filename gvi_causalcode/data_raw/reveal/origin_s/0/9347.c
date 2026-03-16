int mem_close ( gx_device * dev ) {
 gx_device_memory * const mdev = ( gx_device_memory * ) dev ;
 if ( mdev -> bitmap_memory != 0 ) {
 gs_free_object ( mdev -> bitmap_memory , mdev -> base , "mem_close" ) ;
 mdev -> base = 0 ;
 }
 else if ( mdev -> line_pointer_memory != 0 ) {
 gs_free_object ( mdev -> line_pointer_memory , mdev -> line_ptrs , "mem_close" ) ;
 mdev -> line_ptrs = 0 ;
 }
 return 0 ;
 }