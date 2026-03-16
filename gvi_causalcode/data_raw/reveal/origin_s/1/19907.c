static void virtio_balloon_receive_stats ( VirtIODevice * vdev , VirtQueue * vq ) {
 VirtIOBalloon * s = DO_UPCAST ( VirtIOBalloon , vdev , vdev ) ;
 VirtQueueElement * elem = & s -> stats_vq_elem ;
 VirtIOBalloonStat stat ;
 size_t offset = 0 ;
 if ( ! virtqueue_pop ( vq , elem ) ) {
 return ;
 }
 reset_stats ( s ) ;
 while ( iov_to_buf ( elem -> out_sg , elem -> out_num , & stat , offset , sizeof ( stat ) ) == sizeof ( stat ) ) {
 uint16_t tag = tswap16 ( stat . tag ) ;
 uint64_t val = tswap64 ( stat . val ) ;
 offset += sizeof ( stat ) ;
 if ( tag < VIRTIO_BALLOON_S_NR ) s -> stats [ tag ] = val ;
 }
 s -> stats_vq_offset = offset ;
 }