static vpx_codec_err_t parse_scale_factors ( SvcContext * svc_ctx , const char * scale_factors ) {
 char * input_string ;
 char * token ;
 const char * delim = "," ;
 char * save_ptr ;
 int found = 0 ;
 int i ;
 int64_t num , den ;
 vpx_codec_err_t res = VPX_CODEC_OK ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( scale_factors == NULL || strlen ( scale_factors ) == 0 ) {
 input_string = strdup ( DEFAULT_SCALE_FACTORS ) ;
 }
 else {
 input_string = strdup ( scale_factors ) ;
 }
 token = strtok_r ( input_string , delim , & save_ptr ) ;
 for ( i = 0 ;
 i < svc_ctx -> spatial_layers ;
 ++ i ) {
 num = den = 0 ;
 if ( token != NULL ) {
 num = strtol ( token , & token , 10 ) ;
 if ( num <= 0 ) {
 log_invalid_scale_factor ( svc_ctx , token ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 break ;
 }
 if ( * token ++ != '/' ) {
 log_invalid_scale_factor ( svc_ctx , token ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 break ;
 }
 den = strtol ( token , & token , 10 ) ;
 if ( den <= 0 ) {
 log_invalid_scale_factor ( svc_ctx , token ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 break ;
 }
 token = strtok_r ( NULL , delim , & save_ptr ) ;
 found = i + 1 ;
 }
 si -> scaling_factor_num [ i + VPX_SS_MAX_LAYERS - svc_ctx -> spatial_layers ] = ( int ) num ;
 si -> scaling_factor_den [ i + VPX_SS_MAX_LAYERS - svc_ctx -> spatial_layers ] = ( int ) den ;
 }
 if ( res == VPX_CODEC_OK && found != svc_ctx -> spatial_layers ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "svc: scale-factors: %d values required, but only %d specified\n" , svc_ctx -> spatial_layers , found ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 }
 free ( input_string ) ;
 return res ;
 }