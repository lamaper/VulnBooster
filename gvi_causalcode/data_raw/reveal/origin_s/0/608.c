void do_info_qdm ( Monitor * mon ) {
 DeviceInfo * info ;
 char msg [ 256 ] ;
 for ( info = device_info_list ;
 info != NULL ;
 info = info -> next ) {
 qdev_print_devinfo ( info , msg , sizeof ( msg ) ) ;
 monitor_printf ( mon , "%s\n" , msg ) ;
 }
 }