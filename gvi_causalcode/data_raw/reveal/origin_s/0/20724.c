static void dissect_rsvp_call_id ( proto_tree * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int c_type ) {
 int type = 0 ;
 const char * str ;
 int offset2 = offset + 4 ;
 int offset3 , offset4 , len ;
 proto_tree * ti2 = NULL ;
 proto_item_set_text ( ti , "CALL-ID: " ) ;
 switch ( c_type ) {
 case 0 : proto_item_append_text ( ti , "Empty" ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , c_type , "Empty (%u)" , c_type ) ;
 if ( obj_length > 4 ) proto_tree_add_item ( rsvp_object_tree , hf_rsvp_call_id_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 case 1 : case 2 : type = tvb_get_guint8 ( tvb , offset2 ) ;
 if ( c_type == 1 ) {
 offset3 = offset2 + 4 ;
 len = obj_length - 16 ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , c_type , "1 (operator specific)" ) ;
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_call_id_address_type , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_call_id_reserved , tvb , offset2 + 1 , 3 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "Operator-Specific. Addr Type: %s. " , val_to_str ( type , address_type_vals , "Unknown (%u)" ) ) ;
 }
 else {
 offset3 = offset2 + 16 ;
 len = obj_length - 28 ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , c_type , "2 (globally unique)" ) ;
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_call_id_address_type , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 str = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset2 + 1 , 3 , ENC_ASCII ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_call_id_international_segment , tvb , offset2 + 1 , 3 , ENC_NA | ENC_ASCII ) ;
 proto_item_append_text ( ti , "Globally-Unique. Addr Type: %s. Intl Segment: %s. " , val_to_str ( type , address_type_vals , "Unknown (%u)" ) , str ) ;
 str = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset2 + 4 , 12 , ENC_ASCII ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_call_id_national_segment , tvb , offset2 + 4 , 12 , ENC_NA | ENC_ASCII ) ;
 proto_item_append_text ( ti , "Natl Segment: %s. " , str ) ;
 }
 switch ( type ) {
 case 1 : offset4 = offset3 + 4 ;
 str = tvb_ip_to_str ( tvb , offset3 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_CALL_ID_SRC_ADDR_IPV4 ] , tvb , offset3 , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case 2 : offset4 = offset3 + 16 ;
 str = tvb_ip6_to_str ( tvb , offset3 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_CALL_ID_SRC_ADDR_IPV6 ] , tvb , offset3 , 16 , ENC_NA ) ;
 break ;
 case 3 : offset4 = offset3 + 20 ;
 str = print_nsap_net ( tvb , offset3 , 20 ) ;
 proto_tree_add_string ( rsvp_object_tree , hf_rsvp_source_transport_network_addr , tvb , offset3 , 20 , str ) ;
 break ;
 case 4 : offset4 = offset3 + 6 ;
 str = tvb_ether_to_str ( tvb , offset3 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_callid_srcaddr_ether , tvb , offset3 , 6 , ENC_NA ) ;
 break ;
 case 0x7F : offset4 = offset3 + len ;
 str = tvb_bytes_to_str ( wmem_packet_scope ( ) , tvb , offset3 , len ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_callid_srcaddr_bytes , tvb , offset3 , len , ENC_NA ) ;
 break ;
 default : offset4 = offset3 + len ;
 str = "???" ;
 expert_add_info ( pinfo , ti2 , & ei_rsvp_call_id_address_type ) ;
 break ;
 }
 proto_item_append_text ( ti , "Src: %s. " , str ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_call_id_local_identifier , tvb , offset4 , 8 , ENC_NA ) ;
 proto_item_append_text ( ti , "Local ID: %s. " , tvb_bytes_to_str ( wmem_packet_scope ( ) , tvb , offset4 , 8 ) ) ;
 break ;
 default : proto_item_append_text ( ti , " Unknown" ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , c_type , "Unknown (%u)" , c_type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_call_id_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }