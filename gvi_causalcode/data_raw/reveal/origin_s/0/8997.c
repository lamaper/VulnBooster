bool del_edge_h ( connection_t * c ) {
 edge_t * e ;
 char from_name [ MAX_STRING_SIZE ] ;
 char to_name [ MAX_STRING_SIZE ] ;
 node_t * from , * to ;
 if ( sscanf ( c -> buffer , "%*d %*x " MAX_STRING " " MAX_STRING , from_name , to_name ) != 2 ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s)" , "DEL_EDGE" , c -> name , c -> hostname ) ;
 return false ;
 }
 if ( ! check_id ( from_name ) || ! check_id ( to_name ) || ! strcmp ( from_name , to_name ) ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s): %s" , "DEL_EDGE" , c -> name , c -> hostname , "invalid name" ) ;
 return false ;
 }
 if ( seen_request ( c -> buffer ) ) {
 return true ;
 }
 from = lookup_node ( from_name ) ;
 to = lookup_node ( to_name ) ;
 if ( tunnelserver && from != myself && from != c -> node && to != myself && to != c -> node ) {
 ifdebug ( PROTOCOL ) logger ( LOG_WARNING , "Ignoring indirect %s from %s (%s)" , "DEL_EDGE" , c -> name , c -> hostname ) ;
 return true ;
 }
 if ( ! from ) {
 ifdebug ( PROTOCOL ) logger ( LOG_ERR , "Got %s from %s (%s) which does not appear in the edge tree" , "DEL_EDGE" , c -> name , c -> hostname ) ;
 return true ;
 }
 if ( ! to ) {
 ifdebug ( PROTOCOL ) logger ( LOG_ERR , "Got %s from %s (%s) which does not appear in the edge tree" , "DEL_EDGE" , c -> name , c -> hostname ) ;
 return true ;
 }
 e = lookup_edge ( from , to ) ;
 if ( ! e ) {
 ifdebug ( PROTOCOL ) logger ( LOG_WARNING , "Got %s from %s (%s) which does not appear in the edge tree" , "DEL_EDGE" , c -> name , c -> hostname ) ;
 return true ;
 }
 if ( e -> from == myself ) {
 ifdebug ( PROTOCOL ) logger ( LOG_WARNING , "Got %s from %s (%s) for ourself" , "DEL_EDGE" , c -> name , c -> hostname ) ;
 contradicting_del_edge ++ ;
 send_add_edge ( c , e ) ;
 return true ;
 }
 if ( ! tunnelserver ) {
 forward_request ( c ) ;
 }
 edge_del ( e ) ;
 graph ( ) ;
 if ( ! to -> status . reachable ) {
 e = lookup_edge ( to , myself ) ;
 if ( e ) {
 if ( ! tunnelserver ) {
 send_del_edge ( everyone , e ) ;
 }
 edge_del ( e ) ;
 }
 }
 return true ;
 }