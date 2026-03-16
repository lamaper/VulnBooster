static int receive_header ( VirtIONet * n , struct iovec * iov , int iovcnt , const void * buf , size_t size , size_t hdr_len ) {
 struct virtio_net_hdr * hdr = ( struct virtio_net_hdr * ) iov [ 0 ] . iov_base ;
 int offset = 0 ;
 hdr -> flags = 0 ;
 hdr -> gso_type = VIRTIO_NET_HDR_GSO_NONE ;
 if ( n -> has_vnet_hdr ) {
 memcpy ( hdr , buf , sizeof ( * hdr ) ) ;
 offset = sizeof ( * hdr ) ;
 work_around_broken_dhclient ( hdr , buf + offset , size - offset ) ;
 }
 iov [ 0 ] . iov_base += hdr_len ;
 iov [ 0 ] . iov_len -= hdr_len ;
 return offset ;
 }