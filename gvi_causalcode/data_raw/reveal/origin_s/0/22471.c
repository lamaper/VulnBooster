static void ras_call_matching ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , h225_packet_info * pi ) {
 proto_item * hidden_item ;
 conversation_t * conversation = NULL ;
 h225ras_call_info_key h225ras_call_key ;
 h225ras_call_t * h225ras_call = NULL ;
 nstime_t delta ;
 guint msg_category ;
 if ( pi -> msg_type == H225_RAS && pi -> msg_tag < 21 ) {
 msg_category = pi -> msg_tag / 3 ;
 if ( pi -> msg_tag % 3 == 0 ) {
 conversation = find_or_create_conversation ( pinfo ) ;
 h225ras_call_key . reqSeqNum = pi -> requestSeqNum ;
 h225ras_call_key . conversation = conversation ;
 h225ras_call = find_h225ras_call ( & h225ras_call_key , msg_category ) ;
 if ( h225ras_call != NULL ) {
 do {
 if ( pinfo -> num == h225ras_call -> req_num ) {
 break ;
 }
 if ( h225ras_call -> next_call == NULL ) {
 if ( ( pinfo -> num > h225ras_call -> rsp_num && h225ras_call -> rsp_num != 0 && pinfo -> abs_ts . secs > ( h225ras_call -> req_time . secs + THRESHOLD_REPEATED_RESPONDED_CALL ) ) || ( pinfo -> num > h225ras_call -> req_num && h225ras_call -> rsp_num == 0 && pinfo -> abs_ts . secs > ( h225ras_call -> req_time . secs + THRESHOLD_REPEATED_NOT_RESPONDED_CALL ) ) ) {
 h225ras_call = append_h225ras_call ( h225ras_call , pinfo , & pi -> guid , msg_category ) ;
 }
 else {
 pi -> is_duplicate = TRUE ;
 hidden_item = proto_tree_add_uint ( tree , hf_h225_ras_dup , tvb , 0 , 0 , pi -> requestSeqNum ) ;
 PROTO_ITEM_SET_HIDDEN ( hidden_item ) ;
 }
 break ;
 }
 h225ras_call = h225ras_call -> next_call ;
 }
 while ( h225ras_call != NULL ) ;
 }
 else {
 h225ras_call = new_h225ras_call ( & h225ras_call_key , pinfo , & pi -> guid , msg_category ) ;
 }
 if ( h225ras_call && h225ras_call -> rsp_num != 0 ) {
 proto_item * ti = proto_tree_add_uint_format ( tree , hf_h225_ras_rsp_frame , tvb , 0 , 0 , h225ras_call -> rsp_num , "The response to this request is in frame %u" , h225ras_call -> rsp_num ) ;
 PROTO_ITEM_SET_GENERATED ( ti ) ;
 }
 }
 else {
 conversation = find_conversation ( pinfo -> num , & pinfo -> src , & pinfo -> dst , pinfo -> ptype , pinfo -> srcport , pinfo -> destport , 0 ) ;
 if ( conversation != NULL ) {
 h225ras_call_key . reqSeqNum = pi -> requestSeqNum ;
 h225ras_call_key . conversation = conversation ;
 h225ras_call = find_h225ras_call ( & h225ras_call_key , msg_category ) ;
 if ( h225ras_call ) {
 do {
 if ( pinfo -> num == h225ras_call -> rsp_num ) {
 break ;
 }
 if ( h225ras_call -> next_call == NULL ) {
 break ;
 }
 h225ras_call = h225ras_call -> next_call ;
 }
 while ( h225ras_call != NULL ) ;
 if ( ! h225ras_call ) {
 return ;
 }
 if ( msg_category == 3 || msg_category == 5 ) {
 pi -> guid = h225ras_call -> guid ;
 hidden_item = proto_tree_add_guid ( tree , hf_h225_guid , tvb , 0 , GUID_LEN , & pi -> guid ) ;
 PROTO_ITEM_SET_HIDDEN ( hidden_item ) ;
 }
 if ( h225ras_call -> rsp_num == 0 ) {
 h225ras_call -> rsp_num = pinfo -> num ;
 }
 else {
 if ( h225ras_call -> rsp_num != pinfo -> num ) {
 pi -> is_duplicate = TRUE ;
 hidden_item = proto_tree_add_uint ( tree , hf_h225_ras_dup , tvb , 0 , 0 , pi -> requestSeqNum ) ;
 PROTO_ITEM_SET_HIDDEN ( hidden_item ) ;
 }
 }
 if ( h225ras_call -> req_num != 0 ) {
 proto_item * ti ;
 h225ras_call -> responded = TRUE ;
 pi -> request_available = TRUE ;
 ti = proto_tree_add_uint_format ( tree , hf_h225_ras_req_frame , tvb , 0 , 0 , h225ras_call -> req_num , "This is a response to a request in frame %u" , h225ras_call -> req_num ) ;
 PROTO_ITEM_SET_GENERATED ( ti ) ;
 nstime_delta ( & delta , & pinfo -> abs_ts , & h225ras_call -> req_time ) ;
 pi -> delta_time = delta ;
 ti = proto_tree_add_time ( tree , hf_h225_ras_deltatime , tvb , 0 , 0 , & ( pi -> delta_time ) ) ;
 PROTO_ITEM_SET_GENERATED ( ti ) ;
 }
 }
 }
 }
 }
 }