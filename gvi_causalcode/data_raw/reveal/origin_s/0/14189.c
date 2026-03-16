static void virtio_balloon_get_config ( VirtIODevice * vdev , uint8_t * config_data ) {
 VirtIOBalloon * dev = to_virtio_balloon ( vdev ) ;
 struct virtio_balloon_config config ;
 config . num_pages = cpu_to_le32 ( dev -> num_pages ) ;
 config . actual = cpu_to_le32 ( dev -> actual ) ;
 memcpy ( config_data , & config , 8 ) ;
 }