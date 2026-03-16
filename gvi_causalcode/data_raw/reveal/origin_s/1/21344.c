static vpx_codec_err_t parse_options ( SvcContext * svc_ctx , const char * options ) {
 char * input_string ;
 char * option_name ;
 char * option_value ;
 char * input_ptr ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 vpx_codec_err_t res = VPX_CODEC_OK ;
 if ( options == NULL ) return VPX_CODEC_OK ;
 input_string = strdup ( options ) ;
 option_name = strtok_r ( input_string , "=" , & input_ptr ) ;
 while ( option_name != NULL ) {
 option_value = strtok_r ( NULL , " " , & input_ptr ) ;
 if ( option_value == NULL ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "option missing value: %s\n" , option_name ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 break ;
 }
 if ( strcmp ( "spatial-layers" , option_name ) == 0 ) {
 svc_ctx -> spatial_layers = atoi ( option_value ) ;
 }
 else if ( strcmp ( "temporal-layers" , option_name ) == 0 ) {
 svc_ctx -> temporal_layers = atoi ( option_value ) ;
 }
 else if ( strcmp ( "scale-factors" , option_name ) == 0 ) {
 res = parse_scale_factors ( svc_ctx , option_value ) ;
 if ( res != VPX_CODEC_OK ) break ;
 }
 else if ( strcmp ( "quantizers" , option_name ) == 0 ) {
 res = parse_quantizer_values ( svc_ctx , option_value ) ;
 if ( res != VPX_CODEC_OK ) break ;
 }
 else if ( strcmp ( "auto-alt-refs" , option_name ) == 0 ) {
 res = parse_auto_alt_ref ( svc_ctx , option_value ) ;
 if ( res != VPX_CODEC_OK ) break ;
 }
 else if ( strcmp ( "multi-frame-contexts" , option_name ) == 0 ) {
 si -> use_multiple_frame_contexts = atoi ( option_value ) ;
 }
 else {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "invalid option: %s\n" , option_name ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 break ;
 }
 option_name = strtok_r ( NULL , "=" , & input_ptr ) ;
 }
 free ( input_string ) ;
 if ( si -> use_multiple_frame_contexts && ( svc_ctx -> spatial_layers > 3 || svc_ctx -> spatial_layers * svc_ctx -> temporal_layers > 4 ) ) res = VPX_CODEC_INVALID_PARAM ;
 return res ;
 }