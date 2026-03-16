static void udev_hotplug_event ( struct udev_device * udev_dev ) {
 const char * udev_action ;
 const char * sys_name = NULL ;
 uint8_t busnum = 0 , devaddr = 0 ;
 int detached ;
 int r ;
 do {
 udev_action = udev_device_get_action ( udev_dev ) ;
 if ( ! udev_action ) {
 break ;
 }
 detached = ! strncmp ( udev_action , "remove" , 6 ) ;
 r = udev_device_info ( NULL , detached , udev_dev , & busnum , & devaddr , & sys_name ) ;
 if ( LIBUSB_SUCCESS != r ) {
 break ;
 }
 usbi_dbg ( "udev hotplug event. action: %s." , udev_action ) ;
 if ( strncmp ( udev_action , "add" , 3 ) == 0 ) {
 linux_hotplug_enumerate ( busnum , devaddr , sys_name ) ;
 }
 else if ( detached ) {
 linux_device_disconnected ( busnum , devaddr , sys_name ) ;
 }
 else {
 usbi_err ( NULL , "ignoring udev action %s" , udev_action ) ;
 }
 }
 while ( 0 ) ;
 udev_device_unref ( udev_dev ) ;
 }