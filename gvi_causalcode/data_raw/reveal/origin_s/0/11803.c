static void search_request_finished ( struct request * const req ) {
 if ( req -> search_state ) {
 search_state_decref ( req -> search_state ) ;
 req -> search_state = NULL ;
 }
 if ( req -> search_origname ) {
 free ( req -> search_origname ) ;
 req -> search_origname = NULL ;
 }
 }