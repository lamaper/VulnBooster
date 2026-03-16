static void virtio_net_tx_bh ( void * opaque ) {
 VirtIONet * n = opaque ;
 int32_t ret ;
 assert ( n -> vdev . vm_running ) ;
 n -> tx_waiting = 0 ;
 if ( unlikely ( ! ( n -> vdev . status & VIRTIO_CONFIG_S_DRIVER_OK ) ) ) return ;
 ret = virtio_net_flush_tx ( n , n -> tx_vq ) ;
 if ( ret == - EBUSY ) {
 return ;
 }
 if ( ret >= n -> tx_burst ) {
 qemu_bh_schedule ( n -> tx_bh ) ;
 n -> tx_waiting = 1 ;
 return ;
 }
 virtio_queue_set_notification ( n -> tx_vq , 1 ) ;
 if ( virtio_net_flush_tx ( n , n -> tx_vq ) > 0 ) {
 virtio_queue_set_notification ( n -> tx_vq , 0 ) ;
 qemu_bh_schedule ( n -> tx_bh ) ;
 n -> tx_waiting = 1 ;
 }
 }