int gdev_x_close ( gx_device_X * xdev ) {
 if ( xdev -> ghostview ) gdev_x_send_event ( xdev , xdev -> DONE ) ;
 if ( xdev -> vinfo ) {
 XFree ( ( char * ) xdev -> vinfo ) ;
 xdev -> vinfo = NULL ;
 }
 gdev_x_free_colors ( xdev ) ;
 if ( xdev -> cmap != DefaultColormapOfScreen ( xdev -> scr ) ) XFreeColormap ( xdev -> dpy , xdev -> cmap ) ;
 if ( xdev -> gc ) XFreeGC ( xdev -> dpy , xdev -> gc ) ;
 XCloseDisplay ( xdev -> dpy ) ;
 return 0 ;
 }