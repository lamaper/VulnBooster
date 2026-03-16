static vpx_codec_err_t parse_auto_alt_ref ( SvcContext * svc_ctx , const char * alt_ref_options ) {
 char * input_string ;
 char * token ;
 const char * delim = "," ;
 char * save_ptr ;
 int found = 0 , enabled = 0 ;
 int i , value ;
 vpx_codec_err_t res = VPX_CODEC_OK ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( alt_ref_options == NULL || strlen ( alt_ref_options ) == 0 ) {
 return VPX_CODEC_INVALID_PARAM ;
 }
 else {
 input_string = strdup ( alt_ref_options ) ;
 }
 token = strtok_r ( input_string , delim , & save_ptr ) ;
 for ( i = 0 ;
 i < svc_ctx -> spatial_layers ;
 ++ i ) {
 if ( token != NULL ) {
 value = atoi ( token ) ;
 if ( value < 0 || value > 1 ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "enable auto alt ref values: invalid value %s\n" , token ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 break ;
 }
 token = strtok_r ( NULL , delim , & save_ptr ) ;
 found = i + 1 ;
 }
 else {
 value = 0 ;
 }
 si -> enable_auto_alt_ref [ i ] = value ;
 if ( value > 0 ) ++ enabled ;
 }
 if ( res == VPX_CODEC_OK && found != svc_ctx -> spatial_layers ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "svc: quantizers: %d values required, but only %d specified\n" , svc_ctx -> spatial_layers , found ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 }
 if ( enabled > REF_FRAMES - svc_ctx -> spatial_layers ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "svc: auto alt ref: Maxinum %d(REF_FRAMES - layers) layers could" "enabled auto alt reference frame, but % layers are enabled\n" , REF_FRAMES - svc_ctx -> spatial_layers , enabled ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 }
 free ( input_string ) ;
 return res ;
 }