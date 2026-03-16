static int virtio_net_load ( QEMUFile * f , void * opaque , int version_id ) {
 VirtIONet * n = opaque ;
 int i ;
 int ret ;
 if ( version_id < 2 || version_id > VIRTIO_NET_VM_VERSION ) return - EINVAL ;
 ret = virtio_load ( & n -> vdev , f ) ;
 if ( ret ) {
 return ret ;
 }
 qemu_get_buffer ( f , n -> mac , ETH_ALEN ) ;
 n -> tx_waiting = qemu_get_be32 ( f ) ;
 n -> mergeable_rx_bufs = qemu_get_be32 ( f ) ;
 if ( version_id >= 3 ) n -> status = qemu_get_be16 ( f ) ;
 if ( version_id >= 4 ) {
 if ( version_id < 8 ) {
 n -> promisc = qemu_get_be32 ( f ) ;
 n -> allmulti = qemu_get_be32 ( f ) ;
 }
 else {
 n -> promisc = qemu_get_byte ( f ) ;
 n -> allmulti = qemu_get_byte ( f ) ;
 }
 }
 if ( version_id >= 5 ) {
 n -> mac_table . in_use = qemu_get_be32 ( f ) ;
 if ( n -> mac_table . in_use <= MAC_TABLE_ENTRIES ) {
 qemu_get_buffer ( f , n -> mac_table . macs , n -> mac_table . in_use * ETH_ALEN ) ;
 }
 else if ( n -> mac_table . in_use ) {
 qemu_fseek ( f , n -> mac_table . in_use * ETH_ALEN , SEEK_CUR ) ;
 n -> mac_table . multi_overflow = n -> mac_table . uni_overflow = 1 ;
 n -> mac_table . in_use = 0 ;
 }
 }
 if ( version_id >= 6 ) qemu_get_buffer ( f , ( uint8_t * ) n -> vlans , MAX_VLAN >> 3 ) ;
 if ( version_id >= 7 ) {
 if ( qemu_get_be32 ( f ) && ! peer_has_vnet_hdr ( n ) ) {
 error_report ( "virtio-net: saved image requires vnet_hdr=on" ) ;
 return - 1 ;
 }
 if ( n -> has_vnet_hdr ) {
 tap_using_vnet_hdr ( n -> nic -> nc . peer , 1 ) ;
 tap_set_offload ( n -> nic -> nc . peer , ( n -> vdev . guest_features >> VIRTIO_NET_F_GUEST_CSUM ) & 1 , ( n -> vdev . guest_features >> VIRTIO_NET_F_GUEST_TSO4 ) & 1 , ( n -> vdev . guest_features >> VIRTIO_NET_F_GUEST_TSO6 ) & 1 , ( n -> vdev . guest_features >> VIRTIO_NET_F_GUEST_ECN ) & 1 , ( n -> vdev . guest_features >> VIRTIO_NET_F_GUEST_UFO ) & 1 ) ;
 }
 }
 if ( version_id >= 9 ) {
 n -> mac_table . multi_overflow = qemu_get_byte ( f ) ;
 n -> mac_table . uni_overflow = qemu_get_byte ( f ) ;
 }
 if ( version_id >= 10 ) {
 n -> alluni = qemu_get_byte ( f ) ;
 n -> nomulti = qemu_get_byte ( f ) ;
 n -> nouni = qemu_get_byte ( f ) ;
 n -> nobcast = qemu_get_byte ( f ) ;
 }
 if ( version_id >= 11 ) {
 if ( qemu_get_byte ( f ) && ! peer_has_ufo ( n ) ) {
 error_report ( "virtio-net: saved image requires TUN_F_UFO support" ) ;
 return - 1 ;
 }
 }
 for ( i = 0 ;
 i < n -> mac_table . in_use ;
 i ++ ) {
 if ( n -> mac_table . macs [ i * ETH_ALEN ] & 1 ) {
 break ;
 }
 }
 n -> mac_table . first_multi = i ;
 return 0 ;
 }