static void _doSetSessionAuth ( ArchiveHandle * AH , const char * user ) {
 PQExpBuffer cmd = createPQExpBuffer ( ) ;
 appendPQExpBufferStr ( cmd , "SET SESSION AUTHORIZATION " ) ;
 if ( user && * user ) appendStringLiteralAHX ( cmd , user , AH ) ;
 else appendPQExpBufferStr ( cmd , "DEFAULT" ) ;
 appendPQExpBufferChar ( cmd , ';
' ) ;
 if ( RestoringToDB ( AH ) ) {
 PGresult * res ;
 res = PQexec ( AH -> connection , cmd -> data ) ;
 if ( ! res || PQresultStatus ( res ) != PGRES_COMMAND_OK ) exit_horribly ( modulename , "could not set session user to \"%s\": %s" , user , PQerrorMessage ( AH -> connection ) ) ;
 PQclear ( res ) ;
 }
 else ahprintf ( AH , "%s\n\n" , cmd -> data ) ;
 destroyPQExpBuffer ( cmd ) ;
 }