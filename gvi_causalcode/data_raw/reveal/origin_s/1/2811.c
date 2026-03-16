static void * linux_udev_event_thread_main ( void * arg ) {
 char dummy ;
 int r ;
 struct udev_device * udev_dev ;
 struct pollfd fds [ ] = {
 {
 . fd = udev_control_pipe [ 0 ] , . events = POLLIN }
 , {
 . fd = udev_monitor_fd , . events = POLLIN }
 , }
 ;
 usbi_dbg ( "udev event thread entering." ) ;
 while ( poll ( fds , 2 , - 1 ) >= 0 ) {
 if ( fds [ 0 ] . revents & POLLIN ) {
 r = usbi_read ( udev_control_pipe [ 0 ] , & dummy , sizeof ( dummy ) ) ;
 if ( r <= 0 ) {
 usbi_warn ( NULL , "udev control pipe read failed" ) ;
 }
 break ;
 }
 if ( fds [ 1 ] . revents & POLLIN ) {
 usbi_mutex_static_lock ( & linux_hotplug_lock ) ;
 udev_dev = udev_monitor_receive_device ( udev_monitor ) ;
 if ( udev_dev ) udev_hotplug_event ( udev_dev ) ;
 usbi_mutex_static_unlock ( & linux_hotplug_lock ) ;
 }
 }
 usbi_dbg ( "udev event thread exiting" ) ;
 return NULL ;
 }