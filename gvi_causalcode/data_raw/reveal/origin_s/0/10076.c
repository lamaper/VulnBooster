vpx_fixed_buf_t * vpx_codec_get_global_headers ( vpx_codec_ctx_t * ctx ) {
 vpx_fixed_buf_t * buf = NULL ;
 if ( ctx ) {
 if ( ! ctx -> iface || ! ctx -> priv ) ctx -> err = VPX_CODEC_ERROR ;
 else if ( ! ( ctx -> iface -> caps & VPX_CODEC_CAP_ENCODER ) ) ctx -> err = VPX_CODEC_INCAPABLE ;
 else if ( ! ctx -> iface -> enc . get_glob_hdrs ) ctx -> err = VPX_CODEC_INCAPABLE ;
 else buf = ctx -> iface -> enc . get_glob_hdrs ( get_alg_priv ( ctx ) ) ;
 }
 return buf ;
 }