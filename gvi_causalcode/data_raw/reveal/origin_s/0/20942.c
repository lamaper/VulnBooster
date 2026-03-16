static void virtio_net_handle_tx_timer ( VirtIODevice * vdev , VirtQueue * vq ) {
 VirtIONet * n = to_virtio_net ( vdev ) ;
 if ( ! n -> vdev . vm_running ) {
 n -> tx_waiting = 1 ;
 return ;
 }
 if ( n -> tx_waiting ) {
 virtio_queue_set_notification ( vq , 1 ) ;
 qemu_del_timer ( n -> tx_timer ) ;
 n -> tx_waiting = 0 ;
 virtio_net_flush_tx ( n , vq ) ;
 }
 else {
 qemu_mod_timer ( n -> tx_timer , qemu_get_clock_ns ( vm_clock ) + n -> tx_timeout ) ;
 n -> tx_waiting = 1 ;
 virtio_queue_set_notification ( vq , 0 ) ;
 }
 }