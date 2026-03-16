void setup_outgoing_connection ( outgoing_t * outgoing ) {
 connection_t * c ;
 node_t * n ;
 outgoing -> event = NULL ;
 n = lookup_node ( outgoing -> name ) ;
 if ( n ) if ( n -> connection ) {
 ifdebug ( CONNECTIONS ) logger ( LOG_INFO , "Already connected to %s" , outgoing -> name ) ;
 n -> connection -> outgoing = outgoing ;
 return ;
 }
 c = new_connection ( ) ;
 c -> name = xstrdup ( outgoing -> name ) ;
 c -> outcipher = myself -> connection -> outcipher ;
 c -> outdigest = myself -> connection -> outdigest ;
 c -> outmaclength = myself -> connection -> outmaclength ;
 c -> outcompression = myself -> connection -> outcompression ;
 init_configuration ( & c -> config_tree ) ;
 if ( ! read_connection_config ( c ) ) {
 free_connection ( c ) ;
 outgoing -> timeout = maxtimeout ;
 retry_outgoing ( outgoing ) ;
 return ;
 }
 outgoing -> cfg = lookup_config ( c -> config_tree , "Address" ) ;
 if ( ! outgoing -> cfg ) {
 logger ( LOG_ERR , "No address specified for %s" , c -> name ) ;
 free_connection ( c ) ;
 outgoing -> timeout = maxtimeout ;
 retry_outgoing ( outgoing ) ;
 return ;
 }
 c -> outgoing = outgoing ;
 c -> last_ping_time = now ;
 connection_add ( c ) ;
 do_outgoing_connection ( c ) ;
 }