static int s390_virtio_blk_init ( VirtIOS390Device * dev ) {
 VirtIODevice * vdev ;
 vdev = virtio_blk_init ( ( DeviceState * ) dev , dev -> dinfo ) ;
 if ( ! vdev ) {
 return - 1 ;
 }
 return s390_virtio_device_init ( dev , vdev ) ;
 }