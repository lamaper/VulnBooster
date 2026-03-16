static void check_for_isn_and_int8_passing_mismatch ( ClusterInfo * cluster ) {
 int dbnum ;
 FILE * script = NULL ;
 bool found = false ;
 char output_path [ MAXPGPATH ] ;
 prep_status ( "Checking for contrib/isn with bigint-passing mismatch" ) ;
 if ( old_cluster . controldata . float8_pass_by_value == new_cluster . controldata . float8_pass_by_value ) {
 check_ok ( ) ;
 return ;
 }
 snprintf ( output_path , sizeof ( output_path ) , "contrib_isn_and_int8_pass_by_value.txt" ) ;
 for ( dbnum = 0 ;
 dbnum < cluster -> dbarr . ndbs ;
 dbnum ++ ) {
 PGresult * res ;
 bool db_used = false ;
 int ntups ;
 int rowno ;
 int i_nspname , i_proname ;
 DbInfo * active_db = & cluster -> dbarr . dbs [ dbnum ] ;
 PGconn * conn = connectToServer ( cluster , active_db -> db_name ) ;
 res = executeQueryOrDie ( conn , "SELECT n.nspname, p.proname " "FROM pg_catalog.pg_proc p, " " pg_catalog.pg_namespace n " "WHERE p.pronamespace = n.oid AND " " p.probin = '$libdir/isn'" ) ;
 ntups = PQntuples ( res ) ;
 i_nspname = PQfnumber ( res , "nspname" ) ;
 i_proname = PQfnumber ( res , "proname" ) ;
 for ( rowno = 0 ;
 rowno < ntups ;
 rowno ++ ) {
 found = true ;
 if ( script == NULL && ( script = fopen_priv ( output_path , "w" ) ) == NULL ) pg_fatal ( "Could not open file \"%s\": %s\n" , output_path , getErrorText ( ) ) ;
 if ( ! db_used ) {
 fprintf ( script , "Database: %s\n" , active_db -> db_name ) ;
 db_used = true ;
 }
 fprintf ( script , " %s.%s\n" , PQgetvalue ( res , rowno , i_nspname ) , PQgetvalue ( res , rowno , i_proname ) ) ;
 }
 PQclear ( res ) ;
 PQfinish ( conn ) ;
 }
 if ( script ) fclose ( script ) ;
 if ( found ) {
 pg_log ( PG_REPORT , "fatal\n" ) ;
 pg_fatal ( "Your installation contains \"contrib/isn\" functions which rely on the\n" "bigint data type. Your old and new clusters pass bigint values\n" "differently so this cluster cannot currently be upgraded. You can\n" "manually upgrade databases that use \"contrib/isn\" facilities and remove\n" "\"contrib/isn\" from the old cluster and restart the upgrade. A list of\n" "the problem functions is in the file:\n" " %s\n\n" , output_path ) ;
 }
 else check_ok ( ) ;
 }