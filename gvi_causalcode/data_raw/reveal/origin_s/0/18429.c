static struct nameserver * nameserver_pick ( void ) {
 struct nameserver * started_at = server_head , * picked ;
 if ( ! server_head ) return NULL ;
 if ( ! global_good_nameservers ) {
 server_head = server_head -> next ;
 return server_head ;
 }
 for ( ;
 ;
 ) {
 if ( server_head -> state ) {
 picked = server_head ;
 server_head = server_head -> next ;
 return picked ;
 }
 server_head = server_head -> next ;
 if ( server_head == started_at ) {
 assert ( global_good_nameservers == 0 ) ;
 picked = server_head ;
 server_head = server_head -> next ;
 return picked ;
 }
 }
 }