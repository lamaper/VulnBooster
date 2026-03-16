static int virtio_net_can_receive ( VLANClientState * nc ) {
 VirtIONet * n = DO_UPCAST ( NICState , nc , nc ) -> opaque ;
 if ( ! n -> vdev . vm_running ) {
 return 0 ;
 }
 if ( ! virtio_queue_ready ( n -> rx_vq ) || ! ( n -> vdev . status & VIRTIO_CONFIG_S_DRIVER_OK ) ) return 0 ;
 return 1 ;
 }