const vpx_codec_cx_pkt_t * vpx_codec_pkt_list_get ( struct vpx_codec_pkt_list * list , vpx_codec_iter_t * iter ) {
 const vpx_codec_cx_pkt_t * pkt ;
 if ( ! ( * iter ) ) {
 * iter = list -> pkts ;
 }
 pkt = ( const vpx_codec_cx_pkt_t * ) * iter ;
 if ( ( size_t ) ( pkt - list -> pkts ) < list -> cnt ) * iter = pkt + 1 ;
 else pkt = NULL ;
 return pkt ;
 }