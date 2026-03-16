static void virtio_net_tx_complete ( VLANClientState * nc , ssize_t len ) {
 VirtIONet * n = DO_UPCAST ( NICState , nc , nc ) -> opaque ;
 virtqueue_push ( n -> tx_vq , & n -> async_tx . elem , n -> async_tx . len ) ;
 virtio_notify ( & n -> vdev , n -> tx_vq ) ;
 n -> async_tx . elem . out_num = n -> async_tx . len = 0 ;
 virtio_queue_set_notification ( n -> tx_vq , 1 ) ;
 virtio_net_flush_tx ( n , n -> tx_vq ) ;
 }