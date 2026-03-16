static DeviceState * qdev_find_recursive ( BusState * bus , const char * id ) {
 DeviceState * dev , * ret ;
 BusState * child ;
 QLIST_FOREACH ( dev , & bus -> children , sibling ) {
 if ( dev -> id && strcmp ( dev -> id , id ) == 0 ) return dev ;
 QLIST_FOREACH ( child , & dev -> child_bus , sibling ) {
 ret = qdev_find_recursive ( child , id ) ;
 if ( ret ) {
 return ret ;
 }
 }
 }
 return NULL ;
 }