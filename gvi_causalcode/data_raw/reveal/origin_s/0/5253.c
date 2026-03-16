static char * summary_session ( tvbuff_t * tvb , int offset ) {
 switch ( tvb_get_guint8 ( tvb , offset + 3 ) ) {
 case RSVP_SESSION_TYPE_IPV4 : return wmem_strdup_printf ( wmem_packet_scope ( ) , "SESSION: IPv4, Destination %s, Protocol %d, Port %d. " , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_get_guint8 ( tvb , offset + 8 ) , tvb_get_ntohs ( tvb , offset + 10 ) ) ;
 break ;
 case RSVP_SESSION_TYPE_IPV4_LSP : return wmem_strdup_printf ( wmem_packet_scope ( ) , "SESSION: IPv4-LSP, Destination %s, Short Call ID %d, Tunnel ID %d, Ext ID %0x. " , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_get_ntohs ( tvb , offset + 8 ) , tvb_get_ntohs ( tvb , offset + 10 ) , tvb_get_ntohl ( tvb , offset + 12 ) ) ;
 break ;
 case RSVP_SESSION_TYPE_IPV6_LSP : return wmem_strdup_printf ( wmem_packet_scope ( ) , "SESSION: IPv6-LSP, Destination %s, Short Call ID %d, Tunnel ID %d, Ext ID %0x%0x%0x%0x. " , tvb_ip6_to_str ( tvb , offset + 4 ) , tvb_get_ntohs ( tvb , offset + 20 ) , tvb_get_ntohs ( tvb , offset + 22 ) , tvb_get_ntohl ( tvb , offset + 24 ) , tvb_get_ntohl ( tvb , offset + 28 ) , tvb_get_ntohl ( tvb , offset + 32 ) , tvb_get_ntohl ( tvb , offset + 36 ) ) ;
 case RSVP_SESSION_TYPE_AGGREGATE_IPV4 : return wmem_strdup_printf ( wmem_packet_scope ( ) , "SESSION: IPv4-Aggregate, Destination %s, DSCP %d. " , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_get_guint8 ( tvb , offset + 11 ) ) ;
 break ;
 case RSVP_SESSION_TYPE_IPV4_UNI : return wmem_strdup_printf ( wmem_packet_scope ( ) , "SESSION: IPv4-UNI, Destination %s, Tunnel ID %d, Ext Address %s. " , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_get_ntohs ( tvb , offset + 10 ) , tvb_ip_to_str ( tvb , offset + 12 ) ) ;
 break ;
 case RSVP_SESSION_TYPE_P2MP_LSP_TUNNEL_IPV4 : return wmem_strdup_printf ( wmem_packet_scope ( ) , "SESSION: IPv4-P2MP LSP TUNNEL, PSMP ID %d, Tunnel ID %d, Ext Tunnel %s. " , tvb_get_ntohl ( tvb , offset + 4 ) , tvb_get_ntohs ( tvb , offset + 10 ) , tvb_ip_to_str ( tvb , offset + 12 ) ) ;
 break ;
 case RSVP_SESSION_TYPE_P2MP_LSP_TUNNEL_IPV6 : return wmem_strdup_printf ( wmem_packet_scope ( ) , "SESSION: IPv6-P2MP LSP TUNNEL, PSMP ID %d, Tunnel ID %d, Ext Tunnel %s. " , tvb_get_ntohl ( tvb , offset + 4 ) , tvb_get_ntohs ( tvb , offset + 10 ) , tvb_ip6_to_str ( tvb , offset + 12 ) ) ;
 break ;
 case RSVP_SESSION_TYPE_IPV4_E_NNI : return wmem_strdup_printf ( wmem_packet_scope ( ) , "SESSION: IPv4-E-NNI, Destination %s, Tunnel ID %d, Ext Address %s. " , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_get_ntohs ( tvb , offset + 10 ) , tvb_ip_to_str ( tvb , offset + 12 ) ) ;
 break ;
 default : return wmem_strdup_printf ( wmem_packet_scope ( ) , "SESSION: Type %d. " , tvb_get_guint8 ( tvb , offset + 3 ) ) ;
 break ;
 }
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }