static int dissect_pcp_message_profile ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_profile_item ;
 proto_tree * pcp_profile_tree ;
 proto_item * pcp_profile_profile_item ;
 proto_tree * pcp_profile_profile_tree ;
 guint32 num_prof ;
 guint32 i ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , "[%s]" , val_to_str ( PCP_PDU_PROFILE , packettypenames , "Unknown Type:0x%02x" ) ) ;
 pcp_profile_item = proto_tree_add_item ( tree , hf_pcp_profile , tvb , offset , - 1 , ENC_NA ) ;
 pcp_profile_tree = proto_item_add_subtree ( pcp_profile_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_profile_tree , hf_pcp_ctxnum , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_profile_tree , hf_pcp_profile_g_state , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_profile_tree , hf_pcp_profile_numprof , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 num_prof = tvb_get_ntohl ( tvb , offset ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_profile_tree , hf_pcp_pdu_padding , tvb , offset , 4 , ENC_NA ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < num_prof ;
 i ++ ) {
 pcp_profile_profile_item = proto_tree_add_item ( pcp_profile_tree , hf_pcp_profile_profile , tvb , offset , 32 , ENC_NA ) ;
 pcp_profile_profile_tree = proto_item_add_subtree ( pcp_profile_profile_item , ett_pcp ) ;
 proto_tree_add_item ( pcp_profile_profile_tree , hf_pcp_instance_indom , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_profile_profile_tree , hf_pcp_profile_profile_state , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_profile_profile_tree , hf_pcp_profile_profile_numinst , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( pcp_profile_tree , hf_pcp_pdu_padding , tvb , offset , 4 , ENC_NA ) ;
 offset += 4 ;
 }
 return offset ;
 }