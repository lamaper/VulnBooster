struct virtio_net_hdr * vmxnet_tx_pkt_get_vhdr ( struct VmxnetTxPkt * pkt ) {
 assert ( pkt ) ;
 return & pkt -> virt_hdr ;
 }