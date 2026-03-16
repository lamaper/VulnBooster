BusState * qbus_create ( BusInfo * info , DeviceState * parent , const char * name ) {
 BusState * bus ;
 bus = qemu_mallocz ( info -> size ) ;
 bus -> qdev_allocated = 1 ;
 qbus_create_inplace ( bus , info , parent , name ) ;
 return bus ;
 }