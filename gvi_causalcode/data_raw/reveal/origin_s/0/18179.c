static int dissect_nlm_test ( tvbuff_t * tvb , int offset , packet_info * pinfo , proto_tree * tree , int version , rpc_call_info_value * rpc_call ) {
 if ( nlm_match_msgres ) {
 if ( rpc_call -> proc == 6 ) {
 if ( ( ! pinfo -> fd -> flags . visited ) ) {
 nlm_register_unmatched_msg ( pinfo , tvb , offset ) ;
 }
 else {
 nlm_print_msgres_request ( pinfo , tree , tvb ) ;
 }
 if ( nfs_fhandle_reqrep_matching ) {
 nlm_match_fhandle_request ( pinfo , tree ) ;
 }
 }
 }
 offset = dissect_rpc_data ( tvb , tree , hf_nlm_cookie , offset ) ;
 dissect_rpc_bool ( tvb , tree , hf_nlm_exclusive , offset ) ;
 offset += 4 ;
 offset = dissect_lock ( tvb , pinfo , tree , version , offset , rpc_call ) ;
 return offset ;
 }