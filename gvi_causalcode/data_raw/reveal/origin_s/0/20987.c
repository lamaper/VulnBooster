static int dns_stats_tree_packet ( stats_tree * st , packet_info * pinfo _U_ , epan_dissect_t * edt _U_ , const void * p ) {
 struct DnsTap * pi = ( struct DnsTap * ) p ;
 tick_stat_node ( st , st_str_packets , 0 , FALSE ) ;
 stats_tree_tick_pivot ( st , st_node_packet_qr , val_to_str ( pi -> packet_qr , dns_qr_vals , "Unknown qr (%d)" ) ) ;
 stats_tree_tick_pivot ( st , st_node_packet_qtypes , val_to_str ( pi -> packet_qtype , dns_types_description_vals , "Unknown packet type (%d)" ) ) ;
 stats_tree_tick_pivot ( st , st_node_packet_qclasses , val_to_str ( pi -> packet_qclass , dns_classes , "Unknown class (%d)" ) ) ;
 stats_tree_tick_pivot ( st , st_node_packet_rcodes , val_to_str ( pi -> packet_rcode , rcode_vals , "Unknown rcode (%d)" ) ) ;
 stats_tree_tick_pivot ( st , st_node_packet_opcodes , val_to_str ( pi -> packet_opcode , opcode_vals , "Unknown opcode (%d)" ) ) ;
 avg_stat_node_add_value ( st , st_str_packets_avg_size , 0 , FALSE , pi -> payload_size ) ;
 if ( pi -> packet_qr == 0 ) {
 avg_stat_node_add_value ( st , st_str_query_qname_len , 0 , FALSE , pi -> qname_len ) ;
 switch ( pi -> qname_labels ) {
 case 1 : tick_stat_node ( st , st_str_query_domains_l1 , 0 , FALSE ) ;
 break ;
 case 2 : tick_stat_node ( st , st_str_query_domains_l2 , 0 , FALSE ) ;
 break ;
 case 3 : tick_stat_node ( st , st_str_query_domains_l3 , 0 , FALSE ) ;
 break ;
 default : tick_stat_node ( st , st_str_query_domains_lmore , 0 , FALSE ) ;
 break ;
 }
 }
 else {
 avg_stat_node_add_value ( st , st_str_response_nquestions , 0 , FALSE , pi -> nquestions ) ;
 avg_stat_node_add_value ( st , st_str_response_nanswers , 0 , FALSE , pi -> nanswers ) ;
 avg_stat_node_add_value ( st , st_str_response_nauthorities , 0 , FALSE , pi -> nauthorities ) ;
 avg_stat_node_add_value ( st , st_str_response_nadditionals , 0 , FALSE , pi -> nadditionals ) ;
 }
 return 1 ;
 }