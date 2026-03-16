VirtIOS390Device * s390_virtio_bus_find_mem ( VirtIOS390Bus * bus , ram_addr_t mem ) {
 VirtIOS390Device * _dev ;
 DeviceState * dev ;
 QLIST_FOREACH ( dev , & bus -> bus . children , sibling ) {
 _dev = ( VirtIOS390Device * ) dev ;
 if ( _dev -> dev_offs == mem ) {
 return _dev ;
 }
 }
 return NULL ;
 }