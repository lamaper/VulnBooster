static void vacuum_one_database ( const char * dbname , vacuumingOptions * vacopts , int stage , SimpleStringList * tables , const char * host , const char * port , const char * username , enum trivalue prompt_password , int concurrentCons , const char * progname , bool echo , bool quiet ) {
 PQExpBufferData sql ;
 PGconn * conn ;
 SimpleStringListCell * cell ;
 ParallelSlot * slots = NULL ;
 SimpleStringList dbtables = {
 NULL , NULL }
 ;
 int i ;
 bool failed = false ;
 bool parallel = concurrentCons > 1 ;
 const char * stage_commands [ ] = {
 "SET default_statistics_target=1;
 SET vacuum_cost_delay=0;
" , "SET default_statistics_target=10;
 RESET vacuum_cost_delay;
" , "RESET default_statistics_target;
" }
 ;
 const char * stage_messages [ ] = {
 gettext_noop ( "Generating minimal optimizer statistics (1 target)" ) , gettext_noop ( "Generating medium optimizer statistics (10 targets)" ) , gettext_noop ( "Generating default (full) optimizer statistics" ) }
 ;
 Assert ( stage == ANALYZE_NO_STAGE || ( stage >= 0 && stage < ANALYZE_NUM_STAGES ) ) ;
 conn = connectDatabase ( dbname , host , port , username , prompt_password , progname , false , true ) ;
 if ( ! quiet ) {
 if ( stage != ANALYZE_NO_STAGE ) printf ( _ ( "%s: processing database \"%s\": %s\n" ) , progname , PQdb ( conn ) , stage_messages [ stage ] ) ;
 else printf ( _ ( "%s: vacuuming database \"%s\"\n" ) , progname , PQdb ( conn ) ) ;
 fflush ( stdout ) ;
 }
 initPQExpBuffer ( & sql ) ;
 if ( parallel && ( ! tables || ! tables -> head ) ) {
 PQExpBufferData buf ;
 PGresult * res ;
 int ntups ;
 int i ;
 initPQExpBuffer ( & buf ) ;
 res = executeQuery ( conn , "SELECT c.relname, ns.nspname FROM pg_class c, pg_namespace ns\n" " WHERE relkind IN (\'r\', \'m\') AND c.relnamespace = ns.oid\n" " ORDER BY c.relpages DESC;
" , progname , echo ) ;
 ntups = PQntuples ( res ) ;
 for ( i = 0 ;
 i < ntups ;
 i ++ ) {
 appendPQExpBufferStr ( & buf , fmtQualifiedId ( PQserverVersion ( conn ) , PQgetvalue ( res , i , 1 ) , PQgetvalue ( res , i , 0 ) ) ) ;
 simple_string_list_append ( & dbtables , buf . data ) ;
 resetPQExpBuffer ( & buf ) ;
 }
 termPQExpBuffer ( & buf ) ;
 tables = & dbtables ;
 if ( concurrentCons > ntups ) concurrentCons = ntups ;
 if ( concurrentCons <= 1 ) parallel = false ;
 PQclear ( res ) ;
 }
 slots = ( ParallelSlot * ) pg_malloc ( sizeof ( ParallelSlot ) * concurrentCons ) ;
 init_slot ( slots , conn , progname ) ;
 if ( parallel ) {
 for ( i = 1 ;
 i < concurrentCons ;
 i ++ ) {
 conn = connectDatabase ( dbname , host , port , username , prompt_password , progname , false , true ) ;
 init_slot ( slots + i , conn , progname ) ;
 }
 }
 if ( stage != ANALYZE_NO_STAGE ) {
 int j ;
 for ( j = 0 ;
 j < concurrentCons ;
 j ++ ) executeCommand ( ( slots + j ) -> connection , stage_commands [ stage ] , progname , echo ) ;
 }
 cell = tables ? tables -> head : NULL ;
 do {
 ParallelSlot * free_slot ;
 const char * tabname = cell ? cell -> val : NULL ;
 prepare_vacuum_command ( & sql , conn , vacopts , tabname ) ;
 if ( CancelRequested ) {
 failed = true ;
 goto finish ;
 }
 if ( parallel ) {
 free_slot = GetIdleSlot ( slots , concurrentCons , progname ) ;
 if ( ! free_slot ) {
 failed = true ;
 goto finish ;
 }
 free_slot -> isFree = false ;
 }
 else free_slot = slots ;
 run_vacuum_command ( free_slot -> connection , sql . data , echo , tabname , progname , parallel ) ;
 if ( cell ) cell = cell -> next ;
 }
 while ( cell != NULL ) ;
 if ( parallel ) {
 int j ;
 for ( j = 0 ;
 j < concurrentCons ;
 j ++ ) {
 if ( ! GetQueryResult ( ( slots + j ) -> connection , progname ) ) goto finish ;
 ( slots + j ) -> isFree = true ;
 }
 }
 finish : for ( i = 0 ;
 i < concurrentCons ;
 i ++ ) DisconnectDatabase ( slots + i ) ;
 pfree ( slots ) ;
 termPQExpBuffer ( & sql ) ;
 if ( failed ) exit ( 1 ) ;
 }