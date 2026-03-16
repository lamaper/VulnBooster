static void release_request ( struct transfer_request * request ) {
 struct transfer_request * entry = request_queue_head ;
 if ( request == request_queue_head ) {
 request_queue_head = request -> next ;
 }
 else {
 while ( entry -> next != NULL && entry -> next != request ) entry = entry -> next ;
 if ( entry -> next == request ) entry -> next = entry -> next -> next ;
 }
 free ( request -> url ) ;
 free ( request ) ;
 }