int gdev_x_open ( gx_device_X * xdev ) {
 XSizeHints sizehints ;
 char * window_id ;
 XEvent event ;
 XVisualInfo xvinfo ;
 int nitems ;
 XtAppContext app_con ;
 Widget toplevel ;
 Display * dpy ;
 XColor xc ;
 int zero = 0 ;
 int xid_height = 0 , xid_width = 0 ;
 int code ;

 extern int _Xdebug ;
 _Xdebug = 1 ;
 }

 char * dispname = getenv ( "DISPLAY" ) ;
 emprintf1 ( xdev -> memory , "Cannot open X display `%s'.\n" , ( dispname == NULL ? "(null)" : dispname ) ) ;
 return_error ( gs_error_ioerror ) ;
 }
 xdev -> dest = 0 ;
 if ( ( window_id = getenv ( "GHOSTVIEW" ) ) ) {
 if ( ! ( xdev -> ghostview = sscanf ( window_id , "%ld %ld" , & ( xdev -> win ) , & ( xdev -> dest ) ) ) ) {
 emprintf ( xdev -> memory , "Cannot get Window ID from ghostview.\n" ) ;
 return_error ( gs_error_ioerror ) ;
 }
 }
 if ( xdev -> pwin != ( Window ) None ) {
 XWindowAttributes attrib ;
 xdev -> win = xdev -> pwin ;
 if ( XGetWindowAttributes ( xdev -> dpy , xdev -> win , & attrib ) ) {
 xdev -> scr = attrib . screen ;
 xvinfo . visual = attrib . visual ;
 xdev -> cmap = attrib . colormap ;
 xid_width = attrib . width ;
 xid_height = attrib . height ;
 }
 else {
 xid_width = xid_height = 0 ;
 }
 }
 else if ( xdev -> ghostview ) {
 XWindowAttributes attrib ;
 Atom type ;
 int format ;
 unsigned long nitems , bytes_after ;
 char * buf ;
 Atom ghostview_atom = XInternAtom ( xdev -> dpy , "GHOSTVIEW" , False ) ;
 if ( XGetWindowAttributes ( xdev -> dpy , xdev -> win , & attrib ) ) {
 xdev -> scr = attrib . screen ;
 xvinfo . visual = attrib . visual ;
 xdev -> cmap = attrib . colormap ;
 xdev -> width = attrib . width ;
 xdev -> height = attrib . height ;
 }
 if ( XGetWindowProperty ( xdev -> dpy , xdev -> win , ghostview_atom , 0 , 256 , ( xdev -> dest != 0 ) , XA_STRING , & type , & format , & nitems , & bytes_after , ( unsigned char * * ) & buf ) == 0 && type == XA_STRING ) {
 int llx , lly , urx , ury ;
 int left_margin = 0 , bottom_margin = 0 ;
 int right_margin = 0 , top_margin = 0 ;
 int page_orientation ;
 float xppp , yppp ;
 nitems = sscanf ( buf , "%ld %d %d %d %d %d %f %f %d %d %d %d" , & ( xdev -> bpixmap ) , & page_orientation , & llx , & lly , & urx , & ury , & ( xdev -> x_pixels_per_inch ) , & ( xdev -> y_pixels_per_inch ) , & left_margin , & bottom_margin , & right_margin , & top_margin ) ;
 if ( ! ( nitems == 8 || nitems == 12 ) ) {
 emprintf ( xdev -> memory , "Cannot get ghostview property.\n" ) ;
 return_error ( gs_error_ioerror ) ;
 }
 if ( xdev -> dest && xdev -> bpixmap ) {
 emprintf ( xdev -> memory , "Both destination and backing pixmap specified.\n" ) ;
 return_error ( gs_error_rangecheck ) ;
 }
 if ( xdev -> dest ) {
 Window root ;
 int x , y ;
 unsigned int width , height ;
 unsigned int border_width , depth ;
 if ( XGetGeometry ( xdev -> dpy , xdev -> dest , & root , & x , & y , & width , & height , & border_width , & depth ) ) {
 xdev -> width = width ;
 xdev -> height = height ;
 }
 }
 xppp = xdev -> x_pixels_per_inch / 72.0 ;
 yppp = xdev -> y_pixels_per_inch / 72.0 ;
 switch ( page_orientation ) {
 case Portrait : xdev -> initial_matrix . xx = xppp ;
 xdev -> initial_matrix . xy = 0.0 ;
 xdev -> initial_matrix . yx = 0.0 ;
 xdev -> initial_matrix . yy = - yppp ;
 xdev -> initial_matrix . tx = - llx * xppp ;
 xdev -> initial_matrix . ty = ury * yppp ;
 break ;
 case Landscape : xdev -> initial_matrix . xx = 0.0 ;
 xdev -> initial_matrix . xy = yppp ;
 xdev -> initial_matrix . yx = xppp ;
 xdev -> initial_matrix . yy = 0.0 ;
 xdev -> initial_matrix . tx = - lly * xppp ;
 xdev -> initial_matrix . ty = - llx * yppp ;
 break ;
 case Upsidedown : xdev -> initial_matrix . xx = - xppp ;
 xdev -> initial_matrix . xy = 0.0 ;
 xdev -> initial_matrix . yx = 0.0 ;
 xdev -> initial_matrix . yy = yppp ;
 xdev -> initial_matrix . tx = urx * xppp ;
 xdev -> initial_matrix . ty = - lly * yppp ;
 break ;
 case Seascape : xdev -> initial_matrix . xx = 0.0 ;
 xdev -> initial_matrix . xy = - yppp ;
 xdev -> initial_matrix . yx = - xppp ;
 xdev -> initial_matrix . yy = 0.0 ;
 xdev -> initial_matrix . tx = ury * xppp ;
 xdev -> initial_matrix . ty = urx * yppp ;
 break ;
 }
 xdev -> ImagingBBox [ 0 ] = llx - left_margin ;
 xdev -> ImagingBBox [ 1 ] = lly - bottom_margin ;
 xdev -> ImagingBBox [ 2 ] = urx + right_margin ;
 xdev -> ImagingBBox [ 3 ] = ury + top_margin ;
 xdev -> ImagingBBox_set = true ;
 }
 else if ( xdev -> pwin == ( Window ) None ) {
 emprintf ( xdev -> memory , "Cannot get ghostview property.\n" ) ;
 return_error ( gs_error_ioerror ) ;
 }
 }
 else {
 Screen * scr = DefaultScreenOfDisplay ( xdev -> dpy ) ;
 xdev -> scr = scr ;
 xvinfo . visual = DefaultVisualOfScreen ( scr ) ;
 xdev -> cmap = DefaultColormapOfScreen ( scr ) ;
 if ( xvinfo . visual -> class != TrueColor ) {
 int scrno = DefaultScreen ( xdev -> dpy ) ;
 if ( XMatchVisualInfo ( xdev -> dpy , scrno , 24 , TrueColor , & xvinfo ) || XMatchVisualInfo ( xdev -> dpy , scrno , 32 , TrueColor , & xvinfo ) || XMatchVisualInfo ( xdev -> dpy , scrno , 16 , TrueColor , & xvinfo ) || XMatchVisualInfo ( xdev -> dpy , scrno , 15 , TrueColor , & xvinfo ) ) {
 xdev -> cmap = XCreateColormap ( xdev -> dpy , DefaultRootWindow ( xdev -> dpy ) , xvinfo . visual , AllocNone ) ;
 }
 }
 }
 xvinfo . visualid = XVisualIDFromVisual ( xvinfo . visual ) ;
 xdev -> vinfo = XGetVisualInfo ( xdev -> dpy , VisualIDMask , & xvinfo , & nitems ) ;
 if ( xdev -> vinfo == NULL ) {
 emprintf ( xdev -> memory , "Cannot get XVisualInfo.\n" ) ;
 return_error ( gs_error_ioerror ) ;
 }
 x_error_handler . orighandler = XSetErrorHandler ( x_catch_free_colors ) ;
 XtToolkitInitialize ( ) ;
 app_con = XtCreateApplicationContext ( ) ;
 XtAppSetFallbackResources ( app_con , gdev_x_fallback_resources ) ;
 dpy = XtOpenDisplay ( app_con , NULL , "ghostscript" , "Ghostscript" , NULL , 0 , & zero , NULL ) ;
 toplevel = XtAppCreateShell ( NULL , "Ghostscript" , applicationShellWidgetClass , dpy , NULL , 0 ) ;
 XtGetApplicationResources ( toplevel , ( XtPointer ) xdev , gdev_x_resources , gdev_x_resource_count , NULL , 0 ) ;
 xc . pixel = xdev -> foreground ;
 XQueryColor ( xdev -> dpy , DefaultColormap ( xdev -> dpy , DefaultScreen ( xdev -> dpy ) ) , & xc ) ;
 XAllocColor ( xdev -> dpy , xdev -> cmap , & xc ) ;
 xdev -> foreground = xc . pixel ;
 xc . pixel = xdev -> background ;
 XQueryColor ( xdev -> dpy , DefaultColormap ( xdev -> dpy , DefaultScreen ( xdev -> dpy ) ) , & xc ) ;
 XAllocColor ( xdev -> dpy , xdev -> cmap , & xc ) ;
 xdev -> background = xc . pixel ;
 code = gdev_x_setup_colors ( xdev ) ;
 if ( code < 0 ) {
 XCloseDisplay ( xdev -> dpy ) ;
 return code ;
 }
 check_device_separable ( ( gx_device * ) xdev ) ;
 if ( ! xdev -> ghostview ) {
 XWMHints wm_hints ;
 XClassHint class_hint ;
 XSetWindowAttributes xswa ;
 gx_device * dev = ( gx_device * ) xdev ;
 if ( xdev -> x_pixels_per_inch == FAKE_RES || xdev -> y_pixels_per_inch == FAKE_RES ) {
 float xsize = ( float ) xdev -> width / xdev -> x_pixels_per_inch ;
 float ysize = ( float ) xdev -> height / xdev -> y_pixels_per_inch ;
 int workarea_width = WidthOfScreen ( xdev -> scr ) , workarea_height = HeightOfScreen ( xdev -> scr ) ;
 x_get_work_area ( xdev , & workarea_width , & workarea_height ) ;
 if ( xdev -> xResolution == 0.0 && xdev -> yResolution == 0.0 ) {
 float dpi , xdpi , ydpi ;
 xdpi = 25.4 * WidthOfScreen ( xdev -> scr ) / WidthMMOfScreen ( xdev -> scr ) ;
 ydpi = 25.4 * HeightOfScreen ( xdev -> scr ) / HeightMMOfScreen ( xdev -> scr ) ;
 dpi = min ( xdpi , ydpi ) ;
 if ( dpi < 30 ) dpi = 75 ;
 else {
 while ( xsize * dpi > WidthOfScreen ( xdev -> scr ) - 32 || ysize * dpi > HeightOfScreen ( xdev -> scr ) - 32 ) dpi *= 0.95 ;
 }
 xdev -> x_pixels_per_inch = dpi ;
 xdev -> y_pixels_per_inch = dpi ;
 }
 else {
 xdev -> x_pixels_per_inch = xdev -> xResolution ;
 xdev -> y_pixels_per_inch = xdev -> yResolution ;
 }
 if ( xdev -> width > workarea_width ) {
 xdev -> width = min ( xsize * xdev -> x_pixels_per_inch , workarea_width ) ;
 }
 if ( xdev -> height > workarea_height ) {
 xdev -> height = min ( ysize * xdev -> y_pixels_per_inch , workarea_height ) ;
 }
 xdev -> MediaSize [ 0 ] = ( float ) xdev -> width / xdev -> x_pixels_per_inch * 72 ;
 xdev -> MediaSize [ 1 ] = ( float ) xdev -> height / xdev -> y_pixels_per_inch * 72 ;
 }
 sizehints . x = 0 ;
 sizehints . y = 0 ;
 sizehints . width = xdev -> width ;
 sizehints . height = xdev -> height ;
 sizehints . flags = 0 ;
 if ( xdev -> geometry != NULL ) {
 char gstr [ 40 ] ;
 int bitmask ;
 gs_sprintf ( gstr , "%dx%d+%d+%d" , sizehints . width , sizehints . height , sizehints . x , sizehints . y ) ;
 bitmask = XWMGeometry ( xdev -> dpy , DefaultScreen ( xdev -> dpy ) , xdev -> geometry , gstr , xdev -> borderWidth , & sizehints , & sizehints . x , & sizehints . y , & sizehints . width , & sizehints . height , & sizehints . win_gravity ) ;
 if ( bitmask & ( XValue | YValue ) ) sizehints . flags |= USPosition ;
 }
 gx_default_get_initial_matrix ( dev , & ( xdev -> initial_matrix ) ) ;
 if ( xdev -> pwin != ( Window ) None && xid_width != 0 && xid_height != 0 ) {

 xdev -> initial_matrix . yy = xdev -> initial_matrix . yy * ( float ) xid_height / ( float ) xdev -> height ;

 xdev -> height = xid_height ;
 xdev -> initial_matrix . ty = xdev -> height ;
 }
 else {
 xswa . event_mask = ExposureMask ;
 xswa . background_pixel = xdev -> background ;
 xswa . border_pixel = xdev -> borderColor ;
 xswa . colormap = xdev -> cmap ;
 xdev -> win = XCreateWindow ( xdev -> dpy , RootWindowOfScreen ( xdev -> scr ) , sizehints . x , sizehints . y , xdev -> width , xdev -> height , xdev -> borderWidth , xdev -> vinfo -> depth , InputOutput , xdev -> vinfo -> visual , CWEventMask | CWBackPixel | CWBorderPixel | CWColormap , & xswa ) ;
 XStoreName ( xdev -> dpy , xdev -> win , "ghostscript" ) ;
 XSetWMNormalHints ( xdev -> dpy , xdev -> win , & sizehints ) ;
 wm_hints . flags = InputHint ;
 wm_hints . input = False ;
 XSetWMHints ( xdev -> dpy , xdev -> win , & wm_hints ) ;
 class_hint . res_name = ( char * ) "ghostscript" ;
 class_hint . res_class = ( char * ) "Ghostscript" ;
 XSetClassHint ( xdev -> dpy , xdev -> win , & class_hint ) ;
 }
 }
 XtDestroyWidget ( toplevel ) ;
 XtCloseDisplay ( dpy ) ;
 XtDestroyApplicationContext ( app_con ) ;
 xdev -> ht . pixmap = ( Pixmap ) 0 ;
 xdev -> ht . id = gx_no_bitmap_id ;
 ;
 xdev -> fill_style = FillSolid ;
 xdev -> function = GXcopy ;
 xdev -> fid = ( Font ) 0 ;
 xdev -> gc = XCreateGC ( xdev -> dpy , xdev -> win , 0 , ( XGCValues * ) NULL ) ;
 XSetFunction ( xdev -> dpy , xdev -> gc , GXcopy ) ;
 XSetLineAttributes ( xdev -> dpy , xdev -> gc , 0 , LineSolid , CapButt , JoinMiter ) ;
 gdev_x_clear_window ( xdev ) ;
 if ( ! xdev -> ghostview ) {
 XMapWindow ( xdev -> dpy , xdev -> win ) ;
 XSync ( xdev -> dpy , False ) ;
 if ( xdev -> pwin == ( Window ) None ) {
 XNextEvent ( xdev -> dpy , & event ) ;
 }
 XSetGraphicsExposures ( xdev -> dpy , xdev -> gc , False ) ;
 XSelectInput ( xdev -> dpy , xdev -> win , NoEventMask ) ;
 }
 else {
 XSetWindowAttributes attributes ;
 attributes . override_redirect = True ;
 xdev -> mwin = XCreateWindow ( xdev -> dpy , RootWindowOfScreen ( xdev -> scr ) , 0 , 0 , 1 , 1 , 0 , CopyFromParent , CopyFromParent , CopyFromParent , CWOverrideRedirect , & attributes ) ;
 xdev -> NEXT = XInternAtom ( xdev -> dpy , "NEXT" , False ) ;
 xdev -> PAGE = XInternAtom ( xdev -> dpy , "PAGE" , False ) ;
 xdev -> DONE = XInternAtom ( xdev -> dpy , "DONE" , False ) ;
 }
 xdev -> ht . no_pixmap = XCreatePixmap ( xdev -> dpy , xdev -> win , 1 , 1 , xdev -> vinfo -> depth ) ;
 return 0 ;
 }