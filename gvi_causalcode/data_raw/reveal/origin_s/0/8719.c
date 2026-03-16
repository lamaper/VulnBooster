int gdev_x_finish_copydevice ( gx_device * dev , const gx_device * from_dev ) {
 gx_device_X * xdev = ( gx_device_X * ) dev ;
 xdev -> is_open = false ;
 xdev -> target = 0 ;
 xdev -> buffer = 0 ;
 xdev -> dpy = 0 ;
 xdev -> scr = 0 ;
 xdev -> vinfo = 0 ;
 xdev -> win = ( Window ) None ;
 xdev -> bpixmap = ( Pixmap ) 0 ;
 xdev -> dest = ( Pixmap ) 0 ;
 xdev -> cp . pixmap = ( Pixmap ) 0 ;
 xdev -> ht . pixmap = ( Pixmap ) 0 ;
 xdev -> is_buffered = false ;
 set_dev_proc ( xdev , fill_rectangle , dev_proc ( & gs_x11_device , fill_rectangle ) ) ;
 return 0 ;
 }