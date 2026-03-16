static int s390_virtio_console_init ( VirtIOS390Device * dev ) {
 VirtIOS390Bus * bus ;
 VirtIODevice * vdev ;
 int r ;
 bus = DO_UPCAST ( VirtIOS390Bus , bus , dev -> qdev . parent_bus ) ;
 vdev = virtio_console_init ( ( DeviceState * ) dev ) ;
 if ( ! vdev ) {
 return - 1 ;
 }
 r = s390_virtio_device_init ( dev , vdev ) ;
 if ( ! r ) {
 bus -> console = dev ;
 }
 return r ;
 }