static int dissect_h225_T_h323_message_body ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 h225_packet_info * h225_pi ;
 contains_faststart = FALSE ;
 call_id_guid = NULL ;
 offset = dissect_per_choice ( tvb , offset , actx , tree , hf_index , ett_h225_T_h323_message_body , T_h323_message_body_choice , & message_body_val ) ;
 col_append_fstr ( actx -> pinfo -> cinfo , COL_INFO , "CS: %s " , val_to_str ( message_body_val , T_h323_message_body_vals , "<unknown>" ) ) ;
 h225_pi = ( h225_packet_info * ) p_get_proto_data ( wmem_packet_scope ( ) , actx -> pinfo , proto_h225 , 0 ) ;
 if ( h225_pi != NULL ) {
 if ( h225_pi -> msg_type == H225_CS ) {
 h225_pi -> msg_tag = message_body_val ;
 }
 if ( call_id_guid ) {
 h225_pi -> guid = * call_id_guid ;
 }
 }
 if ( contains_faststart == TRUE ) {
 col_append_str ( actx -> pinfo -> cinfo , COL_INFO , "OpenLogicalChannel " ) ;
 }
 col_set_fence ( actx -> pinfo -> cinfo , COL_INFO ) ;
 return offset ;
 }