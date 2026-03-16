static bool virtio_net_started ( VirtIONet * n , uint8_t status ) {
 return ( status & VIRTIO_CONFIG_S_DRIVER_OK ) && ( n -> status & VIRTIO_NET_S_LINK_UP ) && n -> vdev . vm_running ;
 }