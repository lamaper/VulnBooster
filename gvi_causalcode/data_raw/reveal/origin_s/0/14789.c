static int dissect_h245_IndicationMessage ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_choice ( tvb , offset , actx , tree , hf_index , ett_h245_IndicationMessage , IndicationMessage_choice , & value ) ;
 if ( h245_shorttypes == TRUE ) {
 col_prepend_fstr ( actx -> pinfo -> cinfo , COL_INFO , "%s " , val_to_str ( value , h245_IndicationMessage_short_vals , "<unknown>" ) ) ;
 }
 else {
 col_prepend_fstr ( actx -> pinfo -> cinfo , COL_INFO , "%s " , val_to_str ( value , h245_IndicationMessage_vals , "<unknown>" ) ) ;
 }
 col_set_fence ( actx -> pinfo -> cinfo , COL_INFO ) ;
 if ( h245_pi != NULL ) {
 if ( strlen ( h245_pi -> frame_label ) == 0 ) {
 g_snprintf ( h245_pi -> frame_label , 50 , "%s" , val_to_str ( value , h245_IndicationMessage_short_vals , "UKN" ) ) ;
 }
 g_strlcat ( h245_pi -> comment , val_to_str ( value , h245_IndicationMessage_vals , "<unknown>" ) , 50 ) ;
 }
 return offset ;
 }