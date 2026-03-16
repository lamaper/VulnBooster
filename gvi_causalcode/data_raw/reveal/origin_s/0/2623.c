static void nlm_print_msgres_request ( packet_info * pinfo , proto_tree * tree , tvbuff_t * tvb ) {
 nlm_msg_res_matched_data * md ;
 md = ( nlm_msg_res_matched_data * ) g_hash_table_lookup ( nlm_msg_res_matched , GINT_TO_POINTER ( pinfo -> fd -> num ) ) ;
 if ( md ) {
 proto_tree_add_uint ( tree , hf_nlm_reply_in , tvb , 0 , 0 , md -> rep_frame ) ;
 }
 }