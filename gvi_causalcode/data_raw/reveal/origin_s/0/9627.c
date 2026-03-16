static void dns_stats_tree_init ( stats_tree * st ) {
 st_node_packets = stats_tree_create_node ( st , st_str_packets , 0 , TRUE ) ;
 st_node_packet_qr = stats_tree_create_pivot ( st , st_str_packet_qr , st_node_packets ) ;
 st_node_packet_qtypes = stats_tree_create_pivot ( st , st_str_packet_qtypes , st_node_packets ) ;
 st_node_packet_qclasses = stats_tree_create_pivot ( st , st_str_packet_qclasses , st_node_packets ) ;
 st_node_packet_rcodes = stats_tree_create_pivot ( st , st_str_packet_rcodes , st_node_packets ) ;
 st_node_packet_opcodes = stats_tree_create_pivot ( st , st_str_packet_opcodes , st_node_packets ) ;
 st_node_packets_avg_size = stats_tree_create_node ( st , st_str_packets_avg_size , 0 , FALSE ) ;
 st_node_query_stats = stats_tree_create_node ( st , st_str_query_stats , 0 , TRUE ) ;
 st_node_query_qname_len = stats_tree_create_node ( st , st_str_query_qname_len , st_node_query_stats , FALSE ) ;
 st_node_query_domains = stats_tree_create_node ( st , st_str_query_domains , st_node_query_stats , TRUE ) ;
 st_node_query_domains_l1 = stats_tree_create_node ( st , st_str_query_domains_l1 , st_node_query_domains , FALSE ) ;
 st_node_query_domains_l2 = stats_tree_create_node ( st , st_str_query_domains_l2 , st_node_query_domains , FALSE ) ;
 st_node_query_domains_l3 = stats_tree_create_node ( st , st_str_query_domains_l3 , st_node_query_domains , FALSE ) ;
 st_node_query_domains_lmore = stats_tree_create_node ( st , st_str_query_domains_lmore , st_node_query_domains , FALSE ) ;
 st_node_response_stats = stats_tree_create_node ( st , st_str_response_stats , 0 , TRUE ) ;
 st_node_response_nquestions = stats_tree_create_node ( st , st_str_response_nquestions , st_node_response_stats , FALSE ) ;
 st_node_response_nanswers = stats_tree_create_node ( st , st_str_response_nanswers , st_node_response_stats , FALSE ) ;
 st_node_response_nauthorities = stats_tree_create_node ( st , st_str_response_nauthorities , st_node_response_stats , FALSE ) ;
 st_node_response_nadditionals = stats_tree_create_node ( st , st_str_response_nadditionals , st_node_response_stats , FALSE ) ;
 }