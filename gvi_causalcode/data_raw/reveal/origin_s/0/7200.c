vpx_codec_err_t vpx_codec_enc_config_default ( vpx_codec_iface_t * iface , vpx_codec_enc_cfg_t * cfg , unsigned int usage ) {
 vpx_codec_err_t res ;
 vpx_codec_enc_cfg_map_t * map ;
 int i ;
 if ( ! iface || ! cfg || usage > INT_MAX ) res = VPX_CODEC_INVALID_PARAM ;
 else if ( ! ( iface -> caps & VPX_CODEC_CAP_ENCODER ) ) res = VPX_CODEC_INCAPABLE ;
 else {
 res = VPX_CODEC_INVALID_PARAM ;
 for ( i = 0 ;
 i < iface -> enc . cfg_map_count ;
 ++ i ) {
 map = iface -> enc . cfg_maps + i ;
 if ( map -> usage == ( int ) usage ) {
 * cfg = map -> cfg ;
 cfg -> g_usage = usage ;
 res = VPX_CODEC_OK ;
 break ;
 }
 }
 }
 return res ;
 }