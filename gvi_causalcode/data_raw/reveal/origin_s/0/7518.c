static void dissect_rsvp_template_filter ( proto_item * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type , rsvp_conversation_info * rsvph ) {
 int offset2 = offset + 4 ;
 proto_item_set_text ( ti , "%s" , summary_template ( tvb , offset ) ) ;
 switch ( type ) {
 case 1 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "1 - IPv4" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_SENDER_IP ] , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_SENDER_PORT ] , tvb , offset2 + 6 , 2 , ENC_BIG_ENDIAN ) ;
 set_address_tvb ( & rsvph -> source , AT_IPv4 , 4 , tvb , offset2 ) ;
 rsvph -> udp_source_port = tvb_get_ntohs ( tvb , offset2 + 6 ) ;
 break ;
 case 2 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "2 - IPv6" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_template_filter_source_address_ipv6 , tvb , offset2 , 16 , ENC_NA ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_template_filter_source_port , tvb , offset2 + 18 , 2 , ENC_BIG_ENDIAN ) ;
 break ;
 case 7 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "7 - IPv4 LSP" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_SENDER_IP ] , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 if ( rsvp_class == RSVP_CLASS_SENDER_TEMPLATE ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_SENDER_SHORT_CALL_ID ] , tvb , offset2 + 4 , 2 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_SENDER_LSP_ID ] , tvb , offset2 + 6 , 2 , ENC_BIG_ENDIAN ) ;
 set_address_tvb ( & rsvph -> source , AT_IPv4 , 4 , tvb , offset2 ) ;
 rsvph -> udp_source_port = tvb_get_ntohs ( tvb , offset2 + 6 ) ;
 break ;
 case 8 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "8 - IPv6 LSP" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_SENDER_IP ] , tvb , offset2 , 16 , ENC_BIG_ENDIAN ) ;
 if ( rsvp_class == RSVP_CLASS_SENDER_TEMPLATE ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_SENDER_SHORT_CALL_ID ] , tvb , offset2 + 16 , 2 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_SENDER_LSP_ID ] , tvb , offset2 + 18 , 2 , ENC_BIG_ENDIAN ) ;
 set_address_tvb ( & rsvph -> source , AT_IPv6 , 16 , tvb , offset2 ) ;
 rsvph -> udp_source_port = tvb_get_ntohs ( tvb , offset2 + 18 ) ;
 break ;
 case 9 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "9 - IPv4 Aggregate" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_SENDER_IP ] , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 set_address_tvb ( & rsvph -> source , AT_IPv4 , 4 , tvb , offset2 ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_template_filter_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }