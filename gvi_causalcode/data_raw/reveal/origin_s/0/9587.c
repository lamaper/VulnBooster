void create_script_for_old_cluster_deletion ( char * * deletion_script_file_name ) {
 FILE * script = NULL ;
 int tblnum ;
 char old_cluster_pgdata [ MAXPGPATH ] , new_cluster_pgdata [ MAXPGPATH ] ;
 * deletion_script_file_name = psprintf ( "%sdelete_old_cluster.%s" , SCRIPT_PREFIX , SCRIPT_EXT ) ;
 strlcpy ( old_cluster_pgdata , old_cluster . pgdata , MAXPGPATH ) ;
 canonicalize_path ( old_cluster_pgdata ) ;
 strlcpy ( new_cluster_pgdata , new_cluster . pgdata , MAXPGPATH ) ;
 canonicalize_path ( new_cluster_pgdata ) ;
 if ( path_is_prefix_of_path ( old_cluster_pgdata , new_cluster_pgdata ) ) {
 pg_log ( PG_WARNING , "\nWARNING: new data directory should not be inside the old data directory, e.g. %s\n" , old_cluster_pgdata ) ;
 unlink ( * deletion_script_file_name ) ;
 pg_free ( * deletion_script_file_name ) ;
 * deletion_script_file_name = NULL ;
 return ;
 }
 for ( tblnum = 0 ;
 tblnum < os_info . num_old_tablespaces ;
 tblnum ++ ) {
 char old_tablespace_dir [ MAXPGPATH ] ;
 strlcpy ( old_tablespace_dir , os_info . old_tablespaces [ tblnum ] , MAXPGPATH ) ;
 canonicalize_path ( old_tablespace_dir ) ;
 if ( path_is_prefix_of_path ( old_cluster_pgdata , old_tablespace_dir ) ) {
 pg_log ( PG_WARNING , "\nWARNING: user-defined tablespace locations should not be inside the data directory, e.g. %s\n" , old_tablespace_dir ) ;
 unlink ( * deletion_script_file_name ) ;
 pg_free ( * deletion_script_file_name ) ;
 * deletion_script_file_name = NULL ;
 return ;
 }
 }
 prep_status ( "Creating script to delete old cluster" ) ;
 if ( ( script = fopen_priv ( * deletion_script_file_name , "w" ) ) == NULL ) pg_fatal ( "Could not open file \"%s\": %s\n" , * deletion_script_file_name , getErrorText ( ) ) ;


 for ( tblnum = 0 ;
 tblnum < os_info . num_old_tablespaces ;
 tblnum ++ ) {
 if ( strlen ( old_cluster . tablespace_suffix ) == 0 ) {
 int dbnum ;
 fprintf ( script , "\n" ) ;
 if ( GET_MAJOR_VERSION ( old_cluster . major_version ) <= 804 ) fprintf ( script , RM_CMD " %s%cPG_VERSION\n" , fix_path_separator ( os_info . old_tablespaces [ tblnum ] ) , PATH_SEPARATOR ) ;
 for ( dbnum = 0 ;
 dbnum < old_cluster . dbarr . ndbs ;
 dbnum ++ ) fprintf ( script , RMDIR_CMD " %c%s%c%d%c\n" , PATH_QUOTE , fix_path_separator ( os_info . old_tablespaces [ tblnum ] ) , PATH_SEPARATOR , old_cluster . dbarr . dbs [ dbnum ] . db_oid , PATH_QUOTE ) ;
 }
 else {
 char * suffix_path = pg_strdup ( old_cluster . tablespace_suffix ) ;
 fprintf ( script , RMDIR_CMD " %c%s%s%c\n" , PATH_QUOTE , fix_path_separator ( os_info . old_tablespaces [ tblnum ] ) , fix_path_separator ( suffix_path ) , PATH_QUOTE ) ;
 pfree ( suffix_path ) ;
 }
 }
 fclose ( script ) ;


 }