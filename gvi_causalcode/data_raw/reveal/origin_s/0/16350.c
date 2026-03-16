static void virtio_net_set_config ( VirtIODevice * vdev , const uint8_t * config ) {
 VirtIONet * n = to_virtio_net ( vdev ) ;
 struct virtio_net_config netcfg ;
 memcpy ( & netcfg , config , sizeof ( netcfg ) ) ;
 if ( memcmp ( netcfg . mac , n -> mac , ETH_ALEN ) ) {
 memcpy ( n -> mac , netcfg . mac , ETH_ALEN ) ;
 qemu_format_nic_info_str ( & n -> nic -> nc , n -> mac ) ;
 }
 }