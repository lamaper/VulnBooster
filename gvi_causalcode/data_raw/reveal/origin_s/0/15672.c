static void nlm_print_msgres_reply ( packet_info * pinfo , proto_tree * tree , tvbuff_t * tvb ) {
 nlm_msg_res_matched_data * md ;
 md = ( nlm_msg_res_matched_data * ) g_hash_table_lookup ( nlm_msg_res_matched , GINT_TO_POINTER ( pinfo -> fd -> num ) ) ;
 if ( md ) {
 nstime_t ns ;
 proto_tree_add_uint ( tree , hf_nlm_request_in , tvb , 0 , 0 , md -> req_frame ) ;
 nstime_delta ( & ns , & pinfo -> fd -> abs_ts , & md -> ns ) ;
 proto_tree_add_time ( tree , hf_nlm_time , tvb , 0 , 0 , & ns ) ;
 }
 }