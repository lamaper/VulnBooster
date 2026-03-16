h225ras_call_t * new_h225ras_call ( h225ras_call_info_key * h225ras_call_key , packet_info * pinfo , e_guid_t * guid , int category ) {
 h225ras_call_info_key * new_h225ras_call_key ;
 h225ras_call_t * h225ras_call = NULL ;
 new_h225ras_call_key = wmem_new ( wmem_file_scope ( ) , h225ras_call_info_key ) ;
 new_h225ras_call_key -> reqSeqNum = h225ras_call_key -> reqSeqNum ;
 new_h225ras_call_key -> conversation = h225ras_call_key -> conversation ;
 h225ras_call = wmem_new ( wmem_file_scope ( ) , h225ras_call_t ) ;
 h225ras_call -> req_num = pinfo -> num ;
 h225ras_call -> rsp_num = 0 ;
 h225ras_call -> requestSeqNum = h225ras_call_key -> reqSeqNum ;
 h225ras_call -> responded = FALSE ;
 h225ras_call -> next_call = NULL ;
 h225ras_call -> req_time = pinfo -> abs_ts ;
 h225ras_call -> guid = * guid ;
 g_hash_table_insert ( ras_calls [ category ] , new_h225ras_call_key , h225ras_call ) ;
 return h225ras_call ;
 }