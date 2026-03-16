static int dissect_lock ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , int version , int offset , rpc_call_info_value * civ ) {
 proto_item * lock_item = NULL ;
 proto_tree * lock_tree = NULL ;
 guint32 fh_hash , svid , start_offset = 0 , end_offset = 0 ;
 if ( tree ) {
 lock_item = proto_tree_add_item ( tree , hf_nlm_lock , tvb , offset , - 1 , ENC_NA ) ;
 if ( lock_item ) lock_tree = proto_item_add_subtree ( lock_item , ett_nlm_lock ) ;
 }
 offset = dissect_rpc_string ( tvb , lock_tree , hf_nlm_lock_caller_name , offset , NULL ) ;
 offset = dissect_nfs3_fh ( tvb , offset , pinfo , lock_tree , "fh" , & fh_hash , civ ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " FH:0x%08x" , fh_hash ) ;
 offset = dissect_rpc_data ( tvb , lock_tree , hf_nlm_lock_owner , offset ) ;
 svid = tvb_get_ntohl ( tvb , offset ) ;
 offset = dissect_rpc_uint32 ( tvb , lock_tree , hf_nlm_lock_svid , offset ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " svid:%d" , svid ) ;
 if ( version == 4 ) {
 start_offset = tvb_get_ntohl ( tvb , offset ) ;
 offset = dissect_rpc_uint64 ( tvb , lock_tree , hf_nlm_lock_l_offset64 , offset ) ;
 end_offset = tvb_get_ntohl ( tvb , offset ) ;
 offset = dissect_rpc_uint64 ( tvb , lock_tree , hf_nlm_lock_l_len64 , offset ) ;
 }
 else {
 start_offset = tvb_get_ntohl ( tvb , offset ) ;
 offset = dissect_rpc_uint32 ( tvb , lock_tree , hf_nlm_lock_l_offset , offset ) ;
 end_offset = tvb_get_ntohl ( tvb , offset ) ;
 offset = dissect_rpc_uint32 ( tvb , lock_tree , hf_nlm_lock_l_len , offset ) ;
 }
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " pos:%d-%d" , start_offset , end_offset ) ;
 return offset ;
 }