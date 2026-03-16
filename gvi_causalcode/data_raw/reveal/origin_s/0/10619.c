static void dissect_dns_common ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gboolean is_tcp , gboolean is_mdns , gboolean is_llmnr ) {
 int offset = is_tcp ? 2 : 0 ;
 int dns_data_offset ;
 proto_tree * dns_tree = NULL , * field_tree ;
 proto_item * ti , * tf ;
 guint16 flags , opcode , rcode , quest , ans , auth , add ;
 guint id ;
 int cur_off ;
 gboolean isupdate ;
 conversation_t * conversation ;
 dns_conv_info_t * dns_info ;
 dns_transaction_t * dns_trans ;
 wmem_tree_key_t key [ 3 ] ;
 struct DnsTap * dns_stats ;
 guint qtype = 0 ;
 guint qclass = 0 ;
 const guchar * name ;
 int name_len ;
 dns_data_offset = offset ;
 col_clear ( pinfo -> cinfo , COL_INFO ) ;
 id = tvb_get_ntohs ( tvb , offset + DNS_ID ) ;
 flags = tvb_get_ntohs ( tvb , offset + DNS_FLAGS ) ;
 opcode = ( guint16 ) ( ( flags & F_OPCODE ) >> OPCODE_SHIFT ) ;
 rcode = ( guint16 ) ( flags & F_RCODE ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%s%s 0x%04x " , val_to_str ( opcode , opcode_vals , "Unknown operation (%u)" ) , ( flags & F_RESPONSE ) ? " response" : "" , id ) ;
 if ( flags & F_RESPONSE ) {
 if ( rcode != RCODE_NOERROR ) {
 col_append_str ( pinfo -> cinfo , COL_INFO , val_to_str ( rcode , rcode_vals , "Unknown error (%u)" ) ) ;
 }
 }
 if ( opcode == OPCODE_UPDATE ) {
 isupdate = TRUE ;
 }
 else {
 isupdate = FALSE ;
 }
 if ( tree ) {
 if ( is_llmnr ) {
 ti = proto_tree_add_protocol_format ( tree , proto_dns , tvb , 0 , - 1 , "Link-local Multicast Name Resolution (%s)" , ( flags & F_RESPONSE ) ? "response" : "query" ) ;
 }
 else {
 ti = proto_tree_add_protocol_format ( tree , proto_dns , tvb , 0 , - 1 , "Domain Name System (%s)" , ( flags & F_RESPONSE ) ? "response" : "query" ) ;
 }
 dns_tree = proto_item_add_subtree ( ti , ett_dns ) ;
 }
 conversation = find_or_create_conversation ( pinfo ) ;
 dns_info = ( dns_conv_info_t * ) conversation_get_proto_data ( conversation , proto_dns ) ;
 if ( ! dns_info ) {
 dns_info = wmem_new ( wmem_file_scope ( ) , dns_conv_info_t ) ;
 dns_info -> pdus = wmem_tree_new ( wmem_file_scope ( ) ) ;
 conversation_add_proto_data ( conversation , proto_dns , dns_info ) ;
 }
 key [ 0 ] . length = 1 ;
 key [ 0 ] . key = & id ;
 key [ 1 ] . length = 1 ;
 key [ 1 ] . key = & pinfo -> fd -> num ;
 key [ 2 ] . length = 0 ;
 key [ 2 ] . key = NULL ;
 if ( ! pinfo -> fd -> flags . visited ) {
 if ( ! ( flags & F_RESPONSE ) ) {
 dns_trans = wmem_new ( wmem_file_scope ( ) , dns_transaction_t ) ;
 dns_trans -> req_frame = pinfo -> fd -> num ;
 dns_trans -> rep_frame = 0 ;
 dns_trans -> req_time = pinfo -> fd -> abs_ts ;
 dns_trans -> id = id ;
 wmem_tree_insert32_array ( dns_info -> pdus , key , ( void * ) dns_trans ) ;
 }
 else {
 dns_trans = ( dns_transaction_t * ) wmem_tree_lookup32_array_le ( dns_info -> pdus , key ) ;
 if ( dns_trans ) {
 if ( dns_trans -> id != id ) {
 dns_trans = NULL ;
 }
 else {
 dns_trans -> rep_frame = pinfo -> fd -> num ;
 }
 }
 }
 }
 else {
 dns_trans = ( dns_transaction_t * ) wmem_tree_lookup32_array_le ( dns_info -> pdus , key ) ;
 if ( dns_trans && dns_trans -> id != id ) {
 dns_trans = NULL ;
 }
 }
 if ( ! dns_trans ) {
 dns_trans = wmem_new ( wmem_packet_scope ( ) , dns_transaction_t ) ;
 dns_trans -> req_frame = 0 ;
 dns_trans -> rep_frame = 0 ;
 dns_trans -> req_time = pinfo -> fd -> abs_ts ;
 }
 if ( ! ( flags & F_RESPONSE ) ) {
 if ( dns_trans -> rep_frame ) {
 proto_item * it ;
 it = proto_tree_add_uint ( dns_tree , hf_dns_response_in , tvb , 0 , 0 , dns_trans -> rep_frame ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 }
 }
 else {
 if ( dns_trans -> req_frame ) {
 proto_item * it ;
 nstime_t ns ;
 it = proto_tree_add_uint ( dns_tree , hf_dns_response_to , tvb , 0 , 0 , dns_trans -> req_frame ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 nstime_delta ( & ns , & pinfo -> fd -> abs_ts , & dns_trans -> req_time ) ;
 it = proto_tree_add_time ( dns_tree , hf_dns_time , tvb , 0 , 0 , & ns ) ;
 PROTO_ITEM_SET_GENERATED ( it ) ;
 }
 }
 if ( is_tcp ) {
 proto_tree_add_item ( dns_tree , hf_dns_length , tvb , offset - 2 , 2 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_uint ( dns_tree , hf_dns_transaction_id , tvb , offset + DNS_ID , 2 , id ) ;
 tf = proto_tree_add_item ( dns_tree , hf_dns_flags , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( tf , " %s" , val_to_str_const ( opcode , opcode_vals , "Unknown operation" ) ) ;
 if ( flags & F_RESPONSE ) {
 proto_item_append_text ( tf , " response, %s" , val_to_str_const ( rcode , rcode_vals , "Unknown error" ) ) ;
 }
 field_tree = proto_item_add_subtree ( tf , ett_dns_flags ) ;
 proto_tree_add_item ( field_tree , hf_dns_flags_response , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( field_tree , hf_dns_flags_opcode , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 if ( is_llmnr ) {
 if ( flags & F_RESPONSE ) {
 proto_tree_add_item ( field_tree , hf_dns_flags_conflict_response , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_item ( field_tree , hf_dns_flags_conflict_query , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( field_tree , hf_dns_flags_truncated , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( field_tree , hf_dns_flags_tentative , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 if ( flags & F_RESPONSE ) {
 proto_tree_add_item ( field_tree , hf_dns_flags_rcode , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 }
 }
 else {
 if ( flags & F_RESPONSE ) {
 proto_tree_add_item ( field_tree , hf_dns_flags_authoritative , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( field_tree , hf_dns_flags_truncated , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( field_tree , hf_dns_flags_recdesired , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 if ( flags & F_RESPONSE ) {
 proto_tree_add_item ( field_tree , hf_dns_flags_recavail , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( field_tree , hf_dns_flags_z , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 if ( flags & F_RESPONSE ) {
 proto_tree_add_item ( field_tree , hf_dns_flags_authenticated , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 }
 else if ( flags & F_AUTHENTIC ) {
 proto_tree_add_item ( field_tree , hf_dns_flags_ad , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 }
 proto_tree_add_item ( field_tree , hf_dns_flags_checkdisable , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 if ( flags & F_RESPONSE ) {
 proto_tree_add_item ( field_tree , hf_dns_flags_rcode , tvb , offset + DNS_FLAGS , 2 , ENC_BIG_ENDIAN ) ;
 }
 }
 quest = tvb_get_ntohs ( tvb , offset + DNS_QUEST ) ;
 if ( tree ) {
 if ( isupdate ) {
 proto_tree_add_uint ( dns_tree , hf_dns_count_zones , tvb , offset + DNS_QUEST , 2 , quest ) ;
 }
 else {
 proto_tree_add_uint ( dns_tree , hf_dns_count_questions , tvb , offset + DNS_QUEST , 2 , quest ) ;
 }
 }
 ans = tvb_get_ntohs ( tvb , offset + DNS_ANS ) ;
 if ( tree ) {
 if ( isupdate ) {
 proto_tree_add_uint ( dns_tree , hf_dns_count_prerequisites , tvb , offset + DNS_ANS , 2 , ans ) ;
 }
 else {
 proto_tree_add_uint ( dns_tree , hf_dns_count_answers , tvb , offset + DNS_ANS , 2 , ans ) ;
 }
 }
 auth = tvb_get_ntohs ( tvb , offset + DNS_AUTH ) ;
 if ( tree ) {
 if ( isupdate ) {
 proto_tree_add_uint ( dns_tree , hf_dns_count_updates , tvb , offset + DNS_AUTH , 2 , auth ) ;
 }
 else {
 proto_tree_add_uint ( dns_tree , hf_dns_count_auth_rr , tvb , offset + DNS_AUTH , 2 , auth ) ;
 }
 }
 add = tvb_get_ntohs ( tvb , offset + DNS_ADD ) ;
 if ( tree ) {
 proto_tree_add_uint ( dns_tree , hf_dns_count_add_rr , tvb , offset + DNS_ADD , 2 , add ) ;
 }
 cur_off = offset + DNS_HDRLEN ;
 dns_stats = wmem_new0 ( wmem_packet_scope ( ) , struct DnsTap ) ;
 dns_stats -> packet_rcode = rcode ;
 dns_stats -> packet_opcode = opcode ;
 dns_stats -> packet_qr = flags >> 15 ;
 get_dns_name_type_class ( tvb , cur_off , dns_data_offset , & name , & name_len , & qtype , & qclass ) ;
 dns_stats -> packet_qtype = qtype ;
 dns_stats -> packet_qclass = qclass ;
 dns_stats -> payload_size = tvb_captured_length ( tvb ) ;
 dns_stats -> nquestions = quest ;
 dns_stats -> nanswers = ans ;
 dns_stats -> nauthorities = auth ;
 dns_stats -> nadditionals = add ;
 if ( quest > 0 ) {
 cur_off += dissect_query_records ( tvb , cur_off , dns_data_offset , quest , ( ! ( flags & F_RESPONSE ) ? pinfo -> cinfo : NULL ) , dns_tree , isupdate , is_mdns ) ;
 dns_stats -> qname_len = name_len ;
 dns_stats -> qname_labels = qname_labels_count ( name , name_len ) ;
 }
 if ( ans > 0 ) {
 cur_off += dissect_answer_records ( tvb , cur_off , dns_data_offset , ans , ( ( flags & F_RESPONSE ) ? pinfo -> cinfo : NULL ) , dns_tree , ( isupdate ? "Prerequisites" : "Answers" ) , pinfo , is_mdns ) ;
 }
 if ( auth > 0 ) {
 cur_off += dissect_answer_records ( tvb , cur_off , dns_data_offset , auth , NULL , dns_tree , ( isupdate ? "Updates" : "Authoritative nameservers" ) , pinfo , is_mdns ) ;
 }
 if ( add > 0 ) {
 dissect_answer_records ( tvb , cur_off , dns_data_offset , add , NULL , dns_tree , "Additional records" , pinfo , is_mdns ) ;
 }
 tap_queue_packet ( dns_tap , pinfo , dns_stats ) ;
 }