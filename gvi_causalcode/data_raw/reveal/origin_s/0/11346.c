static int dissect_pcp_message_result ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_results_item ;
 proto_tree * pcp_results_tree ;
 proto_item * pcp_result_item ;
 proto_tree * pcp_result_tree ;
 proto_item * pcp_result_instance_item ;
 proto_tree * pcp_result_instance_tree ;
 guint32 num_pmid ;
 guint32 num_val ;
 guint32 offset_start ;
 guint32 valfmt_type ;
 guint32 value_type ;
 guint32 pmvalueblock_offset ;
 guint32 pmvalueblock_value_length ;
 guint32 i ;
 guint32 j ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_RESULT , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_results_item = proto_tree_add_item ( tree , hf_pcp_results , tvb , offset , - 1 , ENC_NA ) ;
 pcp_results_tree = proto_item_add_subtree ( pcp_results_item , ett_pcp ) ;
 offset = dissect_pcp_partial_when ( tvb , pinfo , pcp_results_tree , offset ) ;
 proto_tree_add_item ( pcp_results_tree , hf_pcp_results_numpmid , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 num_pmid = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < num_pmid ;
 i ++ ) {
 offset_start = offset ;
 pcp_result_item = proto_tree_add_item ( pcp_results_tree , hf_pcp_result , tvb , offset , - 1 , ENC_NA ) ;
 pcp_result_tree = proto_item_add_subtree ( pcp_result_item , ett_pcp ) ;
 offset = dissect_pcp_partial_pmid ( tvb , pinfo , pcp_result_tree , offset ) ;
 proto_tree_add_item ( pcp_result_tree , hf_pcp_result_numval , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 num_val = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 if ( num_val > 0 ) {
 proto_tree_add_item ( pcp_result_tree , hf_pcp_result_valfmt , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 valfmt_type = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 for ( j = 0 ;
 j < num_val ;
 j ++ ) {
 pcp_result_instance_item = proto_tree_add_item ( pcp_result_tree , hf_pcp_instance , tvb , offset , 8 , ENC_NA ) ;
 pcp_result_instance_tree = proto_item_add_subtree ( pcp_result_instance_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_pmid_inst , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 if ( valfmt_type == PM_VAL_INSITU ) {
 proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_value_insitu , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_valoffset , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 pmvalueblock_offset = tvb_get_ntohl ( tvb , offset ) ;
 pmvalueblock_offset = pmvalueblock_offset * 4 ;
 value_type = tvb_get_guint8 ( tvb , pmvalueblock_offset ) ;
 proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_pmid_type , tvb , pmvalueblock_offset , 1 , ENC_BIG_ENDIAN ) ;
 pmvalueblock_offset += 1 ;
 pmvalueblock_value_length = tvb_get_ntoh24 ( tvb , pmvalueblock_offset ) ;
 proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_vallength , tvb , pmvalueblock_offset , 3 , ENC_BIG_ENDIAN ) ;
 pmvalueblock_offset += 3 ;
 switch ( value_type ) {
 case PM_TYPE_32 : proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_value_int , tvb , pmvalueblock_offset , pmvalueblock_value_length - 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case PM_TYPE_U32 : proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_value_uint , tvb , pmvalueblock_offset , pmvalueblock_value_length - 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case PM_TYPE_64 : proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_value_int64 , tvb , pmvalueblock_offset , pmvalueblock_value_length - 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case PM_TYPE_U64 : proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_value_uint64 , tvb , pmvalueblock_offset , pmvalueblock_value_length - 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case PM_TYPE_FLOAT : proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_value_float , tvb , pmvalueblock_offset , pmvalueblock_value_length - 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case PM_TYPE_DOUBLE : proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_value_double , tvb , pmvalueblock_offset , pmvalueblock_value_length - 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case PM_TYPE_STRING : proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_value_ptr , tvb , pmvalueblock_offset , pmvalueblock_value_length - 4 , ENC_ASCII | ENC_NA ) ;
 break ;
 case PM_TYPE_AGGREGATE : case PM_TYPE_AGGREGATE_STATIC : proto_tree_add_item ( pcp_result_instance_tree , hf_pcp_instance_value_aggr , tvb , pmvalueblock_offset , pmvalueblock_value_length - 4 , ENC_NA ) ;
 break ;
 case PM_TYPE_EVENT : expert_add_info ( pinfo , pcp_result_instance_tree , & ei_pcp_type_event_unimplemented ) ;
 break ;
 case PM_TYPE_NOSUPPORT : expert_add_info ( pinfo , pcp_result_instance_tree , & ei_pcp_type_nosupport_unsupported ) ;
 break ;
 case PM_TYPE_UNKNOWN : expert_add_info ( pinfo , pcp_result_instance_tree , & ei_pcp_type_unknown_unknown_value ) ;
 break ;
 default : expert_add_info ( pinfo , pcp_result_instance_tree , & ei_pcp_unimplemented_value ) ;
 break ;
 }
 }
 offset += 4 ;
 }
 }
 proto_item_set_len ( pcp_result_tree , offset - offset_start ) ;
 }
 return offset ;
 }