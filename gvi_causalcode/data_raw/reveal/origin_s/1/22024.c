vpx_codec_err_t vpx_svc_set_scale_factors ( SvcContext * svc_ctx , const char * scale_factors ) {
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || scale_factors == NULL || si == NULL ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 strncpy ( si -> scale_factors , scale_factors , sizeof ( si -> scale_factors ) ) ;
 si -> scale_factors [ sizeof ( si -> scale_factors ) - 1 ] = '\0' ;
 return VPX_CODEC_OK ;
 }