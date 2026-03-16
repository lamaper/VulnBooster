static void virtio_net_cleanup ( VLANClientState * nc ) {
 VirtIONet * n = DO_UPCAST ( NICState , nc , nc ) -> opaque ;
 n -> nic = NULL ;
 }