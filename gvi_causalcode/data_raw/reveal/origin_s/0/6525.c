static void virtio_net_set_link_status ( VLANClientState * nc ) {
 VirtIONet * n = DO_UPCAST ( NICState , nc , nc ) -> opaque ;
 uint16_t old_status = n -> status ;
 if ( nc -> link_down ) n -> status &= ~ VIRTIO_NET_S_LINK_UP ;
 else n -> status |= VIRTIO_NET_S_LINK_UP ;
 if ( n -> status != old_status ) virtio_notify_config ( & n -> vdev ) ;
 virtio_net_set_status ( & n -> vdev , n -> vdev . status ) ;
 }