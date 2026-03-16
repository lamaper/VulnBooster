bool add_edge_h ( connection_t * c ) {
 edge_t * e ;
 node_t * from , * to ;
 char from_name [ MAX_STRING_SIZE ] ;
 char to_name [ MAX_STRING_SIZE ] ;
 char to_address [ MAX_STRING_SIZE ] ;
 char to_port [ MAX_STRING_SIZE ] ;
 sockaddr_t address ;
 uint32_t options ;
 int weight ;
 if ( sscanf ( c -> buffer , "%*d %*x " MAX_STRING " " MAX_STRING " " MAX_STRING " " MAX_STRING " %x %d" , from_name , to_name , to_address , to_port , & options , & weight ) != 6 ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s)" , "ADD_EDGE" , c -> name , c -> hostname ) ;
 return false ;
 }
 if ( ! check_id ( from_name ) || ! check_id ( to_name ) ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s): %s" , "ADD_EDGE" , c -> name , c -> hostname , "invalid name" ) ;
 return false ;
 }
 if ( seen_request ( c -> buffer ) ) {
 return true ;
 }
 from = lookup_node ( from_name ) ;
 to = lookup_node ( to_name ) ;
 if ( tunnelserver && from != myself && from != c -> node && to != myself && to != c -> node ) {
 ifdebug ( PROTOCOL ) logger ( LOG_WARNING , "Ignoring indirect %s from %s (%s)" , "ADD_EDGE" , c -> name , c -> hostname ) ;
 return true ;
 }
 if ( ! from ) {
 from = new_node ( ) ;
 from -> name = xstrdup ( from_name ) ;
 node_add ( from ) ;
 }
 if ( ! to ) {
 to = new_node ( ) ;
 to -> name = xstrdup ( to_name ) ;
 node_add ( to ) ;
 }
 address = str2sockaddr ( to_address , to_port ) ;
 e = lookup_edge ( from , to ) ;
 if ( e ) {
 if ( e -> weight != weight || e -> options != options || sockaddrcmp ( & e -> address , & address ) ) {
 if ( from == myself ) {
 ifdebug ( PROTOCOL ) logger ( LOG_WARNING , "Got %s from %s (%s) for ourself which does not match existing entry" , "ADD_EDGE" , c -> name , c -> hostname ) ;
 send_add_edge ( c , e ) ;
 return true ;
 }
 else {
 ifdebug ( PROTOCOL ) logger ( LOG_WARNING , "Got %s from %s (%s) which does not match existing entry" , "ADD_EDGE" , c -> name , c -> hostname ) ;
 e -> options = options ;
 if ( sockaddrcmp ( & e -> address , & address ) ) {
 sockaddrfree ( & e -> address ) ;
 e -> address = address ;
 }
 if ( e -> weight != weight ) {
 avl_node_t * node = avl_unlink ( edge_weight_tree , e ) ;
 e -> weight = weight ;
 avl_insert_node ( edge_weight_tree , node ) ;
 }
 goto done ;
 }
 }
 else {
 return true ;
 }
 }
 else if ( from == myself ) {
 ifdebug ( PROTOCOL ) logger ( LOG_WARNING , "Got %s from %s (%s) for ourself which does not exist" , "ADD_EDGE" , c -> name , c -> hostname ) ;
 contradicting_add_edge ++ ;
 e = new_edge ( ) ;
 e -> from = from ;
 e -> to = to ;
 send_del_edge ( c , e ) ;
 free_edge ( e ) ;
 return true ;
 }
 e = new_edge ( ) ;
 e -> from = from ;
 e -> to = to ;
 e -> address = address ;
 e -> options = options ;
 e -> weight = weight ;
 edge_add ( e ) ;
 done : if ( ! tunnelserver ) {
 forward_request ( c ) ;
 }
 graph ( ) ;
 return true ;
 }