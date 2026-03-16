static BusState * qbus_find_bus ( DeviceState * dev , char * elem ) {
 BusState * child ;
 QLIST_FOREACH ( child , & dev -> child_bus , sibling ) {
 if ( strcmp ( child -> name , elem ) == 0 ) {
 return child ;
 }
 }
 return NULL ;
 }