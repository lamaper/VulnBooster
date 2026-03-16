static void reindex_one_database ( const char * name , const char * dbname , const char * type , const char * host , const char * port , const char * username , enum trivalue prompt_password , const char * progname , bool echo , bool verbose ) {
 PQExpBufferData sql ;
 PGconn * conn ;
 conn = connectDatabase ( dbname , host , port , username , prompt_password , progname , false , false ) ;
 initPQExpBuffer ( & sql ) ;
 appendPQExpBufferStr ( & sql , "REINDEX" ) ;
 if ( verbose ) appendPQExpBufferStr ( & sql , " (VERBOSE)" ) ;
 if ( strcmp ( type , "TABLE" ) == 0 ) appendPQExpBuffer ( & sql , " TABLE %s" , name ) ;
 else if ( strcmp ( type , "INDEX" ) == 0 ) appendPQExpBuffer ( & sql , " INDEX %s" , name ) ;
 else if ( strcmp ( type , "SCHEMA" ) == 0 ) appendPQExpBuffer ( & sql , " SCHEMA %s" , name ) ;
 else if ( strcmp ( type , "DATABASE" ) == 0 ) appendPQExpBuffer ( & sql , " DATABASE %s" , fmtId ( PQdb ( conn ) ) ) ;
 appendPQExpBufferChar ( & sql , ';
' ) ;
 if ( ! executeMaintenanceCommand ( conn , sql . data , echo ) ) {
 if ( strcmp ( type , "TABLE" ) == 0 ) fprintf ( stderr , _ ( "%s: reindexing of table \"%s\" in database \"%s\" failed: %s" ) , progname , name , PQdb ( conn ) , PQerrorMessage ( conn ) ) ;
 if ( strcmp ( type , "INDEX" ) == 0 ) fprintf ( stderr , _ ( "%s: reindexing of index \"%s\" in database \"%s\" failed: %s" ) , progname , name , PQdb ( conn ) , PQerrorMessage ( conn ) ) ;
 if ( strcmp ( type , "SCHEMA" ) == 0 ) fprintf ( stderr , _ ( "%s: reindexing of schema \"%s\" in database \"%s\" failed: %s" ) , progname , name , PQdb ( conn ) , PQerrorMessage ( conn ) ) ;
 else fprintf ( stderr , _ ( "%s: reindexing of database \"%s\" failed: %s" ) , progname , PQdb ( conn ) , PQerrorMessage ( conn ) ) ;
 PQfinish ( conn ) ;
 exit ( 1 ) ;
 }
 PQfinish ( conn ) ;
 termPQExpBuffer ( & sql ) ;
 }