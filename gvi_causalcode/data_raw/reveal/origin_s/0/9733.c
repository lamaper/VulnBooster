int main ( int argc , char * * argv ) {
 struct transfer_request * request ;
 struct transfer_request * next_request ;
 int nr_refspec = 0 ;
 char * * refspec = NULL ;
 struct remote_lock * ref_lock = NULL ;
 struct remote_lock * info_ref_lock = NULL ;
 struct rev_info revs ;
 int delete_branch = 0 ;
 int force_delete = 0 ;
 int objects_to_send ;
 int rc = 0 ;
 int i ;
 int new_refs ;
 struct ref * ref , * local_refs ;
 git_setup_gettext ( ) ;
 git_extract_argv0_path ( argv [ 0 ] ) ;
 repo = xcalloc ( 1 , sizeof ( * repo ) ) ;
 argv ++ ;
 for ( i = 1 ;
 i < argc ;
 i ++ , argv ++ ) {
 char * arg = * argv ;
 if ( * arg == '-' ) {
 if ( ! strcmp ( arg , "--all" ) ) {
 push_all = MATCH_REFS_ALL ;
 continue ;
 }
 if ( ! strcmp ( arg , "--force" ) ) {
 force_all = 1 ;
 continue ;
 }
 if ( ! strcmp ( arg , "--dry-run" ) ) {
 dry_run = 1 ;
 continue ;
 }
 if ( ! strcmp ( arg , "--helper-status" ) ) {
 helper_status = 1 ;
 continue ;
 }
 if ( ! strcmp ( arg , "--verbose" ) ) {
 push_verbosely = 1 ;
 http_is_verbose = 1 ;
 continue ;
 }
 if ( ! strcmp ( arg , "-d" ) ) {
 delete_branch = 1 ;
 continue ;
 }
 if ( ! strcmp ( arg , "-D" ) ) {
 delete_branch = 1 ;
 force_delete = 1 ;
 continue ;
 }
 if ( ! strcmp ( arg , "-h" ) ) usage ( http_push_usage ) ;
 }
 if ( ! repo -> url ) {
 char * path = strstr ( arg , "//" ) ;
 str_end_url_with_slash ( arg , & repo -> url ) ;
 repo -> path_len = strlen ( repo -> url ) ;
 if ( path ) {
 repo -> path = strchr ( path + 2 , '/' ) ;
 if ( repo -> path ) repo -> path_len = strlen ( repo -> path ) ;
 }
 continue ;
 }
 refspec = argv ;
 nr_refspec = argc - i ;
 break ;
 }


 if ( delete_branch && nr_refspec != 1 ) die ( "You must specify only one branch name when deleting a remote branch" ) ;
 setup_git_directory ( ) ;
 memset ( remote_dir_exists , - 1 , 256 ) ;
 http_init ( NULL , repo -> url , 1 ) ;


 rc = 1 ;
 goto cleanup ;
 }
 sigchain_push_common ( remove_locks_on_signal ) ;
 repo -> can_update_info_refs = 0 ;
 repo -> has_info_refs = remote_exists ( "info/refs" ) ;
 repo -> has_info_packs = remote_exists ( "objects/info/packs" ) ;
 if ( repo -> has_info_refs ) {
 info_ref_lock = lock_remote ( "info/refs" , LOCK_TIME ) ;
 if ( info_ref_lock ) repo -> can_update_info_refs = 1 ;
 else {
 error ( "cannot lock existing info/refs" ) ;
 rc = 1 ;
 goto cleanup ;
 }
 }
 if ( repo -> has_info_packs ) fetch_indices ( ) ;
 local_refs = get_local_heads ( ) ;
 fprintf ( stderr , "Fetching remote heads...\n" ) ;
 get_dav_remote_heads ( ) ;
 run_request_queue ( ) ;
 if ( delete_branch ) {
 if ( delete_remote_branch ( refspec [ 0 ] , force_delete ) == - 1 ) {
 fprintf ( stderr , "Unable to delete remote branch %s\n" , refspec [ 0 ] ) ;
 if ( helper_status ) printf ( "error %s cannot remove\n" , refspec [ 0 ] ) ;
 }
 goto cleanup ;
 }
 if ( match_push_refs ( local_refs , & remote_refs , nr_refspec , ( const char * * ) refspec , push_all ) ) {
 rc = - 1 ;
 goto cleanup ;
 }
 if ( ! remote_refs ) {
 fprintf ( stderr , "No refs in common and none specified;
 doing nothing.\n" ) ;
 if ( helper_status ) printf ( "error null no match\n" ) ;
 rc = 0 ;
 goto cleanup ;
 }
 new_refs = 0 ;
 for ( ref = remote_refs ;
 ref ;
 ref = ref -> next ) {
 struct argv_array commit_argv = ARGV_ARRAY_INIT ;
 if ( ! ref -> peer_ref ) continue ;
 if ( is_null_oid ( & ref -> peer_ref -> new_oid ) ) {
 if ( delete_remote_branch ( ref -> name , 1 ) == - 1 ) {
 error ( "Could not remove %s" , ref -> name ) ;
 if ( helper_status ) printf ( "error %s cannot remove\n" , ref -> name ) ;
 rc = - 4 ;
 }
 else if ( helper_status ) printf ( "ok %s\n" , ref -> name ) ;
 new_refs ++ ;
 continue ;
 }
 if ( ! oidcmp ( & ref -> old_oid , & ref -> peer_ref -> new_oid ) ) {
 if ( push_verbosely ) fprintf ( stderr , "'%s': up-to-date\n" , ref -> name ) ;
 if ( helper_status ) printf ( "ok %s up to date\n" , ref -> name ) ;
 continue ;
 }
 if ( ! force_all && ! is_null_oid ( & ref -> old_oid ) && ! ref -> force ) {
 if ( ! has_object_file ( & ref -> old_oid ) || ! ref_newer ( & ref -> peer_ref -> new_oid , & ref -> old_oid ) ) {
 error ( "remote '%s' is not an ancestor of\n" "local '%s'.\n" "Maybe you are not up-to-date and " "need to pull first?" , ref -> name , ref -> peer_ref -> name ) ;
 if ( helper_status ) printf ( "error %s non-fast forward\n" , ref -> name ) ;
 rc = - 2 ;
 continue ;
 }
 }
 oidcpy ( & ref -> new_oid , & ref -> peer_ref -> new_oid ) ;
 new_refs ++ ;
 fprintf ( stderr , "updating '%s'" , ref -> name ) ;
 if ( strcmp ( ref -> name , ref -> peer_ref -> name ) ) fprintf ( stderr , " using '%s'" , ref -> peer_ref -> name ) ;
 fprintf ( stderr , "\n from %s\n to %s\n" , oid_to_hex ( & ref -> old_oid ) , oid_to_hex ( & ref -> new_oid ) ) ;
 if ( dry_run ) {
 if ( helper_status ) printf ( "ok %s\n" , ref -> name ) ;
 continue ;
 }
 ref_lock = lock_remote ( ref -> name , LOCK_TIME ) ;
 if ( ref_lock == NULL ) {
 fprintf ( stderr , "Unable to lock remote branch %s\n" , ref -> name ) ;
 if ( helper_status ) printf ( "error %s lock error\n" , ref -> name ) ;
 rc = 1 ;
 continue ;
 }
 argv_array_push ( & commit_argv , "" ) ;
 argv_array_push ( & commit_argv , "--objects" ) ;
 argv_array_push ( & commit_argv , oid_to_hex ( & ref -> new_oid ) ) ;
 if ( ! push_all && ! is_null_oid ( & ref -> old_oid ) ) argv_array_pushf ( & commit_argv , "^%s" , oid_to_hex ( & ref -> old_oid ) ) ;
 init_revisions ( & revs , setup_git_directory ( ) ) ;
 setup_revisions ( commit_argv . argc , commit_argv . argv , & revs , NULL ) ;
 revs . edge_hint = 0 ;
 pushing = 0 ;
 if ( prepare_revision_walk ( & revs ) ) die ( "revision walk setup failed" ) ;
 mark_edges_uninteresting ( & revs , NULL ) ;
 objects_to_send = get_delta ( & revs , ref_lock ) ;
 finish_all_active_slots ( ) ;
 pushing = 1 ;
 if ( objects_to_send ) fprintf ( stderr , " sending %d objects\n" , objects_to_send ) ;
 run_request_queue ( ) ;
 if ( aborted || ! update_remote ( ref -> new_oid . hash , ref_lock ) ) rc = 1 ;
 if ( ! rc ) fprintf ( stderr , " done\n" ) ;
 if ( helper_status ) printf ( "%s %s\n" , ! rc ? "ok" : "error" , ref -> name ) ;
 unlock_remote ( ref_lock ) ;
 check_locks ( ) ;
 argv_array_clear ( & commit_argv ) ;
 }
 if ( repo -> has_info_refs && new_refs ) {
 if ( info_ref_lock && repo -> can_update_info_refs ) {
 fprintf ( stderr , "Updating remote server info\n" ) ;
 if ( ! dry_run ) update_remote_info_refs ( info_ref_lock ) ;
 }
 else {
 fprintf ( stderr , "Unable to update server info\n" ) ;
 }
 }
 cleanup : if ( info_ref_lock ) unlock_remote ( info_ref_lock ) ;
 free ( repo ) ;
 http_cleanup ( ) ;
 request = request_queue_head ;
 while ( request != NULL ) {
 next_request = request -> next ;
 release_request ( request ) ;
 request = next_request ;
 }
 return rc ;
 }