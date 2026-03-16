int vpx_codec_pkt_list_add ( struct vpx_codec_pkt_list * list , const struct vpx_codec_cx_pkt * pkt ) {
 if ( list -> cnt < list -> max ) {
 list -> pkts [ list -> cnt ++ ] = * pkt ;
 return 0 ;
 }
 return 1 ;
 }