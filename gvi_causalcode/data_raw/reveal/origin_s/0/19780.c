vpx_codec_err_t vpx_codec_enc_config_set ( vpx_codec_ctx_t * ctx , const vpx_codec_enc_cfg_t * cfg ) {
 vpx_codec_err_t res ;
 if ( ! ctx || ! ctx -> iface || ! ctx -> priv || ! cfg ) res = VPX_CODEC_INVALID_PARAM ;
 else if ( ! ( ctx -> iface -> caps & VPX_CODEC_CAP_ENCODER ) ) res = VPX_CODEC_INCAPABLE ;
 else res = ctx -> iface -> enc . cfg_set ( get_alg_priv ( ctx ) , cfg ) ;
 return SAVE_STATUS ( ctx , res ) ;
 }