static int virtio_balloon_load ( QEMUFile * f , void * opaque , int version_id ) {
 VirtIOBalloon * s = opaque ;
 int ret ;
 if ( version_id != 1 ) return - EINVAL ;
 ret = virtio_load ( & s -> vdev , f ) ;
 if ( ret ) {
 return ret ;
 }
 s -> num_pages = qemu_get_be32 ( f ) ;
 s -> actual = qemu_get_be32 ( f ) ;
 return 0 ;
 }