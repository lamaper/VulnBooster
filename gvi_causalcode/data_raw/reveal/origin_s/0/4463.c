static ram_addr_t s390_virtio_next_ring ( VirtIOS390Bus * bus ) {
 ram_addr_t r = bus -> next_ring ;
 bus -> next_ring += VIRTIO_RING_LEN ;
 return r ;
 }