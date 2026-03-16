static void virtio_net_handle_rx ( VirtIODevice * vdev , VirtQueue * vq ) {
 VirtIONet * n = to_virtio_net ( vdev ) ;
 qemu_flush_queued_packets ( & n -> nic -> nc ) ;
 qemu_notify_event ( ) ;
 }