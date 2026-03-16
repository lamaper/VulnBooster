void s390_virtio_device_update_status ( VirtIOS390Device * dev ) {
 VirtIODevice * vdev = dev -> vdev ;
 uint32_t features ;
 vdev -> status = ldub_phys ( dev -> dev_offs + VIRTIO_DEV_OFFS_STATUS ) ;
 features = ldl_phys ( dev -> feat_offs ) ;
 if ( vdev -> set_features ) {
 vdev -> set_features ( vdev , features ) ;
 }
 vdev -> guest_features = features ;
 }