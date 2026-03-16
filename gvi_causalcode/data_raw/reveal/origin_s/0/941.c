static uint64_t s390_virtio_device_vq_token ( VirtIOS390Device * dev , int vq ) {
 ram_addr_t token_off ;
 token_off = ( dev -> dev_offs + VIRTIO_DEV_OFFS_CONFIG ) + ( vq * VIRTIO_VQCONFIG_LEN ) + VIRTIO_VQCONFIG_OFFS_TOKEN ;
 return ldq_phys ( token_off ) ;
 }