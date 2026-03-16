bool ack_h ( connection_t * c ) {
 char hisport [ MAX_STRING_SIZE ] ;
 int weight , mtu ;
 uint32_t options ;
 node_t * n ;
 bool choice ;
 if ( sscanf ( c -> buffer , "%*d " MAX_STRING " %d %x" , hisport , & weight , & options ) != 3 ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s)" , "ACK" , c -> name , c -> hostname ) ;
 return false ;
 }
 n = lookup_node ( c -> name ) ;
 if ( ! n ) {
 n = new_node ( ) ;
 n -> name = xstrdup ( c -> name ) ;
 node_add ( n ) ;
 }
 else {
 if ( n -> connection ) {
 ifdebug ( CONNECTIONS ) logger ( LOG_DEBUG , "Established a second connection with %s (%s), closing old connection" , n -> name , n -> hostname ) ;
 terminate_connection ( n -> connection , false ) ;
 graph ( ) ;
 }
 }
 n -> connection = c ;
 c -> node = n ;
 if ( ! ( c -> options & options & OPTION_PMTU_DISCOVERY ) ) {
 c -> options &= ~ OPTION_PMTU_DISCOVERY ;
 options &= ~ OPTION_PMTU_DISCOVERY ;
 }
 c -> options |= options ;
 if ( get_config_int ( lookup_config ( c -> config_tree , "PMTU" ) , & mtu ) && mtu < n -> mtu ) {
 n -> mtu = mtu ;
 }
 if ( get_config_int ( lookup_config ( config_tree , "PMTU" ) , & mtu ) && mtu < n -> mtu ) {
 n -> mtu = mtu ;
 }
 if ( get_config_bool ( lookup_config ( c -> config_tree , "ClampMSS" ) , & choice ) ) {
 if ( choice ) {
 c -> options |= OPTION_CLAMP_MSS ;
 }
 else {
 c -> options &= ~ OPTION_CLAMP_MSS ;
 }
 }
 c -> allow_request = ALL ;
 c -> status . active = true ;
 ifdebug ( CONNECTIONS ) logger ( LOG_NOTICE , "Connection with %s (%s) activated" , c -> name , c -> hostname ) ;
 send_everything ( c ) ;
 c -> edge = new_edge ( ) ;
 c -> edge -> from = myself ;
 c -> edge -> to = n ;
 sockaddrcpy ( & c -> edge -> address , & c -> address ) ;
 sockaddr_setport ( & c -> edge -> address , hisport ) ;
 c -> edge -> weight = ( weight + c -> estimated_weight ) / 2 ;
 c -> edge -> connection = c ;
 c -> edge -> options = c -> options ;
 edge_add ( c -> edge ) ;
 if ( tunnelserver ) {
 send_add_edge ( c , c -> edge ) ;
 }
 else {
 send_add_edge ( everyone , c -> edge ) ;
 }
 graph ( ) ;
 return true ;
 }