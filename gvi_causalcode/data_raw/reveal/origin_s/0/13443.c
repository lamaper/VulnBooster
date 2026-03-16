size_t vmxnet_tx_pkt_get_total_len ( struct VmxnetTxPkt * pkt ) {
 assert ( pkt ) ;
 return pkt -> hdr_len + pkt -> payload_len ;
 }