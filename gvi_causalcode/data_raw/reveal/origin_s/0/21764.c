static void cleanup ( void ) {
 fclose ( log_opts . internal ) ;
 if ( ! log_opts . retain ) {
 int dbnum ;
 char * * filename ;
 for ( filename = output_files ;
 * filename != NULL ;
 filename ++ ) unlink ( * filename ) ;
 unlink ( GLOBALS_DUMP_FILE ) ;
 if ( old_cluster . dbarr . dbs ) for ( dbnum = 0 ;
 dbnum < old_cluster . dbarr . ndbs ;
 dbnum ++ ) {
 char sql_file_name [ MAXPGPATH ] , log_file_name [ MAXPGPATH ] ;
 DbInfo * old_db = & old_cluster . dbarr . dbs [ dbnum ] ;
 snprintf ( sql_file_name , sizeof ( sql_file_name ) , DB_DUMP_FILE_MASK , old_db -> db_oid ) ;
 unlink ( sql_file_name ) ;
 snprintf ( log_file_name , sizeof ( log_file_name ) , DB_DUMP_LOG_FILE_MASK , old_db -> db_oid ) ;
 unlink ( log_file_name ) ;
 }
 }
 }