static vpx_codec_err_t parse_layer_options_from_string ( SvcContext * svc_ctx , LAYER_OPTION_TYPE type , const char * input , int * option0 , int * option1 ) {
 int i ;
 vpx_codec_err_t res = VPX_CODEC_OK ;
 char * input_string ;
 char * token ;
 const char * delim = "," ;
 char * save_ptr ;
 if ( input == NULL || option0 == NULL || ( option1 == NULL && type == SCALE_FACTOR ) ) return VPX_CODEC_INVALID_PARAM ;
 input_string = strdup ( input ) ;
 token = strtok_r ( input_string , delim , & save_ptr ) ;
 for ( i = 0 ;
 i < svc_ctx -> spatial_layers ;
 ++ i ) {
 if ( token != NULL ) {
 res = extract_option ( type , token , option0 + i , option1 + i ) ;
 if ( res != VPX_CODEC_OK ) break ;
 token = strtok_r ( NULL , delim , & save_ptr ) ;
 }
 else {
 break ;
 }
 }
 if ( res == VPX_CODEC_OK && i != svc_ctx -> spatial_layers ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "svc: layer params type: %d %d values required, " "but only %d specified\n" , type , svc_ctx -> spatial_layers , i ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 }
 free ( input_string ) ;
 return res ;
 }