void do_device_del ( Monitor * mon , const QDict * qdict ) {
 const char * id = qdict_get_str ( qdict , "id" ) ;
 DeviceState * dev ;
 dev = qdev_find_recursive ( main_system_bus , id ) ;
 if ( NULL == dev ) {
 qemu_error ( "Device '%s' not found\n" , id ) ;
 return ;
 }
 qdev_unplug ( dev ) ;
 }