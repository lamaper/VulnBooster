static void check_for_jsonb_9_4_usage ( ClusterInfo * cluster ) {
 int dbnum ;
 FILE * script = NULL ;
 bool found = false ;
 char output_path [ MAXPGPATH ] ;
 prep_status ( "Checking for JSONB user data types" ) ;
 snprintf ( output_path , sizeof ( output_path ) , "tables_using_jsonb.txt" ) ;
 for ( dbnum = 0 ;
 dbnum < cluster -> dbarr . ndbs ;
 dbnum ++ ) {
 PGresult * res ;
 bool db_used = false ;
 int ntups ;
 int rowno ;
 int i_nspname , i_relname , i_attname ;
 DbInfo * active_db = & cluster -> dbarr . dbs [ dbnum ] ;
 PGconn * conn = connectToServer ( cluster , active_db -> db_name ) ;
 res = executeQueryOrDie ( conn , "SELECT n.nspname, c.relname, a.attname " "FROM pg_catalog.pg_class c, " " pg_catalog.pg_namespace n, " " pg_catalog.pg_attribute a " "WHERE c.oid = a.attrelid AND " " NOT a.attisdropped AND " " a.atttypid = 'pg_catalog.jsonb'::pg_catalog.regtype AND " " c.relnamespace = n.oid AND " " n.nspname !~ '^pg_temp_' AND " " n.nspname NOT IN ('pg_catalog', 'information_schema')" ) ;
 ntups = PQntuples ( res ) ;
 i_nspname = PQfnumber ( res , "nspname" ) ;
 i_relname = PQfnumber ( res , "relname" ) ;
 i_attname = PQfnumber ( res , "attname" ) ;
 for ( rowno = 0 ;
 rowno < ntups ;
 rowno ++ ) {
 found = true ;
 if ( script == NULL && ( script = fopen_priv ( output_path , "w" ) ) == NULL ) pg_fatal ( "Could not open file \"%s\": %s\n" , output_path , getErrorText ( ) ) ;
 if ( ! db_used ) {
 fprintf ( script , "Database: %s\n" , active_db -> db_name ) ;
 db_used = true ;
 }
 fprintf ( script , " %s.%s.%s\n" , PQgetvalue ( res , rowno , i_nspname ) , PQgetvalue ( res , rowno , i_relname ) , PQgetvalue ( res , rowno , i_attname ) ) ;
 }
 PQclear ( res ) ;
 PQfinish ( conn ) ;
 }
 if ( script ) fclose ( script ) ;
 if ( found ) {
 pg_log ( PG_REPORT , "fatal\n" ) ;
 pg_fatal ( "Your installation contains one of the JSONB data types in user tables.\n" "The internal format of JSONB changed during 9.4 beta so this cluster cannot currently\n" "be upgraded. You can remove the problem tables and restart the upgrade. A list\n" "of the problem columns is in the file:\n" " %s\n\n" , output_path ) ;
 }
 else check_ok ( ) ;
 }