static void virtio_net_get_config ( VirtIODevice * vdev , uint8_t * config ) {
 VirtIONet * n = to_virtio_net ( vdev ) ;
 struct virtio_net_config netcfg ;
 stw_p ( & netcfg . status , n -> status ) ;
 memcpy ( netcfg . mac , n -> mac , ETH_ALEN ) ;
 memcpy ( config , & netcfg , sizeof ( netcfg ) ) ;
 }