void qdev_register ( DeviceInfo * info ) {
 assert ( info -> size >= sizeof ( DeviceState ) ) ;
 assert ( ! info -> next ) ;
 info -> next = device_info_list ;
 device_info_list = info ;
 }