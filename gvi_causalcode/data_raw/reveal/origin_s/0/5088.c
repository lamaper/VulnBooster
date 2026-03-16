bool key_changed_h ( connection_t * c ) {
 char name [ MAX_STRING_SIZE ] ;
 node_t * n ;
 if ( sscanf ( c -> buffer , "%*d %*x " MAX_STRING , name ) != 1 ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s)" , "KEY_CHANGED" , c -> name , c -> hostname ) ;
 return false ;
 }
 if ( ! check_id ( name ) ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s): %s" , "KEY_CHANGED" , c -> name , c -> hostname , "invalid name" ) ;
 return false ;
 }
 if ( seen_request ( c -> buffer ) ) {
 return true ;
 }
 n = lookup_node ( name ) ;
 if ( ! n ) {
 logger ( LOG_ERR , "Got %s from %s (%s) origin %s which does not exist" , "KEY_CHANGED" , c -> name , c -> hostname , name ) ;
 return true ;
 }
 n -> status . validkey = false ;
 n -> last_req_key = 0 ;
 if ( ! tunnelserver ) {
 forward_request ( c ) ;
 }
 return true ;
 }