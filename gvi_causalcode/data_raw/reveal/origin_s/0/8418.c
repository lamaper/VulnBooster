vpx_codec_err_t vpx_codec_set_cx_data_buf ( vpx_codec_ctx_t * ctx , const vpx_fixed_buf_t * buf , unsigned int pad_before , unsigned int pad_after ) {
 if ( ! ctx || ! ctx -> priv ) return VPX_CODEC_INVALID_PARAM ;
 if ( buf ) {
 ctx -> priv -> enc . cx_data_dst_buf = * buf ;
 ctx -> priv -> enc . cx_data_pad_before = pad_before ;
 ctx -> priv -> enc . cx_data_pad_after = pad_after ;
 }
 else {
 ctx -> priv -> enc . cx_data_dst_buf . buf = NULL ;
 ctx -> priv -> enc . cx_data_dst_buf . sz = 0 ;
 ctx -> priv -> enc . cx_data_pad_before = 0 ;
 ctx -> priv -> enc . cx_data_pad_after = 0 ;
 }
 return VPX_CODEC_OK ;
 }