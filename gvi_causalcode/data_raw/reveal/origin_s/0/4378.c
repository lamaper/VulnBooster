static void nlm_msg_res_match_cleanup ( void ) {
 g_hash_table_destroy ( nlm_msg_res_unmatched ) ;
 g_hash_table_destroy ( nlm_msg_res_matched ) ;
 }