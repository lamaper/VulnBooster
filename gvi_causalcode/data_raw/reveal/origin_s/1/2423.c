int linux_udev_stop_event_monitor ( void ) {
 char dummy = 1 ;
 int r ;
 assert ( udev_ctx != NULL ) ;
 assert ( udev_monitor != NULL ) ;
 assert ( udev_monitor_fd != - 1 ) ;
 r = usbi_write ( udev_control_pipe [ 1 ] , & dummy , sizeof ( dummy ) ) ;
 if ( r <= 0 ) {
 usbi_warn ( NULL , "udev control pipe signal failed" ) ;
 }
 pthread_join ( linux_event_thread , NULL ) ;
 udev_monitor_unref ( udev_monitor ) ;
 udev_monitor = NULL ;
 udev_monitor_fd = - 1 ;
 udev_unref ( udev_ctx ) ;
 udev_ctx = NULL ;
 close ( udev_control_pipe [ 0 ] ) ;
 close ( udev_control_pipe [ 1 ] ) ;
 udev_control_pipe [ 0 ] = - 1 ;
 udev_control_pipe [ 1 ] = - 1 ;
 return LIBUSB_SUCCESS ;
 }