static Entity * EntityReverse ( Entity * ent ) {
 Entity * next , * last = NULL ;
 while ( ent != NULL ) {
 next = ent -> next ;
 ent -> next = last ;
 last = ent ;
 ent = next ;
 }
 return ( last ) ;
 }