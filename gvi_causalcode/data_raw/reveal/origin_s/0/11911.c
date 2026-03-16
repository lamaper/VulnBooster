static int dissect_pcp_message_start ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int offset ) {
 proto_item * pcp_start_item ;
 proto_tree * pcp_start_tree ;
 guint32 status ;
 pcp_start_item = proto_tree_add_item ( tree , hf_pcp_start , tvb , 0 , - 1 , ENC_NA ) ;
 pcp_start_tree = proto_item_add_subtree ( pcp_start_item , ett_pcp ) ;
 col_append_str ( pinfo -> cinfo , COL_INFO , "[START]" ) ;
 status = tvb_get_ntohl ( tvb , offset ) ;
 proto_tree_add_item ( pcp_start_tree , hf_pcp_start_status , tvb , offset , 4 , ENC_BIG_ENDIAN ) ;
 offset += 4 ;
 if ( tvb_reported_length_remaining ( tvb , offset ) == 0 ) {
 if ( status == PCP_SECURE_ACK_SUCCESSFUL ) {
 expert_add_info ( pinfo , tree , & ei_pcp_ssl_upgrade ) ;
 ssl_starttls_ack ( find_dissector ( "ssl" ) , pinfo , pcp_handle ) ;
 }
 else {
 expert_add_info ( pinfo , tree , & ei_pcp_ssl_upgrade_failed ) ;
 }
 }
 else {
 proto_tree_add_item ( pcp_start_tree , hf_pcp_start_zero , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( pcp_start_tree , hf_pcp_start_version , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 proto_tree_add_item ( pcp_start_tree , hf_pcp_start_licensed , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 offset = dissect_pcp_partial_features ( tvb , pinfo , pcp_start_tree , offset ) ;
 }
 return offset ;
 }