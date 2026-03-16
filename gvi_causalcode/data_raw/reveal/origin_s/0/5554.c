static struct object_list * * process_blob ( struct blob * blob , struct object_list * * p ) {
 struct object * obj = & blob -> object ;
 obj -> flags |= LOCAL ;
 if ( obj -> flags & ( UNINTERESTING | SEEN ) ) return p ;
 obj -> flags |= SEEN ;
 return add_one_object ( obj , p ) ;
 }