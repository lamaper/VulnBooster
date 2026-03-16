static void nlm_msg_res_match_init ( void ) {
 nlm_msg_res_unmatched = g_hash_table_new_full ( nlm_msg_res_unmatched_hash , nlm_msg_res_unmatched_equal , NULL , nlm_msg_res_unmatched_value_destroy ) ;
 nlm_msg_res_matched = g_hash_table_new_full ( nlm_msg_res_matched_hash , nlm_msg_res_matched_equal , NULL , ( GDestroyNotify ) g_free ) ;
 }