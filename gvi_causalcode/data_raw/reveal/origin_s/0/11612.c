static void _doSetWithOids ( ArchiveHandle * AH , const bool withOids ) {
 PQExpBuffer cmd = createPQExpBuffer ( ) ;
 appendPQExpBuffer ( cmd , "SET default_with_oids = %s;
" , withOids ? "true" : "false" ) ;
 if ( RestoringToDB ( AH ) ) {
 PGresult * res ;
 res = PQexec ( AH -> connection , cmd -> data ) ;
 if ( ! res || PQresultStatus ( res ) != PGRES_COMMAND_OK ) warn_or_exit_horribly ( AH , modulename , "could not set default_with_oids: %s" , PQerrorMessage ( AH -> connection ) ) ;
 PQclear ( res ) ;
 }
 else ahprintf ( AH , "%s\n\n" , cmd -> data ) ;
 destroyPQExpBuffer ( cmd ) ;
 }