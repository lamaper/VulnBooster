int linux_udev_start_event_monitor ( void ) {
 int r ;
 assert ( udev_ctx == NULL ) ;
 udev_ctx = device : : udev_new ( ) ;
 if ( ! udev_ctx ) {
 usbi_err ( NULL , "could not create udev context" ) ;
 return LIBUSB_ERROR_OTHER ;
 }
 udev_monitor = device : : udev_monitor_new_from_netlink ( udev_ctx , "udev" ) ;
 if ( ! udev_monitor ) {
 usbi_err ( NULL , "could not initialize udev monitor" ) ;
 goto err_free_ctx ;
 }
 r = device : : udev_monitor_filter_add_match_subsystem_devtype ( udev_monitor , "usb" , 0 ) ;
 if ( r ) {
 usbi_err ( NULL , "could not initialize udev monitor filter for \"usb\" subsystem" ) ;
 goto err_free_monitor ;
 }
 if ( device : : udev_monitor_enable_receiving ( udev_monitor ) ) {
 usbi_err ( NULL , "failed to enable the udev monitor" ) ;
 goto err_free_monitor ;
 }
 udev_monitor_fd = device : : udev_monitor_get_fd ( udev_monitor ) ;
 r = fcntl ( udev_monitor_fd , F_GETFL ) ;
 if ( r == - 1 ) {
 usbi_err ( NULL , "getting udev monitor fd flags (%d)" , errno ) ;
 goto err_free_monitor ;
 }
 r = fcntl ( udev_monitor_fd , F_SETFL , r | O_NONBLOCK ) ;
 if ( r ) {
 usbi_err ( NULL , "setting udev monitor fd flags (%d)" , errno ) ;
 goto err_free_monitor ;
 }
 r = usbi_pipe ( udev_control_pipe ) ;
 if ( r ) {
 usbi_err ( NULL , "could not create udev control pipe" ) ;
 goto err_free_monitor ;
 }
 r = pthread_create ( & linux_event_thread , NULL , linux_udev_event_thread_main , NULL ) ;
 if ( r ) {
 usbi_err ( NULL , "creating hotplug event thread (%d)" , r ) ;
 goto err_close_pipe ;
 }
 return LIBUSB_SUCCESS ;
 err_close_pipe : close ( udev_control_pipe [ 0 ] ) ;
 close ( udev_control_pipe [ 1 ] ) ;
 err_free_monitor : device : : udev_monitor_unref ( udev_monitor ) ;
 udev_monitor = NULL ;
 udev_monitor_fd = - 1 ;
 err_free_ctx : device : : udev_unref ( udev_ctx ) ;
 udev_ctx = NULL ;
 return LIBUSB_ERROR_OTHER ;
 }