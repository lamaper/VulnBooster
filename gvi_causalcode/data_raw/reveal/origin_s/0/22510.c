bool vmxnet_tx_pkt_parse ( struct VmxnetTxPkt * pkt ) {
 return vmxnet_tx_pkt_parse_headers ( pkt ) && vmxnet_tx_pkt_rebuild_payload ( pkt ) ;
 }