static char * summary_template ( tvbuff_t * tvb , int offset ) {
 const char * objtype ;
 if ( tvb_get_guint8 ( tvb , offset + 2 ) == RSVP_CLASS_FILTER_SPEC ) objtype = "FILTERSPEC" ;
 else objtype = "SENDER TEMPLATE" ;
 switch ( tvb_get_guint8 ( tvb , offset + 3 ) ) {
 case 1 : return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s: IPv4, Sender %s, Port %d. " , objtype , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_get_ntohs ( tvb , offset + 10 ) ) ;
 break ;
 case 7 : return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s: IPv4-LSP, Tunnel Source: %s, Short Call ID: %d, LSP ID: %d. " , objtype , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_get_ntohs ( tvb , offset + 8 ) , tvb_get_ntohs ( tvb , offset + 10 ) ) ;
 break ;
 case 8 : return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s: IPv6-LSP, Tunnel Source: %s, Short Call ID: %d, LSP ID: %d. " , objtype , tvb_ip6_to_str ( tvb , offset + 4 ) , tvb_get_ntohs ( tvb , offset + 20 ) , tvb_get_ntohs ( tvb , offset + 22 ) ) ;
 break ;
 case 9 : return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s: IPv4-Aggregate, Aggregator %s. " , objtype , tvb_ip_to_str ( tvb , offset + 4 ) ) ;
 break ;
 default : return wmem_strdup_printf ( wmem_packet_scope ( ) , "%s: Type %d. " , objtype , tvb_get_guint8 ( tvb , offset + 3 ) ) ;
 break ;
 }
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }