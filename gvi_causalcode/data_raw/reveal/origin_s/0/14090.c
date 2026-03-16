static void virtio_net_handle_ctrl ( VirtIODevice * vdev , VirtQueue * vq ) {
 VirtIONet * n = to_virtio_net ( vdev ) ;
 struct virtio_net_ctrl_hdr ctrl ;
 virtio_net_ctrl_ack status = VIRTIO_NET_ERR ;
 VirtQueueElement elem ;
 while ( virtqueue_pop ( vq , & elem ) ) {
 if ( ( elem . in_num < 1 ) || ( elem . out_num < 1 ) ) {
 error_report ( "virtio-net ctrl missing headers" ) ;
 exit ( 1 ) ;
 }
 if ( elem . out_sg [ 0 ] . iov_len < sizeof ( ctrl ) || elem . in_sg [ elem . in_num - 1 ] . iov_len < sizeof ( status ) ) {
 error_report ( "virtio-net ctrl header not in correct element" ) ;
 exit ( 1 ) ;
 }
 ctrl . class = ldub_p ( elem . out_sg [ 0 ] . iov_base ) ;
 ctrl . cmd = ldub_p ( elem . out_sg [ 0 ] . iov_base + sizeof ( ctrl . class ) ) ;
 if ( ctrl . class == VIRTIO_NET_CTRL_RX_MODE ) status = virtio_net_handle_rx_mode ( n , ctrl . cmd , & elem ) ;
 else if ( ctrl . class == VIRTIO_NET_CTRL_MAC ) status = virtio_net_handle_mac ( n , ctrl . cmd , & elem ) ;
 else if ( ctrl . class == VIRTIO_NET_CTRL_VLAN ) status = virtio_net_handle_vlan_table ( n , ctrl . cmd , & elem ) ;
 stb_p ( elem . in_sg [ elem . in_num - 1 ] . iov_base , status ) ;
 virtqueue_push ( vq , & elem , sizeof ( status ) ) ;
 virtio_notify ( vdev , vq ) ;
 }
 }