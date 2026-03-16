static int virtio_net_handle_vlan_table ( VirtIONet * n , uint8_t cmd , VirtQueueElement * elem ) {
 uint16_t vid ;
 if ( elem -> out_num != 2 || elem -> out_sg [ 1 ] . iov_len != sizeof ( vid ) ) {
 error_report ( "virtio-net ctrl invalid vlan command" ) ;
 return VIRTIO_NET_ERR ;
 }
 vid = lduw_p ( elem -> out_sg [ 1 ] . iov_base ) ;
 if ( vid >= MAX_VLAN ) return VIRTIO_NET_ERR ;
 if ( cmd == VIRTIO_NET_CTRL_VLAN_ADD ) n -> vlans [ vid >> 5 ] |= ( 1U << ( vid & 0x1f ) ) ;
 else if ( cmd == VIRTIO_NET_CTRL_VLAN_DEL ) n -> vlans [ vid >> 5 ] &= ~ ( 1U << ( vid & 0x1f ) ) ;
 else return VIRTIO_NET_ERR ;
 return VIRTIO_NET_OK ;
 }