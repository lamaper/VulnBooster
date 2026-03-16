eth_pkt_types_e vmxnet_tx_pkt_get_packet_type ( struct VmxnetTxPkt * pkt ) {
 assert ( pkt ) ;
 return pkt -> packet_type ;
 }