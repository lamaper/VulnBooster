static void x_get_work_area ( gx_device_X * xdev , int * pwidth , int * pheight ) {
 long * area ;
 if ( ( area = x_get_win_property ( xdev , "_NET_WORKAREA" ) ) != NULL || ( area = x_get_win_property ( xdev , "_WIN_WORKAREA" ) ) != NULL ) {
 * pwidth = area [ 2 ] ;
 * pheight = area [ 3 ] ;
 XFree ( area ) ;
 }
 }