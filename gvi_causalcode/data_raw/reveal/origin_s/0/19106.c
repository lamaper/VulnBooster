static void start_fetch_packed ( struct transfer_request * request ) {
 struct packed_git * target ;
 struct transfer_request * check_request = request_queue_head ;
 struct http_pack_request * preq ;
 target = find_sha1_pack ( request -> obj -> oid . hash , repo -> packs ) ;
 if ( ! target ) {
 fprintf ( stderr , "Unable to fetch %s, will not be able to update server info refs\n" , oid_to_hex ( & request -> obj -> oid ) ) ;
 repo -> can_update_info_refs = 0 ;
 release_request ( request ) ;
 return ;
 }
 fprintf ( stderr , "Fetching pack %s\n" , sha1_to_hex ( target -> sha1 ) ) ;
 fprintf ( stderr , " which contains %s\n" , oid_to_hex ( & request -> obj -> oid ) ) ;
 preq = new_http_pack_request ( target , repo -> url ) ;
 if ( preq == NULL ) {
 repo -> can_update_info_refs = 0 ;
 return ;
 }
 preq -> lst = & repo -> packs ;
 while ( check_request ) {
 if ( check_request -> state == RUN_FETCH_PACKED && ! strcmp ( check_request -> url , preq -> url ) ) {
 release_http_pack_request ( preq ) ;
 release_request ( request ) ;
 return ;
 }
 check_request = check_request -> next ;
 }
 preq -> slot -> callback_func = process_response ;
 preq -> slot -> callback_data = request ;
 request -> slot = preq -> slot ;
 request -> userData = preq ;
 request -> state = RUN_FETCH_PACKED ;
 if ( ! start_active_slot ( preq -> slot ) ) {
 fprintf ( stderr , "Unable to start GET request\n" ) ;
 release_http_pack_request ( preq ) ;
 repo -> can_update_info_refs = 0 ;
 release_request ( request ) ;
 }
 }