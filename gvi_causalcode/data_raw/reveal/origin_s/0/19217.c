void virtio_balloon_exit ( VirtIODevice * vdev ) {
 VirtIOBalloon * s = DO_UPCAST ( VirtIOBalloon , vdev , vdev ) ;
 qemu_remove_balloon_handler ( s ) ;
 unregister_savevm ( s -> qdev , "virtio-balloon" , s ) ;
 virtio_cleanup ( vdev ) ;
 }