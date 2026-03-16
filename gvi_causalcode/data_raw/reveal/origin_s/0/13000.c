static void one_remote_object ( const unsigned char * sha1 ) {
 struct object * obj ;
 obj = lookup_object ( sha1 ) ;
 if ( ! obj ) obj = parse_object ( sha1 ) ;
 if ( ! obj ) return ;
 obj -> flags |= REMOTE ;
 if ( ! object_list_contains ( objects , obj ) ) object_list_insert ( obj , & objects ) ;
 }