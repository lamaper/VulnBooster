static void one_remote_ref ( const char * refname ) {
 struct ref * ref ;
 struct object * obj ;
 ref = alloc_ref ( refname ) ;
 if ( http_fetch_ref ( repo -> url , ref ) != 0 ) {
 fprintf ( stderr , "Unable to fetch ref %s from %s\n" , refname , repo -> url ) ;
 free ( ref ) ;
 return ;
 }
 if ( repo -> can_update_info_refs && ! has_object_file ( & ref -> old_oid ) ) {
 obj = lookup_unknown_object ( ref -> old_oid . hash ) ;
 if ( obj ) {
 fprintf ( stderr , " fetch %s for %s\n" , oid_to_hex ( & ref -> old_oid ) , refname ) ;
 add_fetch_request ( obj ) ;
 }
 }
 ref -> next = remote_refs ;
 remote_refs = ref ;
 }