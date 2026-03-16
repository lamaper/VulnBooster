static void check_for_reg_data_type_usage ( ClusterInfo * cluster ) {
 int dbnum ;
 FILE * script = NULL ;
 bool found = false ;
 char output_path [ MAXPGPATH ] ;
 prep_status ( "Checking for reg* system OID user data types" ) ;
 snprintf ( output_path , sizeof ( output_path ) , "tables_using_reg.txt" ) ;
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
 res = executeQueryOrDie ( conn , "SELECT n.nspname, c.relname, a.attname " "FROM pg_catalog.pg_class c, " " pg_catalog.pg_namespace n, " " pg_catalog.pg_attribute a " "WHERE c.oid = a.attrelid AND " " NOT a.attisdropped AND " " a.atttypid IN ( " " 'pg_catalog.regproc'::pg_catalog.regtype, " " 'pg_catalog.regprocedure'::pg_catalog.regtype, " " 'pg_catalog.regoper'::pg_catalog.regtype, " " 'pg_catalog.regoperator'::pg_catalog.regtype, " " 'pg_catalog.regconfig'::pg_catalog.regtype, " " 'pg_catalog.regdictionary'::pg_catalog.regtype) AND " " c.relnamespace = n.oid AND " " n.nspname NOT IN ('pg_catalog', 'information_schema')" ) ;
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
 pg_fatal ( "Your installation contains one of the reg* data types in user tables.\n" "These data types reference system OIDs that are not preserved by\n" "pg_upgrade, so this cluster cannot currently be upgraded. You can\n" "remove the problem tables and restart the upgrade. A list of the problem\n" "columns is in the file:\n" " %s\n\n" , output_path ) ;
 }
 else check_ok ( ) ;
 }