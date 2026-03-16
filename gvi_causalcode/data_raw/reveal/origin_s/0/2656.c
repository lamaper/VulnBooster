static void virtio_net_set_features ( VirtIODevice * vdev , uint32_t features ) {
 VirtIONet * n = to_virtio_net ( vdev ) ;
 n -> mergeable_rx_bufs = ! ! ( features & ( 1 << VIRTIO_NET_F_MRG_RXBUF ) ) ;
 if ( n -> has_vnet_hdr ) {
 tap_set_offload ( n -> nic -> nc . peer , ( features >> VIRTIO_NET_F_GUEST_CSUM ) & 1 , ( features >> VIRTIO_NET_F_GUEST_TSO4 ) & 1 , ( features >> VIRTIO_NET_F_GUEST_TSO6 ) & 1 , ( features >> VIRTIO_NET_F_GUEST_ECN ) & 1 , ( features >> VIRTIO_NET_F_GUEST_UFO ) & 1 ) ;
 }
 if ( ! n -> nic -> nc . peer || n -> nic -> nc . peer -> info -> type != NET_CLIENT_TYPE_TAP ) {
 return ;
 }
 if ( ! tap_get_vhost_net ( n -> nic -> nc . peer ) ) {
 return ;
 }
 vhost_net_ack_features ( tap_get_vhost_net ( n -> nic -> nc . peer ) , features ) ;
 }