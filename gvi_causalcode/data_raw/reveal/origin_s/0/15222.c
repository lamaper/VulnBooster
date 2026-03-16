static call_list * call_list_append ( call_list * list , guint16 scallno ) {
 call_list * node = wmem_new0 ( wmem_packet_scope ( ) , call_list ) ;
 node -> scallno = scallno ;
 if ( list ) {
 call_list * cur = list ;
 while ( cur -> next ) {
 cur = cur -> next ;
 }
 cur -> next = node ;
 return list ;
 }
 else {
 return node ;
 }
 }