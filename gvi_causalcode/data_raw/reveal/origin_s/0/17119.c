static DeviceInfo * qdev_find_info ( BusInfo * bus_info , const char * name ) {
 DeviceInfo * info ;
 for ( info = device_info_list ;
 info != NULL ;
 info = info -> next ) {
 if ( bus_info && info -> bus_info != bus_info ) continue ;
 if ( strcmp ( info -> name , name ) != 0 ) continue ;
 return info ;
 }
 for ( info = device_info_list ;
 info != NULL ;
 info = info -> next ) {
 if ( bus_info && info -> bus_info != bus_info ) continue ;
 if ( ! info -> alias ) continue ;
 if ( strcmp ( info -> alias , name ) != 0 ) continue ;
 return info ;
 }
 return NULL ;
 }