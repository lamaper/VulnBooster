static void virtio_net_tx_timer ( void * opaque ) {
 VirtIONet * n = opaque ;
 assert ( n -> vdev . vm_running ) ;
 n -> tx_waiting = 0 ;
 if ( ! ( n -> vdev . status & VIRTIO_CONFIG_S_DRIVER_OK ) ) return ;
 virtio_queue_set_notification ( n -> tx_vq , 1 ) ;
 virtio_net_flush_tx ( n , n -> tx_vq ) ;
 }