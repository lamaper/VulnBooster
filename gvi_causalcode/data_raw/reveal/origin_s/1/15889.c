vpx_codec_err_t vpx_svc_set_quantizers ( SvcContext * svc_ctx , const char * quantizers ) {
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || quantizers == NULL || si == NULL ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 strncpy ( si -> quantizers , quantizers , sizeof ( si -> quantizers ) ) ;
 si -> quantizers [ sizeof ( si -> quantizers ) - 1 ] = '\0' ;
 return VPX_CODEC_OK ;
 }