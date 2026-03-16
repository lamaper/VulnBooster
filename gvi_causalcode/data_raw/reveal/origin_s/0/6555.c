static int s390_virtio_net_init ( VirtIOS390Device * dev ) {
 VirtIODevice * vdev ;
 vdev = virtio_net_init ( ( DeviceState * ) dev , & dev -> nic ) ;
 if ( ! vdev ) {
 return - 1 ;
 }
 return s390_virtio_device_init ( dev , vdev ) ;
 }