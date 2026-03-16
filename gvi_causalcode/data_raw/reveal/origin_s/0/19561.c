static void setup ( char * argv0 , bool * live_check ) {
 char exec_path [ MAXPGPATH ] ;
 check_pghost_envvar ( ) ;
 verify_directories ( ) ;
 if ( pid_lock_file_exists ( old_cluster . pgdata ) ) {
 if ( start_postmaster ( & old_cluster , false ) ) stop_postmaster ( false ) ;
 else {
 if ( ! user_opts . check ) pg_fatal ( "There seems to be a postmaster servicing the old cluster.\n" "Please shutdown that postmaster and try again.\n" ) ;
 else * live_check = true ;
 }
 }
 if ( pid_lock_file_exists ( new_cluster . pgdata ) ) {
 if ( start_postmaster ( & new_cluster , false ) ) stop_postmaster ( false ) ;
 else pg_fatal ( "There seems to be a postmaster servicing the new cluster.\n" "Please shutdown that postmaster and try again.\n" ) ;
 }
 if ( find_my_exec ( argv0 , exec_path ) < 0 ) pg_fatal ( "Could not get path name to pg_upgrade: %s\n" , getErrorText ( ) ) ;
 * last_dir_separator ( exec_path ) = '\0' ;
 canonicalize_path ( exec_path ) ;
 os_info . exec_path = pg_strdup ( exec_path ) ;
 }