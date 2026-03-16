static uint32_t virtio_net_get_features ( VirtIODevice * vdev , uint32_t features ) {
 VirtIONet * n = to_virtio_net ( vdev ) ;
 features |= ( 1 << VIRTIO_NET_F_MAC ) ;
 if ( peer_has_vnet_hdr ( n ) ) {
 tap_using_vnet_hdr ( n -> nic -> nc . peer , 1 ) ;
 }
 else {
 features &= ~ ( 0x1 << VIRTIO_NET_F_CSUM ) ;
 features &= ~ ( 0x1 << VIRTIO_NET_F_HOST_TSO4 ) ;
 features &= ~ ( 0x1 << VIRTIO_NET_F_HOST_TSO6 ) ;
 features &= ~ ( 0x1 << VIRTIO_NET_F_HOST_ECN ) ;
 features &= ~ ( 0x1 << VIRTIO_NET_F_GUEST_CSUM ) ;
 features &= ~ ( 0x1 << VIRTIO_NET_F_GUEST_TSO4 ) ;
 features &= ~ ( 0x1 << VIRTIO_NET_F_GUEST_TSO6 ) ;
 features &= ~ ( 0x1 << VIRTIO_NET_F_GUEST_ECN ) ;
 }
 if ( ! peer_has_vnet_hdr ( n ) || ! peer_has_ufo ( n ) ) {
 features &= ~ ( 0x1 << VIRTIO_NET_F_GUEST_UFO ) ;
 features &= ~ ( 0x1 << VIRTIO_NET_F_HOST_UFO ) ;
 }
 if ( ! n -> nic -> nc . peer || n -> nic -> nc . peer -> info -> type != NET_CLIENT_TYPE_TAP ) {
 return features ;
 }
 if ( ! tap_get_vhost_net ( n -> nic -> nc . peer ) ) {
 return features ;
 }
 return vhost_net_get_features ( tap_get_vhost_net ( n -> nic -> nc . peer ) , features ) ;
 }