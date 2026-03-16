vpx_codec_err_t vpx_codec_enc_init_ver ( vpx_codec_ctx_t * ctx , vpx_codec_iface_t * iface , const vpx_codec_enc_cfg_t * cfg , vpx_codec_flags_t flags , int ver ) {
 vpx_codec_err_t res ;
 if ( ver != VPX_ENCODER_ABI_VERSION ) res = VPX_CODEC_ABI_MISMATCH ;
 else if ( ! ctx || ! iface || ! cfg ) res = VPX_CODEC_INVALID_PARAM ;
 else if ( iface -> abi_version != VPX_CODEC_INTERNAL_ABI_VERSION ) res = VPX_CODEC_ABI_MISMATCH ;
 else if ( ! ( iface -> caps & VPX_CODEC_CAP_ENCODER ) ) res = VPX_CODEC_INCAPABLE ;
 else if ( ( flags & VPX_CODEC_USE_PSNR ) && ! ( iface -> caps & VPX_CODEC_CAP_PSNR ) ) res = VPX_CODEC_INCAPABLE ;
 else if ( ( flags & VPX_CODEC_USE_OUTPUT_PARTITION ) && ! ( iface -> caps & VPX_CODEC_CAP_OUTPUT_PARTITION ) ) res = VPX_CODEC_INCAPABLE ;
 else {
 ctx -> iface = iface ;
 ctx -> name = iface -> name ;
 ctx -> priv = NULL ;
 ctx -> init_flags = flags ;
 ctx -> config . enc = cfg ;
 res = ctx -> iface -> init ( ctx , NULL ) ;
 if ( res ) {
 ctx -> err_detail = ctx -> priv ? ctx -> priv -> err_detail : NULL ;
 vpx_codec_destroy ( ctx ) ;
 }
 }
 return SAVE_STATUS ( ctx , res ) ;
 }