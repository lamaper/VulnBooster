static ssize_t virtio_net_receive ( VLANClientState * nc , const uint8_t * buf , size_t size ) {
 VirtIONet * n = DO_UPCAST ( NICState , nc , nc ) -> opaque ;
 struct virtio_net_hdr_mrg_rxbuf * mhdr = NULL ;
 size_t guest_hdr_len , offset , i , host_hdr_len ;
 if ( ! virtio_net_can_receive ( & n -> nic -> nc ) ) return - 1 ;
 guest_hdr_len = n -> mergeable_rx_bufs ? sizeof ( struct virtio_net_hdr_mrg_rxbuf ) : sizeof ( struct virtio_net_hdr ) ;
 host_hdr_len = n -> has_vnet_hdr ? sizeof ( struct virtio_net_hdr ) : 0 ;
 if ( ! virtio_net_has_buffers ( n , size + guest_hdr_len - host_hdr_len ) ) return 0 ;
 if ( ! receive_filter ( n , buf , size ) ) return size ;
 offset = i = 0 ;
 while ( offset < size ) {
 VirtQueueElement elem ;
 int len , total ;
 struct iovec sg [ VIRTQUEUE_MAX_SIZE ] ;
 total = 0 ;
 if ( virtqueue_pop ( n -> rx_vq , & elem ) == 0 ) {
 if ( i == 0 ) return - 1 ;
 error_report ( "virtio-net unexpected empty queue: " "i %zd mergeable %d offset %zd, size %zd, " "guest hdr len %zd, host hdr len %zd guest features 0x%x" , i , n -> mergeable_rx_bufs , offset , size , guest_hdr_len , host_hdr_len , n -> vdev . guest_features ) ;
 exit ( 1 ) ;
 }
 if ( elem . in_num < 1 ) {
 error_report ( "virtio-net receive queue contains no in buffers" ) ;
 exit ( 1 ) ;
 }
 if ( ! n -> mergeable_rx_bufs && elem . in_sg [ 0 ] . iov_len != guest_hdr_len ) {
 error_report ( "virtio-net header not in first element" ) ;
 exit ( 1 ) ;
 }
 memcpy ( & sg , & elem . in_sg [ 0 ] , sizeof ( sg [ 0 ] ) * elem . in_num ) ;
 if ( i == 0 ) {
 if ( n -> mergeable_rx_bufs ) mhdr = ( struct virtio_net_hdr_mrg_rxbuf * ) sg [ 0 ] . iov_base ;
 offset += receive_header ( n , sg , elem . in_num , buf + offset , size - offset , guest_hdr_len ) ;
 total += guest_hdr_len ;
 }
 len = iov_from_buf ( sg , elem . in_num , buf + offset , 0 , size - offset ) ;
 total += len ;
 offset += len ;
 if ( ! n -> mergeable_rx_bufs && offset < size ) {


 }
 virtqueue_fill ( n -> rx_vq , & elem , total , i ++ ) ;
 }
 if ( mhdr ) {
 stw_p ( & mhdr -> num_buffers , i ) ;
 }
 virtqueue_flush ( n -> rx_vq , i ) ;
 virtio_notify ( & n -> vdev , n -> rx_vq ) ;
 return size ;
 }