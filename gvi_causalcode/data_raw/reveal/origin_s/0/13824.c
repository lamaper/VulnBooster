void gs_make_mem_mono_device ( gx_device_memory * dev , gs_memory_t * mem , gx_device * target ) {
 gx_device_init ( ( gx_device * ) dev , ( const gx_device * ) & mem_mono_device , mem , true ) ;
 set_dev_proc ( dev , get_page_device , gx_default_get_page_device ) ;
 gx_device_set_target ( ( gx_device_forward * ) dev , target ) ;
 dev -> raster = gx_device_raster ( ( gx_device * ) dev , 1 ) ;
 gdev_mem_mono_set_inverted ( dev , true ) ;
 check_device_separable ( ( gx_device * ) dev ) ;
 gx_device_fill_in_procs ( ( gx_device * ) dev ) ;
 set_dev_proc ( dev , get_profile , gx_forward_get_profile ) ;
 set_dev_proc ( dev , set_graphics_type_tag , gx_forward_set_graphics_type_tag ) ;
 dev -> graphics_type_tag = target ? target -> graphics_type_tag : GS_UNKNOWN_TAG ;
 }