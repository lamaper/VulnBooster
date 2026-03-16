vpx_codec_err_t vpx_svc_set_options ( SvcContext * svc_ctx , const char * options ) {
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( svc_ctx == NULL || options == NULL || si == NULL ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 strncpy ( si -> options , options , sizeof ( si -> options ) ) ;
 si -> options [ sizeof ( si -> options ) - 1 ] = '\0' ;
 return VPX_CODEC_OK ;
 }