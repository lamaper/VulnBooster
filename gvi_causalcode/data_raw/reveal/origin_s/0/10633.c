static uint32_t virtio_balloon_get_features ( VirtIODevice * vdev , uint32_t f ) {
 f |= ( 1 << VIRTIO_BALLOON_F_STATS_VQ ) ;
 return f ;
 }