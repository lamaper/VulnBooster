bool DropReplicationSlot ( PGconn * conn , const char * slot_name ) {
 PQExpBuffer query ;
 PGresult * res ;
 Assert ( slot_name != NULL ) ;
 query = createPQExpBuffer ( ) ;
 appendPQExpBuffer ( query , "DROP_REPLICATION_SLOT \"%s\"" , slot_name ) ;
 res = PQexec ( conn , query -> data ) ;
 if ( PQresultStatus ( res ) != PGRES_COMMAND_OK ) {
 fprintf ( stderr , _ ( "%s: could not send replication command \"%s\": %s" ) , progname , query -> data , PQerrorMessage ( conn ) ) ;
 destroyPQExpBuffer ( query ) ;
 PQclear ( res ) ;
 return false ;
 }
 if ( PQntuples ( res ) != 0 || PQnfields ( res ) != 0 ) {
 fprintf ( stderr , _ ( "%s: could not drop replication slot \"%s\": got %d rows and %d fields, expected %d rows and %d fields\n" ) , progname , slot_name , PQntuples ( res ) , PQnfields ( res ) , 0 , 0 ) ;
 destroyPQExpBuffer ( query ) ;
 PQclear ( res ) ;
 return false ;
 }
 destroyPQExpBuffer ( query ) ;
 PQclear ( res ) ;
 return true ;
 }