static int dissect_nlm_gen_reply ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data ) {
 guint32 nlm_stat ;
 int offset = 0 ;
 if ( nlm_match_msgres ) {
 rpc_call_info_value * rpc_call = ( rpc_call_info_value * ) data ;
 if ( ( rpc_call -> proc == 12 ) || ( rpc_call -> proc == 13 ) || ( rpc_call -> proc == 14 ) || ( rpc_call -> proc == 15 ) ) {
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
 nlm_stat = tvb_get_ntohl ( tvb , offset ) ;
 if ( nlm_stat ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " %s" , val_to_str ( nlm_stat , names_nlm_stats , "Unknown Status (%u)" ) ) ;
 }
 offset = dissect_rpc_uint32 ( tvb , tree , hf_nlm_stat , offset ) ;
 return offset ;
 }