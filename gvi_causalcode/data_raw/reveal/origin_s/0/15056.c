bool RunIdentifySystem ( PGconn * conn , char * * sysid , TimeLineID * starttli , XLogRecPtr * startpos , char * * db_name ) {
 PGresult * res ;
 uint32 hi , lo ;
 Assert ( conn != NULL ) ;
 res = PQexec ( conn , "IDENTIFY_SYSTEM" ) ;
 if ( PQresultStatus ( res ) != PGRES_TUPLES_OK ) {
 fprintf ( stderr , _ ( "%s: could not send replication command \"%s\": %s" ) , progname , "IDENTIFY_SYSTEM" , PQerrorMessage ( conn ) ) ;
 PQclear ( res ) ;
 return false ;
 }
 if ( PQntuples ( res ) != 1 || PQnfields ( res ) < 3 ) {
 fprintf ( stderr , _ ( "%s: could not identify system: got %d rows and %d fields, expected %d rows and %d or more fields\n" ) , progname , PQntuples ( res ) , PQnfields ( res ) , 1 , 3 ) ;
 PQclear ( res ) ;
 return false ;
 }
 if ( sysid != NULL ) * sysid = pg_strdup ( PQgetvalue ( res , 0 , 0 ) ) ;
 if ( starttli != NULL ) * starttli = atoi ( PQgetvalue ( res , 0 , 1 ) ) ;
 if ( startpos != NULL ) {
 if ( sscanf ( PQgetvalue ( res , 0 , 2 ) , "%X/%X" , & hi , & lo ) != 2 ) {
 fprintf ( stderr , _ ( "%s: could not parse transaction log location \"%s\"\n" ) , progname , PQgetvalue ( res , 0 , 2 ) ) ;
 PQclear ( res ) ;
 return false ;
 }
 * startpos = ( ( uint64 ) hi ) << 32 | lo ;
 }
 if ( db_name != NULL ) {
 * db_name = NULL ;
 if ( PQserverVersion ( conn ) >= 90400 ) {
 if ( PQnfields ( res ) < 4 ) {
 fprintf ( stderr , _ ( "%s: could not identify system: got %d rows and %d fields, expected %d rows and %d or more fields\n" ) , progname , PQntuples ( res ) , PQnfields ( res ) , 1 , 4 ) ;
 PQclear ( res ) ;
 return false ;
 }
 if ( ! PQgetisnull ( res , 0 , 3 ) ) * db_name = pg_strdup ( PQgetvalue ( res , 0 , 3 ) ) ;
 }
 }
 PQclear ( res ) ;
 return true ;
 }