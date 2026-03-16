static int virtio_net_handle_rx_mode ( VirtIONet * n , uint8_t cmd , VirtQueueElement * elem ) {
 uint8_t on ;
 if ( elem -> out_num != 2 || elem -> out_sg [ 1 ] . iov_len != sizeof ( on ) ) {
 error_report ( "virtio-net ctrl invalid rx mode command" ) ;
 exit ( 1 ) ;
 }
 on = ldub_p ( elem -> out_sg [ 1 ] . iov_base ) ;
 if ( cmd == VIRTIO_NET_CTRL_RX_MODE_PROMISC ) n -> promisc = on ;
 else if ( cmd == VIRTIO_NET_CTRL_RX_MODE_ALLMULTI ) n -> allmulti = on ;
 else if ( cmd == VIRTIO_NET_CTRL_RX_MODE_ALLUNI ) n -> alluni = on ;
 else if ( cmd == VIRTIO_NET_CTRL_RX_MODE_NOMULTI ) n -> nomulti = on ;
 else if ( cmd == VIRTIO_NET_CTRL_RX_MODE_NOUNI ) n -> nouni = on ;
 else if ( cmd == VIRTIO_NET_CTRL_RX_MODE_NOBCAST ) n -> nobcast = on ;
 else return VIRTIO_NET_ERR ;
 return VIRTIO_NET_OK ;
 }