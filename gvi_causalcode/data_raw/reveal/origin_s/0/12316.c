const vpx_codec_cx_pkt_t * vpx_codec_get_cx_data ( vpx_codec_ctx_t * ctx , vpx_codec_iter_t * iter ) {
 const vpx_codec_cx_pkt_t * pkt = NULL ;
 if ( ctx ) {
 if ( ! iter ) ctx -> err = VPX_CODEC_INVALID_PARAM ;
 else if ( ! ctx -> iface || ! ctx -> priv ) ctx -> err = VPX_CODEC_ERROR ;
 else if ( ! ( ctx -> iface -> caps & VPX_CODEC_CAP_ENCODER ) ) ctx -> err = VPX_CODEC_INCAPABLE ;
 else pkt = ctx -> iface -> enc . get_cx_data ( get_alg_priv ( ctx ) , iter ) ;
 }
 if ( pkt && pkt -> kind == VPX_CODEC_CX_FRAME_PKT ) {
 vpx_codec_priv_t * const priv = ctx -> priv ;
 char * const dst_buf = ( char * ) priv -> enc . cx_data_dst_buf . buf ;
 if ( dst_buf && pkt -> data . raw . buf != dst_buf && pkt -> data . raw . sz + priv -> enc . cx_data_pad_before + priv -> enc . cx_data_pad_after <= priv -> enc . cx_data_dst_buf . sz ) {
 vpx_codec_cx_pkt_t * modified_pkt = & priv -> enc . cx_data_pkt ;
 memcpy ( dst_buf + priv -> enc . cx_data_pad_before , pkt -> data . raw . buf , pkt -> data . raw . sz ) ;
 * modified_pkt = * pkt ;
 modified_pkt -> data . raw . buf = dst_buf ;
 modified_pkt -> data . raw . sz += priv -> enc . cx_data_pad_before + priv -> enc . cx_data_pad_after ;
 pkt = modified_pkt ;
 }
 if ( dst_buf == pkt -> data . raw . buf ) {
 priv -> enc . cx_data_dst_buf . buf = dst_buf + pkt -> data . raw . sz ;
 priv -> enc . cx_data_dst_buf . sz -= pkt -> data . raw . sz ;
 }
 }
 return pkt ;
 }