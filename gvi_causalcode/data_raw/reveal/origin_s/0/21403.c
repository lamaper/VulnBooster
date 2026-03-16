static int dissect_h225_SetupAcknowledge_UUIE ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h225_SetupAcknowledge_UUIE , SetupAcknowledge_UUIE_sequence ) ;

 if ( h225_pi != NULL ) {
 h225_pi -> cs_type = H225_SETUP_ACK ;
 g_snprintf ( h225_pi -> frame_label , 50 , "%s" , val_to_str ( h225_pi -> cs_type , T_h323_message_body_vals , "<unknown>" ) ) ;
 }
 return offset ;
 }