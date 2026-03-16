static inline void reset_stats ( VirtIOBalloon * dev ) {
 int i ;
 for ( i = 0 ;
 i < VIRTIO_BALLOON_S_NR ;
 dev -> stats [ i ++ ] = - 1 ) ;
 }