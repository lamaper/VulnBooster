static void _selectTablespace ( ArchiveHandle * AH , const char * tablespace ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 PQExpBuffer qry ;
 const char * want , * have ;
 if ( ropt -> noTablespace ) return ;
 have = AH -> currTablespace ;
 want = tablespace ;
 if ( ! want ) return ;
 if ( have && strcmp ( want , have ) == 0 ) return ;
 qry = createPQExpBuffer ( ) ;
 if ( strcmp ( want , "" ) == 0 ) {
 appendPQExpBufferStr ( qry , "SET default_tablespace = ''" ) ;
 }
 else {
 appendPQExpBuffer ( qry , "SET default_tablespace = %s" , fmtId ( want ) ) ;
 }
 if ( RestoringToDB ( AH ) ) {
 PGresult * res ;
 res = PQexec ( AH -> connection , qry -> data ) ;
 if ( ! res || PQresultStatus ( res ) != PGRES_COMMAND_OK ) warn_or_exit_horribly ( AH , modulename , "could not set default_tablespace to %s: %s" , fmtId ( want ) , PQerrorMessage ( AH -> connection ) ) ;
 PQclear ( res ) ;
 }
 else ahprintf ( AH , "%s;
\n\n" , qry -> data ) ;
 if ( AH -> currTablespace ) free ( AH -> currTablespace ) ;
 AH -> currTablespace = pg_strdup ( want ) ;
 destroyPQExpBuffer ( qry ) ;
 }