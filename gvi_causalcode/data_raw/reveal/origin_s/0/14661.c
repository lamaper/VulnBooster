static int delete_remote_branch ( const char * pattern , int force ) {
 struct ref * refs = remote_refs ;
 struct ref * remote_ref = NULL ;
 unsigned char head_sha1 [ 20 ] ;
 char * symref = NULL ;
 int match ;
 int patlen = strlen ( pattern ) ;
 int i ;
 struct active_request_slot * slot ;
 struct slot_results results ;
 char * url ;
 for ( match = 0 ;
 refs ;
 refs = refs -> next ) {
 char * name = refs -> name ;
 int namelen = strlen ( name ) ;
 if ( namelen < patlen || memcmp ( name + namelen - patlen , pattern , patlen ) ) continue ;
 if ( namelen != patlen && name [ namelen - patlen - 1 ] != '/' ) continue ;
 match ++ ;
 remote_ref = refs ;
 }
 if ( match == 0 ) return error ( "No remote branch matches %s" , pattern ) ;
 if ( match != 1 ) return error ( "More than one remote branch matches %s" , pattern ) ;
 fetch_symref ( "HEAD" , & symref , head_sha1 ) ;
 if ( ! symref ) return error ( "Remote HEAD is not a symref" ) ;
 for ( i = 0 ;
 symref && i < MAXDEPTH ;
 i ++ ) {
 if ( ! strcmp ( remote_ref -> name , symref ) ) return error ( "Remote branch %s is the current HEAD" , remote_ref -> name ) ;
 fetch_symref ( symref , & symref , head_sha1 ) ;
 }
 if ( ! force ) {
 if ( symref ) return error ( "Remote HEAD symrefs too deep" ) ;
 if ( is_null_sha1 ( head_sha1 ) ) return error ( "Unable to resolve remote HEAD" ) ;
 if ( ! has_sha1_file ( head_sha1 ) ) return error ( "Remote HEAD resolves to object %s\nwhich does not exist locally, perhaps you need to fetch?" , sha1_to_hex ( head_sha1 ) ) ;
 if ( is_null_oid ( & remote_ref -> old_oid ) ) return error ( "Unable to resolve remote branch %s" , remote_ref -> name ) ;
 if ( ! has_object_file ( & remote_ref -> old_oid ) ) return error ( "Remote branch %s resolves to object %s\nwhich does not exist locally, perhaps you need to fetch?" , remote_ref -> name , oid_to_hex ( & remote_ref -> old_oid ) ) ;
 if ( ! verify_merge_base ( head_sha1 , remote_ref ) ) {
 return error ( "The branch '%s' is not an ancestor " "of your current HEAD.\n" "If you are sure you want to delete it," " run:\n\t'git http-push -D %s %s'" , remote_ref -> name , repo -> url , pattern ) ;
 }
 }
 fprintf ( stderr , "Removing remote branch '%s'\n" , remote_ref -> name ) ;
 if ( dry_run ) return 0 ;
 url = xstrfmt ( "%s%s" , repo -> url , remote_ref -> name ) ;
 slot = get_active_slot ( ) ;
 slot -> results = & results ;
 curl_setup_http_get ( slot -> curl , url , DAV_DELETE ) ;
 if ( start_active_slot ( slot ) ) {
 run_active_slot ( slot ) ;
 free ( url ) ;
 if ( results . curl_result != CURLE_OK ) return error ( "DELETE request failed (%d/%ld)" , results . curl_result , results . http_code ) ;
 }
 else {
 free ( url ) ;
 return error ( "Unable to start DELETE request" ) ;
 }
 return 0 ;
 }