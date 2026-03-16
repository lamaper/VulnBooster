bool send_ack ( connection_t * c ) {
 struct timeval now ;
 bool choice ;
 gettimeofday ( & now , NULL ) ;
 c -> estimated_weight = ( now . tv_sec - c -> start . tv_sec ) * 1000 + ( now . tv_usec - c -> start . tv_usec ) / 1000 ;
 if ( ( get_config_bool ( lookup_config ( c -> config_tree , "IndirectData" ) , & choice ) && choice ) || myself -> options & OPTION_INDIRECT ) {
 c -> options |= OPTION_INDIRECT ;
 }
 if ( ( get_config_bool ( lookup_config ( c -> config_tree , "TCPOnly" ) , & choice ) && choice ) || myself -> options & OPTION_TCPONLY ) {
 c -> options |= OPTION_TCPONLY | OPTION_INDIRECT ;
 }
 if ( myself -> options & OPTION_PMTU_DISCOVERY && ! ( c -> options & OPTION_TCPONLY ) ) {
 c -> options |= OPTION_PMTU_DISCOVERY ;
 }
 choice = myself -> options & OPTION_CLAMP_MSS ;
 get_config_bool ( lookup_config ( c -> config_tree , "ClampMSS" ) , & choice ) ;
 if ( choice ) {
 c -> options |= OPTION_CLAMP_MSS ;
 }
 get_config_int ( lookup_config ( c -> config_tree , "Weight" ) , & c -> estimated_weight ) ;
 return send_request ( c , "%d %s %d %x" , ACK , myport , c -> estimated_weight , c -> options ) ;
 }