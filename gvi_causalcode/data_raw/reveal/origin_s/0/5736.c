static void virtio_balloon_set_config ( VirtIODevice * vdev , const uint8_t * config_data ) {
 VirtIOBalloon * dev = to_virtio_balloon ( vdev ) ;
 struct virtio_balloon_config config ;
 memcpy ( & config , config_data , 8 ) ;
 dev -> actual = le32_to_cpu ( config . actual ) ;
 }