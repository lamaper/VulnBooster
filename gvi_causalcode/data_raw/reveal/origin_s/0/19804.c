static void dissect_ack_byte ( proto_tree * tree , tvbuff_t * tvb , int offset , packet_info * pinfo _U_ ) {
 proto_item * ack_item ;
 proto_tree * ack_tree ;

 ack_byte = tvb_get_guint8 ( tvb , offset ) ;

 ack_item = proto_tree_add_item ( tree , hf_cipsafety_ack_byte , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 ack_tree = proto_item_add_subtree ( ack_item , ett_cipsafety_ack_byte ) ;
 proto_tree_add_item ( ack_tree , hf_cipsafety_ack_byte_ping_count_reply , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( ack_tree , hf_cipsafety_ack_byte_reserved1 , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( ack_tree , hf_cipsafety_ack_byte_ping_response , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( ack_tree , hf_cipsafety_ack_byte_reserved2 , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( ack_tree , hf_cipsafety_ack_byte_parity_even , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 }