static const vpx_codec_cx_pkt_t * encoder_get_cxdata ( vpx_codec_alg_priv_t * ctx , vpx_codec_iter_t * iter ) {
 return vpx_codec_pkt_list_get ( & ctx -> pkt_list . head , iter ) ;
 }