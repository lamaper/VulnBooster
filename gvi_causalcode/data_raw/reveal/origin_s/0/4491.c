void gs_make_mem_device ( gx_device_memory * dev , const gx_device_memory * mdproto , gs_memory_t * mem , int page_device , gx_device * target ) {
 gx_device_init ( ( gx_device * ) dev , ( const gx_device * ) mdproto , mem , true ) ;
 dev -> stype = & st_device_memory ;
 switch ( page_device ) {
 case - 1 : set_dev_proc ( dev , get_page_device , gx_default_get_page_device ) ;
 break ;
 case 1 : set_dev_proc ( dev , get_page_device , gx_page_device_get_page_device ) ;
 break ;
 }
 if ( target == 0 ) {
 if ( dev -> color_info . depth == 1 ) {
 dev -> cached_colors . black = 1 ;
 dev -> cached_colors . white = 0 ;
 }
 else {
 dev -> cached_colors . black = 0 ;
 dev -> cached_colors . white = ( 1 << dev -> color_info . depth ) - 1 ;
 }
 dev -> graphics_type_tag = GS_UNKNOWN_TAG ;
 }
 else {
 gx_device_set_target ( ( gx_device_forward * ) dev , target ) ;
 gx_device_forward_color_procs ( ( gx_device_forward * ) dev ) ;
 gx_device_copy_color_procs ( ( gx_device * ) dev , target ) ;
 dev -> color_info . separable_and_linear = target -> color_info . separable_and_linear ;
 dev -> cached_colors = target -> cached_colors ;
 dev -> graphics_type_tag = target -> graphics_type_tag ;


 if ( dev -> color_info . depth == 1 ) {
 gx_color_value cv [ GX_DEVICE_COLOR_MAX_COMPONENTS ] ;
 uchar k ;
 if ( target != 0 ) {
 for ( k = 0 ;
 k < target -> color_info . num_components ;
 k ++ ) {
 cv [ k ] = 0 ;
 }
 }
 gdev_mem_mono_set_inverted ( dev , ( target == 0 || ( * dev_proc ( dev , encode_color ) ) ( ( gx_device * ) dev , cv ) != 0 ) ) ;
 }
 check_device_separable ( ( gx_device * ) dev ) ;
 gx_device_fill_in_procs ( ( gx_device * ) dev ) ;
 dev -> band_y = 0 ;
 }