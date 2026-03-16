static struct object_list * * add_one_object ( struct object * obj , struct object_list * * p ) {
 struct object_list * entry = xmalloc ( sizeof ( struct object_list ) ) ;
 entry -> item = obj ;
 entry -> next = * p ;
 * p = entry ;
 return & entry -> next ;
 }