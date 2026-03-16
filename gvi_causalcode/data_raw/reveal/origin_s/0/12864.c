static int x_set_buffer ( gx_device_X * xdev ) {
 gs_memory_t * mem = gs_memory_stable ( xdev -> memory ) ;
 bool buffered = xdev -> space_params . MaxBitmap > 0 ;
 const gx_device_procs * procs ;
 setup : if ( buffered ) {
 gx_device_memory * mdev = ( gx_device_memory * ) xdev -> target ;
 if ( mdev == 0 || mdev -> color_info . depth != xdev -> orig_color_info . depth ) {
 const gx_device_memory * mdproto = gdev_mem_device_for_bits ( xdev -> orig_color_info . depth ) ;
 if ( ! mdproto ) {
 buffered = false ;
 goto setup ;
 }
 if ( mdev ) {
 gx_device_set_target ( ( gx_device_forward * ) mdev , NULL ) ;
 }
 else {
 mdev = gs_alloc_struct ( mem , gx_device_memory , & st_device_memory , "memory device" ) ;
 if ( mdev == 0 ) {
 buffered = false ;
 goto setup ;
 }
 }
 gs_make_mem_device ( mdev , mdproto , mem , 0 , ( gx_device * ) xdev ) ;
 gx_device_set_target ( ( gx_device_forward * ) xdev , ( gx_device * ) mdev ) ;
 xdev -> is_buffered = true ;
 }
 if ( mdev -> width != xdev -> width || mdev -> height != xdev -> height ) {
 byte * buffer ;
 ulong space ;
 if ( gdev_mem_data_size ( mdev , xdev -> width , xdev -> height , & space ) < 0 || space > xdev -> space_params . MaxBitmap ) {
 buffered = false ;
 goto setup ;
 }
 buffer = ( xdev -> buffer ? ( byte * ) gs_resize_object ( mem , xdev -> buffer , space , "buffer" ) : gs_alloc_bytes ( mem , space , "buffer" ) ) ;
 if ( ! buffer ) {
 buffered = false ;
 goto setup ;
 }
 xdev -> buffer_size = space ;
 xdev -> buffer = buffer ;
 mdev -> width = xdev -> width ;
 mdev -> height = xdev -> height ;
 mdev -> icc_struct = xdev -> icc_struct ;
 rc_increment ( xdev -> icc_struct ) ;
 mdev -> color_info = xdev -> orig_color_info ;
 mdev -> base = xdev -> buffer ;
 gdev_mem_open_scan_lines ( mdev , xdev -> height ) ;
 }
 xdev -> white = gx_device_white ( ( gx_device * ) xdev ) ;
 xdev -> black = gx_device_black ( ( gx_device * ) xdev ) ;
 procs = & gs_bbox_device . procs ;
 }
 else {
 gs_free_object ( mem , xdev -> buffer , "buffer" ) ;
 xdev -> buffer = 0 ;
 xdev -> buffer_size = 0 ;
 if ( ! xdev -> is_buffered ) return 0 ;
 gx_device_set_target ( ( gx_device_forward * ) xdev -> target , NULL ) ;
 gx_device_set_target ( ( gx_device_forward * ) xdev , NULL ) ;
 xdev -> is_buffered = false ;
 procs = & gs_x11_device . procs ;
 }
 if ( dev_proc ( xdev , fill_rectangle ) != procs -> fill_rectangle ) {

 COPY_PROC ( copy_mono ) ;
 COPY_PROC ( copy_color ) ;
 COPY_PROC ( copy_alpha ) ;
 COPY_PROC ( fill_path ) ;
 COPY_PROC ( stroke_path ) ;
 COPY_PROC ( fill_mask ) ;
 COPY_PROC ( fill_trapezoid ) ;
 COPY_PROC ( fill_parallelogram ) ;
 COPY_PROC ( fill_triangle ) ;
 COPY_PROC ( draw_thin_line ) ;
 COPY_PROC ( strip_tile_rectangle ) ;
 COPY_PROC ( strip_copy_rop ) ;
 COPY_PROC ( begin_typed_image ) ;
 COPY_PROC ( text_begin ) ;

 check_device_separable ( ( gx_device * ) xdev ) ;
 gx_device_forward_fill_in_procs ( ( gx_device_forward * ) xdev ) ;
 xdev -> box_procs = gdev_x_box_procs ;
 xdev -> box_proc_data = xdev ;
 }
 else {
 check_device_separable ( ( gx_device * ) xdev ) ;
 gx_device_fill_in_procs ( ( gx_device * ) xdev ) ;
 }
 }
 return 0 ;
 }