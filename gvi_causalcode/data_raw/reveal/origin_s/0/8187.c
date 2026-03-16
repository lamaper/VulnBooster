DeviceState * qdev_create ( BusState * bus , const char * name ) {
 DeviceInfo * info ;
 DeviceState * dev ;
 if ( ! bus ) {
 if ( ! main_system_bus ) {
 main_system_bus = qbus_create ( & system_bus_info , NULL , "main-system-bus" ) ;
 }
 bus = main_system_bus ;
 }
 info = qdev_find_info ( bus -> info , name ) ;
 if ( ! info ) {
 hw_error ( "Unknown device '%s' for bus '%s'\n" , name , bus -> info -> name ) ;
 }
 dev = qemu_mallocz ( info -> size ) ;
 dev -> info = info ;
 dev -> parent_bus = bus ;
 qdev_prop_set_defaults ( dev , dev -> info -> props ) ;
 qdev_prop_set_defaults ( dev , dev -> parent_bus -> info -> props ) ;
 qdev_prop_set_globals ( dev ) ;
 QLIST_INSERT_HEAD ( & bus -> children , dev , sibling ) ;
 if ( qdev_hotplug ) {
 assert ( bus -> allow_hotplug ) ;
 dev -> hotplugged = 1 ;
 }
 dev -> state = DEV_STATE_CREATED ;
 return dev ;
 }