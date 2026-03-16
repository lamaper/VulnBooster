static vpx_codec_err_t encoder_destroy ( vpx_codec_alg_priv_t * ctx ) {
 free ( ctx -> cx_data ) ;
 vp9_remove_compressor ( ctx -> cpi ) ;
 vpx_free ( ctx ) ;
 return VPX_CODEC_OK ;
 }