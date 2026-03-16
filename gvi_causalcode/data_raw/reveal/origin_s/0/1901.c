int gs_make_mem_device_with_copydevice ( gx_device_memory * * ppdev , const gx_device_memory * mdproto , gs_memory_t * mem , int page_device , gx_device * target ) {
 int code ;
 gx_device_memory * pdev ;
 if ( mem == 0 ) return - 1 ;
 code = gs_copydevice ( ( gx_device * * ) & pdev , ( const gx_device * ) mdproto , mem ) ;
 if ( code < 0 ) return code ;
 switch ( page_device ) {
 case - 1 : set_dev_proc ( pdev , get_page_device , gx_default_get_page_device ) ;
 break ;
 case 1 : set_dev_proc ( pdev , get_page_device , gx_page_device_get_page_device ) ;
 break ;
 }
 if ( target == 0 ) {
 if ( pdev -> color_info . depth == 1 ) {
 pdev -> cached_colors . black = 1 ;
 pdev -> cached_colors . white = 0 ;
 }
 else {
 pdev -> cached_colors . black = 0 ;
 pdev -> cached_colors . white = ( 1 << pdev -> color_info . depth ) - 1 ;
 }
 pdev -> graphics_type_tag = GS_UNKNOWN_TAG ;
 }
 else {
 gx_device_set_target ( ( gx_device_forward * ) pdev , target ) ;
 gx_device_forward_color_procs ( ( gx_device_forward * ) pdev ) ;
 gx_device_copy_color_procs ( ( gx_device * ) pdev , target ) ;
 pdev -> cached_colors = target -> cached_colors ;
 pdev -> graphics_type_tag = target -> graphics_type_tag ;
 }
 if ( pdev -> color_info . depth == 1 ) {
 gx_color_value cv [ 3 ] ;
 cv [ 0 ] = cv [ 1 ] = cv [ 2 ] = 0 ;
 gdev_mem_mono_set_inverted ( pdev , ( target == 0 || ( * dev_proc ( pdev , encode_color ) ) ( ( gx_device * ) pdev , cv ) != 0 ) ) ;
 }
 check_device_separable ( ( gx_device * ) pdev ) ;
 gx_device_fill_in_procs ( ( gx_device * ) pdev ) ;
 pdev -> band_y = 0 ;
 * ppdev = pdev ;
 return 0 ;
 }