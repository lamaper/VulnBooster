static int add_send_request ( struct object * obj , struct remote_lock * lock ) {
 struct transfer_request * request ;
 struct packed_git * target ;
 check_locks ( ) ;
 if ( remote_dir_exists [ obj -> oid . hash [ 0 ] ] == - 1 ) get_remote_object_list ( obj -> oid . hash [ 0 ] ) ;
 if ( obj -> flags & ( REMOTE | PUSHING ) ) return 0 ;
 target = find_sha1_pack ( obj -> oid . hash , repo -> packs ) ;
 if ( target ) {
 obj -> flags |= REMOTE ;
 return 0 ;
 }
 obj -> flags |= PUSHING ;
 request = xmalloc ( sizeof ( * request ) ) ;
 request -> obj = obj ;
 request -> url = NULL ;
 request -> lock = lock ;
 request -> headers = NULL ;
 request -> state = NEED_PUSH ;
 request -> next = request_queue_head ;
 request_queue_head = request ;

 step_active_slots ( ) ;

 }