bool req_key_h ( connection_t * c ) {
 char from_name [ MAX_STRING_SIZE ] ;
 char to_name [ MAX_STRING_SIZE ] ;
 node_t * from , * to ;
 if ( sscanf ( c -> buffer , "%*d " MAX_STRING " " MAX_STRING , from_name , to_name ) != 2 ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s)" , "REQ_KEY" , c -> name , c -> hostname ) ;
 return false ;
 }
 if ( ! check_id ( from_name ) || ! check_id ( to_name ) ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s): %s" , "REQ_KEY" , c -> name , c -> hostname , "invalid name" ) ;
 return false ;
 }
 from = lookup_node ( from_name ) ;
 if ( ! from ) {
 logger ( LOG_ERR , "Got %s from %s (%s) origin %s which does not exist in our connection list" , "REQ_KEY" , c -> name , c -> hostname , from_name ) ;
 return true ;
 }
 to = lookup_node ( to_name ) ;
 if ( ! to ) {
 logger ( LOG_ERR , "Got %s from %s (%s) destination %s which does not exist in our connection list" , "REQ_KEY" , c -> name , c -> hostname , to_name ) ;
 return true ;
 }
 if ( to == myself ) {
 if ( ! send_ans_key ( from ) ) {
 return false ;
 }
 }
 else {
 if ( tunnelserver ) {
 return true ;
 }
 if ( ! to -> status . reachable ) {
 logger ( LOG_WARNING , "Got %s from %s (%s) destination %s which is not reachable" , "REQ_KEY" , c -> name , c -> hostname , to_name ) ;
 return true ;
 }
 send_request ( to -> nexthop -> connection , "%s" , c -> buffer ) ;
 }
 return true ;
 }