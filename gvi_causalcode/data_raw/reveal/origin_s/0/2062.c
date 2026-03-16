void gdev_x_clear_window ( gx_device_X * xdev ) {
 if ( ! xdev -> ghostview ) {
 if ( xdev -> useBackingPixmap ) {
 if ( xdev -> bpixmap == 0 ) {
 x_error_handler . oldhandler = XSetErrorHandler ( x_catch_alloc ) ;
 x_error_handler . alloc_error = False ;
 xdev -> bpixmap = XCreatePixmap ( xdev -> dpy , xdev -> win , xdev -> width , xdev -> height , xdev -> vinfo -> depth ) ;
 XSync ( xdev -> dpy , False ) ;
 if ( x_error_handler . alloc_error ) {
 xdev -> useBackingPixmap = False ;


 XFreePixmap ( xdev -> dpy , xdev -> bpixmap ) ;
 xdev -> bpixmap = None ;
 XSync ( xdev -> dpy , False ) ;
 }
 }
 x_error_handler . oldhandler = XSetErrorHandler ( x_error_handler . oldhandler ) ;
 }
 }
 else {
 if ( xdev -> bpixmap != 0 ) {
 XFreePixmap ( xdev -> dpy , xdev -> bpixmap ) ;
 xdev -> bpixmap = ( Pixmap ) 0 ;
 }
 }
 }
 x_set_buffer ( xdev ) ;
 if ( xdev -> dest == ( Pixmap ) 0 ) {
 xdev -> dest = ( xdev -> bpixmap != ( Pixmap ) 0 ? xdev -> bpixmap : ( Pixmap ) xdev -> win ) ;
 }
 if ( xdev -> dest != ( Pixmap ) 0 ) {
 XSetForeground ( xdev -> dpy , xdev -> gc , xdev -> background ) ;
 XFillRectangle ( xdev -> dpy , xdev -> dest , xdev -> gc , 0 , 0 , xdev -> width , xdev -> height ) ;
 }
 if ( xdev -> bpixmap != ( Pixmap ) 0 ) {
 if ( ! xdev -> ghostview ) XSetWindowBackgroundPixmap ( xdev -> dpy , xdev -> win , xdev -> bpixmap ) ;
 XSetForeground ( xdev -> dpy , xdev -> gc , xdev -> background ) ;
 XFillRectangle ( xdev -> dpy , xdev -> bpixmap , xdev -> gc , 0 , 0 , xdev -> width , xdev -> height ) ;
 }
 xdev -> back_color = xdev -> background ;
 XSetBackground ( xdev -> dpy , xdev -> gc , xdev -> background ) ;
 xdev -> fore_color = xdev -> background ;
 XSetForeground ( xdev -> dpy , xdev -> gc , xdev -> background ) ;
 xdev -> colors_or = xdev -> colors_and = xdev -> background ;
 }