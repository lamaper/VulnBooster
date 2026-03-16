static vpx_codec_err_t parse_quantizer_values ( SvcContext * svc_ctx , const char * quantizer_values ) {
 char * input_string ;
 char * token ;
 const char * delim = "," ;
 char * save_ptr ;
 int found = 0 ;
 int i , q ;
 vpx_codec_err_t res = VPX_CODEC_OK ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( quantizer_values == NULL || strlen ( quantizer_values ) == 0 ) {
 input_string = strdup ( DEFAULT_QUANTIZER_VALUES ) ;
 }
 else {
 input_string = strdup ( quantizer_values ) ;
 }
 token = strtok_r ( input_string , delim , & save_ptr ) ;
 for ( i = 0 ;
 i < svc_ctx -> spatial_layers ;
 ++ i ) {
 if ( token != NULL ) {
 q = atoi ( token ) ;
 if ( q <= 0 || q > 100 ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "svc-quantizer-values: invalid value %s\n" , token ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 break ;
 }
 token = strtok_r ( NULL , delim , & save_ptr ) ;
 found = i + 1 ;
 }
 else {
 q = 0 ;
 }
 si -> quantizer [ i + VPX_SS_MAX_LAYERS - svc_ctx -> spatial_layers ] = q ;
 }
 if ( res == VPX_CODEC_OK && found != svc_ctx -> spatial_layers ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "svc: quantizers: %d values required, but only %d specified\n" , svc_ctx -> spatial_layers , found ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 }
 free ( input_string ) ;
 return res ;
 }