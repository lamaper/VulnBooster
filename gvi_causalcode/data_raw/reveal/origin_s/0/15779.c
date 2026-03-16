static void virtio_balloon_save ( QEMUFile * f , void * opaque ) {
 VirtIOBalloon * s = opaque ;
 virtio_save ( & s -> vdev , f ) ;
 qemu_put_be32 ( f , s -> num_pages ) ;
 qemu_put_be32 ( f , s -> actual ) ;
 }