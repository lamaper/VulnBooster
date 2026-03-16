static int dissect_pcp_message_instance ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_instances_item ;
 proto_tree * pcp_instances_tree ;
 proto_item * pcp_instance_item ;
 proto_tree * pcp_instance_tree ;
 guint32 num_inst ;
 guint32 i ;
 guint32 name_len ;
 guint32 padding ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_INSTANCE , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_instances_item = proto_tree_add_item ( tree , hf_pcp_instances , tvb , offset , - 1 , ENC_NA ) ;
 pcp_instances_tree = proto_item_add_subtree ( pcp_instances_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_instances_tree , hf_pcp_instance_indom , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_instances_tree , hf_pcp_instances_numinst , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 num_inst = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < num_inst ;
 i ++ ) {
 name_len = tvb_get_ntohl ( tvb , offset + 4 ) ;
 pcp_instance_item = proto_tree_add_item ( pcp_instances_tree , hf_pcp_instance , tvb , offset , name_len + 8 , ENC_NA ) ;
 pcp_instance_tree = proto_item_add_subtree ( pcp_instance_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_instance_tree , hf_pcp_pmid_inst , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_instance_tree , hf_pcp_instance_namelen , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 if ( name_len > 0 ) {
 proto_tree_add_item ( pcp_instance_tree , hf_pcp_instance_name , tvb , offset , name_len , ENC_ASCII | ENC_NA ) ;
 offset += name_len ;
 }
 padding = name_len % 4 ;
 if ( padding != 0 ) {
 padding = 4 - padding ;
 proto_tree_add_item ( pcp_instance_tree , hf_pcp_pdu_padding , tvb , offset , padding , ENC_NA ) ;
 offset += padding ;
 }
 }
 return offset ;
 }