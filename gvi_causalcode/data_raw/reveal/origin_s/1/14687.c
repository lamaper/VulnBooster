bool id_h ( connection_t * c ) {
 char name [ MAX_STRING_SIZE ] ;
 if ( sscanf ( c -> buffer , "%*d " MAX_STRING " %d" , name , & c -> protocol_version ) != 2 ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s)" , "ID" , c -> name , c -> hostname ) ;
 return false ;
 }
 if ( ! check_id ( name ) ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s): %s" , "ID" , c -> name , c -> hostname , "invalid name" ) ;
 return false ;
 }
 if ( c -> outgoing ) {
 if ( strcmp ( c -> name , name ) ) {
 logger ( LOG_ERR , "Peer %s is %s instead of %s" , c -> hostname , name , c -> name ) ;
 return false ;
 }
 }
 else {
 if ( c -> name ) {
 free ( c -> name ) ;
 }
 c -> name = xstrdup ( name ) ;
 }
 if ( c -> protocol_version != myself -> connection -> protocol_version ) {
 logger ( LOG_ERR , "Peer %s (%s) uses incompatible version %d" , c -> name , c -> hostname , c -> protocol_version ) ;
 return false ;
 }
 if ( bypass_security ) {
 if ( ! c -> config_tree ) {
 init_configuration ( & c -> config_tree ) ;
 }
 c -> allow_request = ACK ;
 return send_ack ( c ) ;
 }
 if ( ! c -> config_tree ) {
 init_configuration ( & c -> config_tree ) ;
 if ( ! read_connection_config ( c ) ) {
 logger ( LOG_ERR , "Peer %s had unknown identity (%s)" , c -> hostname , c -> name ) ;
 return false ;
 }
 }
 if ( ! read_rsa_public_key ( c ) ) {
 return false ;
 }
 c -> allow_request = METAKEY ;
 return send_metakey ( c ) ;
 }