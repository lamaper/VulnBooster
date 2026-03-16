static int dissect_s_validator_type ( packet_info * pinfo , proto_tree * tree , proto_item * item , tvbuff_t * tvb , int offset , int total_len ) {
 proto_item * pi ;
 proto_tree * item_tree ;
 if ( total_len < 1 ) {
 expert_add_info ( pinfo , item , & ei_mal_svalidator_type ) ;
 return total_len ;
 }
 pi = proto_tree_add_item ( tree , hf_cip_svalidator_type , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 item_tree = proto_item_add_subtree ( pi , ett_svalidator_type ) ;
 proto_tree_add_item ( item_tree , hf_cip_svalidator_type_pc , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( item_tree , hf_cip_svalidator_type_conn_type , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 return 1 ;
 }