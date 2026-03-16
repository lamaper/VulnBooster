const vpx_image_t * vpx_codec_get_preview_frame ( vpx_codec_ctx_t * ctx ) {
 vpx_image_t * img = NULL ;
 if ( ctx ) {
 if ( ! ctx -> iface || ! ctx -> priv ) ctx -> err = VPX_CODEC_ERROR ;
 else if ( ! ( ctx -> iface -> caps & VPX_CODEC_CAP_ENCODER ) ) ctx -> err = VPX_CODEC_INCAPABLE ;
 else if ( ! ctx -> iface -> enc . get_preview ) ctx -> err = VPX_CODEC_INCAPABLE ;
 else img = ctx -> iface -> enc . get_preview ( get_alg_priv ( ctx ) ) ;
 }
 return img ;
 }