void virtio_net_exit ( VirtIODevice * vdev ) {
 VirtIONet * n = DO_UPCAST ( VirtIONet , vdev , vdev ) ;
 virtio_net_set_status ( vdev , 0 ) ;
 qemu_purge_queued_packets ( & n -> nic -> nc ) ;
 unregister_savevm ( n -> qdev , "virtio-net" , n ) ;
 g_free ( n -> mac_table . macs ) ;
 g_free ( n -> vlans ) ;
 if ( n -> tx_timer ) {
 qemu_del_timer ( n -> tx_timer ) ;
 qemu_free_timer ( n -> tx_timer ) ;
 }
 else {
 qemu_bh_delete ( n -> tx_bh ) ;
 }
 qemu_del_vlan_client ( & n -> nic -> nc ) ;
 virtio_cleanup ( & n -> vdev ) ;
 }