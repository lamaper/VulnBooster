int qdev_init ( DeviceState * dev ) {
 int rc ;
 assert ( dev -> state == DEV_STATE_CREATED ) ;
 rc = dev -> info -> init ( dev , dev -> info ) ;
 if ( rc < 0 ) {
 qdev_free ( dev ) ;
 return rc ;
 }
 qemu_register_reset ( qdev_reset , dev ) ;
 if ( dev -> info -> vmsd ) vmstate_register ( - 1 , dev -> info -> vmsd , dev ) ;
 dev -> state = DEV_STATE_INITIALIZED ;
 return 0 ;
 }