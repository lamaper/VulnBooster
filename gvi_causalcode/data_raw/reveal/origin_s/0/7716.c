static vpx_codec_err_t ctrl_set_svc ( vpx_codec_alg_priv_t * ctx , va_list args ) {
 int data = va_arg ( args , int ) ;
 const vpx_codec_enc_cfg_t * cfg = & ctx -> cfg ;
 vp9_set_svc ( ctx -> cpi , data ) ;
 if ( data == 1 && ( cfg -> rc_end_usage == VPX_CBR || cfg -> g_pass == VPX_RC_FIRST_PASS || cfg -> g_pass == VPX_RC_LAST_PASS ) && cfg -> ss_number_layers > 1 && cfg -> ts_number_layers > 1 ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 return VPX_CODEC_OK ;
 }