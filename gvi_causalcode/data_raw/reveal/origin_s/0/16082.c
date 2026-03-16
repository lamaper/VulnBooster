static void run_vacuum_command ( PGconn * conn , const char * sql , bool echo , const char * table , const char * progname , bool async ) {
 bool status ;
 if ( async ) {
 if ( echo ) printf ( "%s\n" , sql ) ;
 status = PQsendQuery ( conn , sql ) == 1 ;
 }
 else status = executeMaintenanceCommand ( conn , sql , echo ) ;
 if ( ! status ) {
 if ( table ) fprintf ( stderr , _ ( "%s: vacuuming of table \"%s\" in database \"%s\" failed: %s" ) , progname , table , PQdb ( conn ) , PQerrorMessage ( conn ) ) ;
 else fprintf ( stderr , _ ( "%s: vacuuming of database \"%s\" failed: %s" ) , progname , PQdb ( conn ) , PQerrorMessage ( conn ) ) ;
 if ( ! async ) {
 PQfinish ( conn ) ;
 exit ( 1 ) ;
 }
 }
 }