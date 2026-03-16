static void qbus_print ( Monitor * mon , BusState * bus , int indent ) {
 struct DeviceState * dev ;
 qdev_printf ( "bus: %s\n" , bus -> name ) ;
 indent += 2 ;
 qdev_printf ( "type %s\n" , bus -> info -> name ) ;
 QLIST_FOREACH ( dev , & bus -> children , sibling ) {
 qdev_print ( mon , dev , indent ) ;
 }
 }