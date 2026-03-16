static int dissect_nlm_test_res ( tvbuff_t * tvb , int offset , packet_info * pinfo _U_ , proto_tree * tree , int version , rpc_call_info_value * rpc_call ) {
 proto_item * lock_item = NULL ;
 proto_tree * lock_tree = NULL ;
 if ( nlm_match_msgres ) {
 if ( rpc_call -> proc == 11 ) {
 if ( ( ! pinfo -> fd -> flags . visited ) ) {
 nlm_register_unmatched_res ( pinfo , tvb , offset ) ;
 }
 else {
 nlm_print_msgres_reply ( pinfo , tree , tvb ) ;
 }
 if ( nfs_fhandle_reqrep_matching ) {
 nlm_match_fhandle_reply ( pinfo , tree ) ;
 }
 }
 }
 offset = dissect_rpc_data ( tvb , tree , hf_nlm_cookie , offset ) ;
 if ( tree ) {
 lock_item = proto_tree_add_item ( tree , hf_nlm_test_stat , tvb , offset , - 1 , ENC_NA ) ;
 lock_tree = proto_item_add_subtree ( lock_item , ett_nlm_lock ) ;
 }
 offset = dissect_rpc_uint32 ( tvb , lock_tree , hf_nlm_test_stat_stat , offset ) ;
 if ( tvb_reported_length_remaining ( tvb , offset ) == 0 ) {
 return offset ;
 }
 if ( tree ) {
 lock_item = proto_tree_add_item ( lock_tree , hf_nlm_holder , tvb , offset , - 1 , ENC_NA ) ;
 if ( lock_item ) lock_tree = proto_item_add_subtree ( lock_item , ett_nlm_lock ) ;
 }
 offset = dissect_rpc_bool ( tvb , lock_tree , hf_nlm_exclusive , offset ) ;
 offset = dissect_rpc_uint32 ( tvb , lock_tree , hf_nlm_lock_svid , offset ) ;
 offset = dissect_rpc_data ( tvb , lock_tree , hf_nlm_lock_owner , offset ) ;
 if ( version == 4 ) {
 offset = dissect_rpc_uint64 ( tvb , lock_tree , hf_nlm_lock_l_offset64 , offset ) ;
 offset = dissect_rpc_uint64 ( tvb , lock_tree , hf_nlm_lock_l_len64 , offset ) ;
 }
 else {
 offset = dissect_rpc_uint32 ( tvb , lock_tree , hf_nlm_lock_l_offset , offset ) ;
 offset = dissect_rpc_uint32 ( tvb , lock_tree , hf_nlm_lock_l_len , offset ) ;
 }
 return offset ;
 }