static int dissect_nlm_share ( tvbuff_t * tvb , int offset , packet_info * pinfo , proto_tree * tree , int version _U_ , rpc_call_info_value * civ ) {
 proto_item * lock_item = NULL ;
 proto_tree * lock_tree = NULL ;
 guint32 fh_hash ;
 offset = dissect_rpc_data ( tvb , tree , hf_nlm_cookie , offset ) ;
 if ( tree ) {
 lock_item = proto_tree_add_item ( tree , hf_nlm_share , tvb , offset , - 1 , ENC_NA ) ;
 if ( lock_item ) lock_tree = proto_item_add_subtree ( lock_item , ett_nlm_lock ) ;
 }
 offset = dissect_rpc_string ( tvb , lock_tree , hf_nlm_lock_caller_name , offset , NULL ) ;
 offset = dissect_nfs3_fh ( tvb , offset , pinfo , lock_tree , "fh" , & fh_hash , civ ) ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " FH:0x%08x" , fh_hash ) ;
 offset = dissect_rpc_data ( tvb , lock_tree , hf_nlm_lock_owner , offset ) ;
 offset = dissect_rpc_uint32 ( tvb , lock_tree , hf_nlm_share_mode , offset ) ;
 offset = dissect_rpc_uint32 ( tvb , lock_tree , hf_nlm_share_access , offset ) ;
 offset = dissect_rpc_bool ( tvb , tree , hf_nlm_reclaim , offset ) ;
 return offset ;
 }