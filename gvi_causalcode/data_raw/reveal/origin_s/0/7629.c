VirtIODevice * virtio_balloon_init ( DeviceState * dev ) {
 VirtIOBalloon * s ;
 int ret ;
 s = ( VirtIOBalloon * ) virtio_common_init ( "virtio-balloon" , VIRTIO_ID_BALLOON , 8 , sizeof ( VirtIOBalloon ) ) ;
 s -> vdev . get_config = virtio_balloon_get_config ;
 s -> vdev . set_config = virtio_balloon_set_config ;
 s -> vdev . get_features = virtio_balloon_get_features ;
 ret = qemu_add_balloon_handler ( virtio_balloon_to_target , virtio_balloon_stat , s ) ;
 if ( ret < 0 ) {
 virtio_cleanup ( & s -> vdev ) ;
 return NULL ;
 }
 s -> ivq = virtio_add_queue ( & s -> vdev , 128 , virtio_balloon_handle_output ) ;
 s -> dvq = virtio_add_queue ( & s -> vdev , 128 , virtio_balloon_handle_output ) ;
 s -> svq = virtio_add_queue ( & s -> vdev , 128 , virtio_balloon_receive_stats ) ;
 reset_stats ( s ) ;
 s -> qdev = dev ;
 register_savevm ( dev , "virtio-balloon" , - 1 , 1 , virtio_balloon_save , virtio_balloon_load , s ) ;
 return & s -> vdev ;
 }