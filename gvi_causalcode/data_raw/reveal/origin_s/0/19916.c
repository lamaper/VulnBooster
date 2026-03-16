static void netbios_data_first_middle_flags ( tvbuff_t * tvb , proto_tree * tree , int offset ) {
 proto_tree * field_tree ;
 proto_item * tf ;
 tf = proto_tree_add_item ( tree , hf_netb_flags , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 field_tree = proto_item_add_subtree ( tf , ett_netb_flags ) ;
 proto_tree_add_item ( field_tree , hf_netb_flags_ack , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( field_tree , hf_netb_flags_ack_expected , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( field_tree , hf_netb_flags_recv_cont_req , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 }