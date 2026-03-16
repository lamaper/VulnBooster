h225ras_call_t * append_h225ras_call ( h225ras_call_t * prev_call , packet_info * pinfo , e_guid_t * guid , int category _U_ ) {
 h225ras_call_t * h225ras_call = NULL ;
 h225ras_call = wmem_new ( wmem_file_scope ( ) , h225ras_call_t ) ;
 h225ras_call -> req_num = pinfo -> num ;
 h225ras_call -> rsp_num = 0 ;
 h225ras_call -> requestSeqNum = prev_call -> requestSeqNum ;
 h225ras_call -> responded = FALSE ;
 h225ras_call -> next_call = NULL ;
 h225ras_call -> req_time = pinfo -> abs_ts ;
 h225ras_call -> guid = * guid ;
 prev_call -> next_call = h225ras_call ;
 return h225ras_call ;
 }