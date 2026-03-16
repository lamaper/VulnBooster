int gs_make_mem_mono_device_with_copydevice ( gx_device_memory * * ppdev , gs_memory_t * mem , gx_device * target ) {
 int code ;
 gx_device_memory * pdev ;
 if ( mem == 0 ) return - 1 ;
 code = gs_copydevice ( ( gx_device * * ) & pdev , ( const gx_device * ) & mem_mono_device , mem ) ;
 if ( code < 0 ) return code ;
 set_dev_proc ( pdev , get_page_device , gx_default_get_page_device ) ;
 gx_device_set_target ( ( gx_device_forward * ) pdev , target ) ;
 set_dev_proc ( pdev , get_profile , gx_forward_get_profile ) ;
 gdev_mem_mono_set_inverted ( pdev , true ) ;
 check_device_separable ( ( gx_device * ) pdev ) ;
 gx_device_fill_in_procs ( ( gx_device * ) pdev ) ;
 * ppdev = pdev ;
 return 0 ;
 }