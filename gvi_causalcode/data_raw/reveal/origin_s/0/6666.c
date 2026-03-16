static void add_fetch_request ( struct object * obj ) {
 struct transfer_request * request ;
 check_locks ( ) ;
 if ( remote_dir_exists [ obj -> oid . hash [ 0 ] ] == - 1 ) get_remote_object_list ( obj -> oid . hash [ 0 ] ) ;
 if ( obj -> flags & ( LOCAL | FETCHING ) ) return ;
 obj -> flags |= FETCHING ;
 request = xmalloc ( sizeof ( * request ) ) ;
 request -> obj = obj ;
 request -> url = NULL ;
 request -> lock = NULL ;
 request -> headers = NULL ;
 request -> state = NEED_FETCH ;
 request -> next = request_queue_head ;
 request_queue_head = request ;

 step_active_slots ( ) ;
