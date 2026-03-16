static vpx_codec_err_t update_error_state ( vpx_codec_alg_priv_t * ctx , const struct vpx_internal_error_info * error ) {
 const vpx_codec_err_t res = error -> error_code ;
 if ( res != VPX_CODEC_OK ) ctx -> base . err_detail = error -> has_detail ? error -> detail : NULL ;
 return res ;
 }