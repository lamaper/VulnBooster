VirtIOS390Bus * s390_virtio_bus_init ( ram_addr_t * ram_size ) {
 VirtIOS390Bus * bus ;
 BusState * _bus ;
 DeviceState * dev ;
 dev = qdev_create ( NULL , "s390-virtio-bridge" ) ;
 qdev_init_nofail ( dev ) ;
 _bus = qbus_create ( & s390_virtio_bus_info , dev , "s390-virtio" ) ;
 bus = DO_UPCAST ( VirtIOS390Bus , bus , _bus ) ;
 bus -> dev_page = * ram_size ;
 bus -> dev_offs = bus -> dev_page ;
 bus -> next_ring = bus -> dev_page + TARGET_PAGE_SIZE ;
 * ram_size += S390_DEVICE_PAGES * TARGET_PAGE_SIZE ;
 return bus ;
 }