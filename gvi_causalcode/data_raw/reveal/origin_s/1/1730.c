int dissect_h225_RasMessage ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 h225_packet_info * h225_pi ;
 call_id_guid = NULL ;
 offset = dissect_per_choice ( tvb , offset , actx , tree , hf_index , ett_h225_RasMessage , RasMessage_choice , & rasmessage_value ) ;
 col_add_fstr ( actx -> pinfo -> cinfo , COL_INFO , "RAS: %s " , val_to_str ( rasmessage_value , h225_RasMessage_vals , "<unknown>" ) ) ;
 h225_pi = ( h225_packet_info * ) p_get_proto_data ( wmem_packet_scope ( ) , actx -> pinfo , proto_h225 , 0 ) ;
 if ( h225_pi != NULL ) {
 h225_pi -> msg_tag = rasmessage_value ;
 if ( call_id_guid ) {
 h225_pi -> guid = * call_id_guid ;
 }
 }
 return offset ;
 }