DeviceState * qdev_device_add ( QemuOpts * opts ) {
 const char * driver , * path , * id ;
 DeviceInfo * info ;
 DeviceState * qdev ;
 BusState * bus ;
 driver = qemu_opt_get ( opts , "driver" ) ;
 if ( ! driver ) {
 qemu_error ( "-device: no driver specified\n" ) ;
 return NULL ;
 }
 if ( strcmp ( driver , "?" ) == 0 ) {
 char msg [ 256 ] ;
 for ( info = device_info_list ;
 info != NULL ;
 info = info -> next ) {
 qdev_print_devinfo ( info , msg , sizeof ( msg ) ) ;
 qemu_error ( "%s\n" , msg ) ;
 }
 return NULL ;
 }
 info = qdev_find_info ( NULL , driver ) ;
 if ( ! info ) {
 qemu_error_new ( QERR_DEVICE_NOT_FOUND , driver ) ;
 return NULL ;
 }
 if ( info -> no_user ) {
 qemu_error ( "device \"%s\" can't be added via command line\n" , info -> name ) ;
 return NULL ;
 }
 path = qemu_opt_get ( opts , "bus" ) ;
 if ( path != NULL ) {
 bus = qbus_find ( path ) ;
 }
 else {
 bus = qbus_find_recursive ( main_system_bus , NULL , info -> bus_info ) ;
 }
 if ( ! bus ) {
 qemu_error ( "Did not find %s bus for %s\n" , path ? path : info -> bus_info -> name , info -> name ) ;
 return NULL ;
 }
 if ( qdev_hotplug && ! bus -> allow_hotplug ) {
 qemu_error ( "Bus %s does not support hotplugging\n" , bus -> name ) ;
 return NULL ;
 }
 qdev = qdev_create ( bus , driver ) ;
 id = qemu_opts_id ( opts ) ;
 if ( id ) {
 qdev -> id = id ;
 }
 if ( qemu_opt_foreach ( opts , set_property , qdev , 1 ) != 0 ) {
 qdev_free ( qdev ) ;
 return NULL ;
 }
 if ( qdev_init ( qdev ) < 0 ) {
 qemu_error ( "Error initializing device %s\n" , driver ) ;
 return NULL ;
 }
 qdev -> opts = opts ;
 return qdev ;
 }