static int x_catch_alloc ( Display * dpy , XErrorEvent * err ) {
 if ( err -> error_code == BadAlloc ) x_error_handler . alloc_error = True ;
 if ( x_error_handler . alloc_error ) return 0 ;
 return x_error_handler . oldhandler ( dpy , err ) ;
 }