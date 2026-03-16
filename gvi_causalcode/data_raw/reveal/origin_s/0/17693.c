static void finish_request ( struct transfer_request * request ) {
 struct http_pack_request * preq ;
 struct http_object_request * obj_req ;
 request -> curl_result = request -> slot -> curl_result ;
 request -> http_code = request -> slot -> http_code ;
 request -> slot = NULL ;
 check_locks ( ) ;
 if ( request -> headers != NULL ) curl_slist_free_all ( request -> headers ) ;
 if ( request -> state != RUN_PUT ) {
 free ( request -> url ) ;
 request -> url = NULL ;
 }
 if ( request -> state == RUN_MKCOL ) {
 if ( request -> curl_result == CURLE_OK || request -> http_code == 405 ) {
 remote_dir_exists [ request -> obj -> oid . hash [ 0 ] ] = 1 ;
 start_put ( request ) ;
 }
 else {
 fprintf ( stderr , "MKCOL %s failed, aborting (%d/%ld)\n" , oid_to_hex ( & request -> obj -> oid ) , request -> curl_result , request -> http_code ) ;
 request -> state = ABORTED ;
 aborted = 1 ;
 }
 }
 else if ( request -> state == RUN_PUT ) {
 if ( request -> curl_result == CURLE_OK ) {
 start_move ( request ) ;
 }
 else {
 fprintf ( stderr , "PUT %s failed, aborting (%d/%ld)\n" , oid_to_hex ( & request -> obj -> oid ) , request -> curl_result , request -> http_code ) ;
 request -> state = ABORTED ;
 aborted = 1 ;
 }
 }
 else if ( request -> state == RUN_MOVE ) {
 if ( request -> curl_result == CURLE_OK ) {
 if ( push_verbosely ) fprintf ( stderr , " sent %s\n" , oid_to_hex ( & request -> obj -> oid ) ) ;
 request -> obj -> flags |= REMOTE ;
 release_request ( request ) ;
 }
 else {
 fprintf ( stderr , "MOVE %s failed, aborting (%d/%ld)\n" , oid_to_hex ( & request -> obj -> oid ) , request -> curl_result , request -> http_code ) ;
 request -> state = ABORTED ;
 aborted = 1 ;
 }
 }
 else if ( request -> state == RUN_FETCH_LOOSE ) {
 obj_req = ( struct http_object_request * ) request -> userData ;
 if ( finish_http_object_request ( obj_req ) == 0 ) if ( obj_req -> rename == 0 ) request -> obj -> flags |= ( LOCAL | REMOTE ) ;
 if ( request -> obj -> flags & LOCAL ) {
 release_http_object_request ( obj_req ) ;
 release_request ( request ) ;
 }
 else start_fetch_packed ( request ) ;
 }
 else if ( request -> state == RUN_FETCH_PACKED ) {
 int fail = 1 ;
 if ( request -> curl_result != CURLE_OK ) {
 fprintf ( stderr , "Unable to get pack file %s\n%s" , request -> url , curl_errorstr ) ;
 }
 else {
 preq = ( struct http_pack_request * ) request -> userData ;
 if ( preq ) {
 if ( finish_http_pack_request ( preq ) == 0 ) fail = 0 ;
 release_http_pack_request ( preq ) ;
 }
 }
 if ( fail ) repo -> can_update_info_refs = 0 ;
 release_request ( request ) ;
 }
 }