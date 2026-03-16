static void cluster_one_database ( const char * dbname , bool verbose , const char * table , const char * host , const char * port , const char * username , enum trivalue prompt_password , const char * progname , bool echo ) {
 PQExpBufferData sql ;
 PGconn * conn ;
 initPQExpBuffer ( & sql ) ;
 appendPQExpBufferStr ( & sql , "CLUSTER" ) ;
 if ( verbose ) appendPQExpBufferStr ( & sql , " VERBOSE" ) ;
 if ( table ) appendPQExpBuffer ( & sql , " %s" , table ) ;
 appendPQExpBufferChar ( & sql , ';
' ) ;
 conn = connectDatabase ( dbname , host , port , username , prompt_password , progname , false , false ) ;
 if ( ! executeMaintenanceCommand ( conn , sql . data , echo ) ) {
 if ( table ) fprintf ( stderr , _ ( "%s: clustering of table \"%s\" in database \"%s\" failed: %s" ) , progname , table , PQdb ( conn ) , PQerrorMessage ( conn ) ) ;
 else fprintf ( stderr , _ ( "%s: clustering of database \"%s\" failed: %s" ) , progname , PQdb ( conn ) , PQerrorMessage ( conn ) ) ;
 PQfinish ( conn ) ;
 exit ( 1 ) ;
 }
 PQfinish ( conn ) ;
 termPQExpBuffer ( & sql ) ;
 }