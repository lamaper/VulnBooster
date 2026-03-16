static vpx_codec_err_t parse_options ( SvcContext * svc_ctx , const char * options ) {
 char * input_string ;
 char * option_name ;
 char * option_value ;
 char * input_ptr ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 vpx_codec_err_t res = VPX_CODEC_OK ;
 int i , alt_ref_enabled = 0 ;
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
 res = parse_layer_options_from_string ( svc_ctx , SCALE_FACTOR , option_value , si -> svc_params . scaling_factor_num , si -> svc_params . scaling_factor_den ) ;
 if ( res != VPX_CODEC_OK ) break ;
 }
 else if ( strcmp ( "max-quantizers" , option_name ) == 0 ) {
 res = parse_layer_options_from_string ( svc_ctx , QUANTIZER , option_value , si -> svc_params . max_quantizers , NULL ) ;
 if ( res != VPX_CODEC_OK ) break ;
 }
 else if ( strcmp ( "min-quantizers" , option_name ) == 0 ) {
 res = parse_layer_options_from_string ( svc_ctx , QUANTIZER , option_value , si -> svc_params . min_quantizers , NULL ) ;
 if ( res != VPX_CODEC_OK ) break ;
 }
 else if ( strcmp ( "auto-alt-refs" , option_name ) == 0 ) {
 res = parse_layer_options_from_string ( svc_ctx , AUTO_ALT_REF , option_value , si -> enable_auto_alt_ref , NULL ) ;
 if ( res != VPX_CODEC_OK ) break ;
 }
 else if ( strcmp ( "bitrates" , option_name ) == 0 ) {
 res = parse_layer_options_from_string ( svc_ctx , BITRATE , option_value , si -> bitrates , NULL ) ;
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
 for ( i = 0 ;
 i < svc_ctx -> spatial_layers ;
 ++ i ) {
 if ( si -> svc_params . max_quantizers [ i ] > MAX_QUANTIZER || si -> svc_params . max_quantizers [ i ] < 0 || si -> svc_params . min_quantizers [ i ] > si -> svc_params . max_quantizers [ i ] || si -> svc_params . min_quantizers [ i ] < 0 ) res = VPX_CODEC_INVALID_PARAM ;
 }
 if ( si -> use_multiple_frame_contexts && ( svc_ctx -> spatial_layers > 3 || svc_ctx -> spatial_layers * svc_ctx -> temporal_layers > 4 ) ) res = VPX_CODEC_INVALID_PARAM ;
 for ( i = 0 ;
 i < svc_ctx -> spatial_layers ;
 ++ i ) alt_ref_enabled += si -> enable_auto_alt_ref [ i ] ;
 if ( alt_ref_enabled > REF_FRAMES - svc_ctx -> spatial_layers ) {
 svc_log ( svc_ctx , SVC_LOG_ERROR , "svc: auto alt ref: Maxinum %d(REF_FRAMES - layers) layers could" "enabled auto alt reference frame, but % layers are enabled\n" , REF_FRAMES - svc_ctx -> spatial_layers , alt_ref_enabled ) ;
 res = VPX_CODEC_INVALID_PARAM ;
 }
 return res ;
 }