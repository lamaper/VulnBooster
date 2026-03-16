int x_catch_free_colors ( Display * dpy , XErrorEvent * err ) {
 if ( err -> request_code == X_FreeColors || x_error_handler . orighandler == x_catch_free_colors ) return 0 ;
 return x_error_handler . orighandler ( dpy , err ) ;
 }