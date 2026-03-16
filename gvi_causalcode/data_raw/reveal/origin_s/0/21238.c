VirtIOS390Device * s390_virtio_bus_find_vring ( VirtIOS390Bus * bus , ram_addr_t mem , int * vq_num ) {
 VirtIOS390Device * _dev ;
 DeviceState * dev ;
 int i ;
 QLIST_FOREACH ( dev , & bus -> bus . children , sibling ) {
 _dev = ( VirtIOS390Device * ) dev ;
 for ( i = 0 ;
 i < VIRTIO_PCI_QUEUE_MAX ;
 i ++ ) {
 if ( ! virtio_queue_get_addr ( _dev -> vdev , i ) ) break ;
 if ( virtio_queue_get_addr ( _dev -> vdev , i ) == mem ) {
 if ( vq_num ) {
 * vq_num = i ;
 }
 return _dev ;
 }
 }
 }
 return NULL ;
 }