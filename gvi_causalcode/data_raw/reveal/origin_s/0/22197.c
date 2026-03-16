static long * x_get_win_property ( gx_device_X * xdev , const char * atom_name ) {
 Atom r_type = ( Atom ) 0 ;
 int r_format = 0 ;
 unsigned long count = 0 ;
 unsigned long bytes_remain ;
 unsigned char * prop ;
 if ( XGetWindowProperty ( xdev -> dpy , RootWindowOfScreen ( xdev -> scr ) , XInternAtom ( xdev -> dpy , atom_name , False ) , 0 , 4 , False , XA_CARDINAL , & r_type , & r_format , & count , & bytes_remain , & prop ) == Success && prop && r_type == XA_CARDINAL && r_format == 32 && count == 4 && bytes_remain == 0 ) return ( long * ) prop ;
 XFree ( prop ) ;
 return NULL ;
 }