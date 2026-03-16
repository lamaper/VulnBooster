int gdev_x_put_params ( gx_device * dev , gs_param_list * plist ) {
 gx_device_X * xdev = ( gx_device_X * ) dev ;
 gx_device_X values ;
 int orig_MaxBitmap = xdev -> space_params . MaxBitmap ;
 long pwin = ( long ) xdev -> pwin ;
 bool save_is_page = xdev -> IsPageDevice ;
 int ecode = 0 , code ;
 bool clear_window = false ;
 values = * xdev ;
 ecode = param_put_long ( plist , "WindowID" , & pwin , ecode ) ;
 ecode = param_put_bool ( plist , ".IsPageDevice" , & values . IsPageDevice , ecode ) ;
 ecode = param_put_int ( plist , "MaxTempPixmap" , & values . MaxTempPixmap , ecode ) ;
 ecode = param_put_int ( plist , "MaxTempImage" , & values . MaxTempImage , ecode ) ;
 if ( ecode < 0 ) return ecode ;
 if ( pwin == ( long ) xdev -> pwin ) dev -> is_open = false ;
 xdev -> IsPageDevice = values . IsPageDevice ;
 code = gx_default_put_params ( dev , plist ) ;
 dev -> is_open = values . is_open ;
 if ( code < 0 ) {
 xdev -> IsPageDevice = save_is_page ;
 return code ;
 }
 if ( pwin != ( long ) xdev -> pwin ) {
 if ( xdev -> is_open ) gs_closedevice ( dev ) ;
 xdev -> pwin = ( Window ) pwin ;
 }
 if ( xdev -> is_open && xdev -> ghostview ) {
 dev -> width = values . width ;
 dev -> height = values . height ;
 dev -> x_pixels_per_inch = values . x_pixels_per_inch ;
 dev -> y_pixels_per_inch = values . y_pixels_per_inch ;
 dev -> HWResolution [ 0 ] = values . HWResolution [ 0 ] ;
 dev -> HWResolution [ 1 ] = values . HWResolution [ 1 ] ;
 dev -> MediaSize [ 0 ] = values . MediaSize [ 0 ] ;
 dev -> MediaSize [ 1 ] = values . MediaSize [ 1 ] ;
 }
 if ( xdev -> is_open && ! xdev -> ghostview && ( dev -> width != values . width || dev -> height != values . height || dev -> HWResolution [ 0 ] != values . HWResolution [ 0 ] || dev -> HWResolution [ 1 ] != values . HWResolution [ 1 ] ) ) {
 int area_width = WidthOfScreen ( xdev -> scr ) , area_height = HeightOfScreen ( xdev -> scr ) ;
 int dw , dh ;
 x_get_work_area ( xdev , & area_width , & area_height ) ;
 dev -> x_pixels_per_inch = values . x_pixels_per_inch ;
 dev -> y_pixels_per_inch = values . y_pixels_per_inch ;
 dev -> HWResolution [ 0 ] = values . HWResolution [ 0 ] ;
 dev -> HWResolution [ 1 ] = values . HWResolution [ 1 ] ;
 dev -> width = min ( dev -> width , area_width ) ;
 dev -> height = min ( dev -> height , area_height ) ;
 if ( dev -> width <= 0 || dev -> height <= 0 ) {
 emprintf3 ( dev -> memory , "Requested pagesize %d x %d not supported by %s device\n" , dev -> width , dev -> height , dev -> dname ) ;
 return_error ( gs_error_rangecheck ) ;
 }
 dev -> MediaSize [ 0 ] = ( float ) dev -> width / xdev -> x_pixels_per_inch * 72 ;
 dev -> MediaSize [ 1 ] = ( float ) dev -> height / xdev -> y_pixels_per_inch * 72 ;
 dw = dev -> width - values . width ;
 dh = dev -> height - values . height ;
 if ( dw || dh ) {
 XResizeWindow ( xdev -> dpy , xdev -> win , dev -> width , dev -> height ) ;
 if ( xdev -> bpixmap != ( Pixmap ) 0 ) {
 XFreePixmap ( xdev -> dpy , xdev -> bpixmap ) ;
 xdev -> bpixmap = ( Pixmap ) 0 ;
 }
 xdev -> dest = 0 ;
 clear_window = true ;
 }
 if ( xdev -> initial_matrix . xy == 0 ) {
 if ( xdev -> initial_matrix . xx < 0 ) {
 xdev -> initial_matrix . tx += dw ;
 }
 else {
 xdev -> initial_matrix . ty += dh ;
 }
 }
 else {
 if ( xdev -> initial_matrix . xy < 0 ) {
 xdev -> initial_matrix . tx += dh ;
 xdev -> initial_matrix . ty += dw ;
 }
 else {
 }
 }
 }
 xdev -> MaxTempPixmap = values . MaxTempPixmap ;
 xdev -> MaxTempImage = values . MaxTempImage ;
 if ( clear_window || xdev -> space_params . MaxBitmap != orig_MaxBitmap ) {
 if ( xdev -> is_open ) gdev_x_clear_window ( xdev ) ;
 }
 return 0 ;
 }