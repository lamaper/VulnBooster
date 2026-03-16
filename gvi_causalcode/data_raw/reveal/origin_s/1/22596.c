int linux_udev_scan_devices ( struct libusb_context * ctx ) {
 struct udev_enumerate * enumerator ;
 struct udev_list_entry * devices , * entry ;
 struct udev_device * udev_dev ;
 const char * sys_name ;
 int r ;
 assert ( udev_ctx != NULL ) ;
 enumerator = udev_enumerate_new ( udev_ctx ) ;
 if ( NULL == enumerator ) {
 usbi_err ( ctx , "error creating udev enumerator" ) ;
 return LIBUSB_ERROR_OTHER ;
 }
 udev_enumerate_add_match_subsystem ( enumerator , "usb" ) ;
 udev_enumerate_scan_devices ( enumerator ) ;
 devices = udev_enumerate_get_list_entry ( enumerator ) ;
 udev_list_entry_foreach ( entry , devices ) {
 const char * path = udev_list_entry_get_name ( entry ) ;
 uint8_t busnum = 0 , devaddr = 0 ;
 udev_dev = udev_device_new_from_syspath ( udev_ctx , path ) ;
 r = udev_device_info ( ctx , 0 , udev_dev , & busnum , & devaddr , & sys_name ) ;
 if ( r ) {
 udev_device_unref ( udev_dev ) ;
 continue ;
 }
 linux_enumerate_device ( ctx , busnum , devaddr , sys_name ) ;
 udev_device_unref ( udev_dev ) ;
 }
 udev_enumerate_unref ( enumerator ) ;
 return LIBUSB_SUCCESS ;
 }