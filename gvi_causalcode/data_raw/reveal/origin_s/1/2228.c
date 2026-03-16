static void virtio_balloon_handle_output ( VirtIODevice * vdev , VirtQueue * vq ) {
 VirtIOBalloon * s = to_virtio_balloon ( vdev ) ;
 VirtQueueElement elem ;
 MemoryRegionSection section ;
 while ( virtqueue_pop ( vq , & elem ) ) {
 size_t offset = 0 ;
 uint32_t pfn ;
 while ( iov_to_buf ( elem . out_sg , elem . out_num , & pfn , offset , 4 ) == 4 ) {
 ram_addr_t pa ;
 ram_addr_t addr ;
 pa = ( ram_addr_t ) ldl_p ( & pfn ) << VIRTIO_BALLOON_PFN_SHIFT ;
 offset += 4 ;
 section = memory_region_find ( get_system_memory ( ) , pa , 1 ) ;
 if ( ! section . size || ! memory_region_is_ram ( section . mr ) ) continue ;
 addr = section . offset_within_region ;
 balloon_page ( memory_region_get_ram_ptr ( section . mr ) + addr , ! ! ( vq == s -> dvq ) ) ;
 }
 virtqueue_push ( vq , & elem , offset ) ;
 virtio_notify ( vdev , vq ) ;
 }
 }