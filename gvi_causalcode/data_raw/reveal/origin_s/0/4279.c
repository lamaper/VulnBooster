bool CreateReplicationSlot ( PGconn * conn , const char * slot_name , const char * plugin , bool is_physical , bool slot_exists_ok ) {
 PQExpBuffer query ;
 PGresult * res ;
 query = createPQExpBuffer ( ) ;
 Assert ( ( is_physical && plugin == NULL ) || ( ! is_physical && plugin != NULL ) ) ;
 Assert ( slot_name != NULL ) ;
 if ( is_physical ) appendPQExpBuffer ( query , "CREATE_REPLICATION_SLOT \"%s\" PHYSICAL" , slot_name ) ;
 else appendPQExpBuffer ( query , "CREATE_REPLICATION_SLOT \"%s\" LOGICAL \"%s\"" , slot_name , plugin ) ;
 res = PQexec ( conn , query -> data ) ;
 if ( PQresultStatus ( res ) != PGRES_TUPLES_OK ) {
 const char * sqlstate = PQresultErrorField ( res , PG_DIAG_SQLSTATE ) ;
 if ( slot_exists_ok && sqlstate && strcmp ( sqlstate , ERRCODE_DUPLICATE_OBJECT ) == 0 ) {
 destroyPQExpBuffer ( query ) ;
 PQclear ( res ) ;
 return true ;
 }
 else {
 fprintf ( stderr , _ ( "%s: could not send replication command \"%s\": %s" ) , progname , query -> data , PQerrorMessage ( conn ) ) ;
 destroyPQExpBuffer ( query ) ;
 PQclear ( res ) ;
 return false ;
 }
 }
 if ( PQntuples ( res ) != 1 || PQnfields ( res ) != 4 ) {
 fprintf ( stderr , _ ( "%s: could not create replication slot \"%s\": got %d rows and %d fields, expected %d rows and %d fields\n" ) , progname , slot_name , PQntuples ( res ) , PQnfields ( res ) , 1 , 4 ) ;
 destroyPQExpBuffer ( query ) ;
 PQclear ( res ) ;
 return false ;
 }
 destroyPQExpBuffer ( query ) ;
 PQclear ( res ) ;
 return true ;
 }