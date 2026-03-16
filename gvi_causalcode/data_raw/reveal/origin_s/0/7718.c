static void _selectOutputSchema ( ArchiveHandle * AH , const char * schemaName ) {
 PQExpBuffer qry ;
 if ( ! schemaName || * schemaName == '\0' || ( AH -> currSchema && strcmp ( AH -> currSchema , schemaName ) == 0 ) ) return ;
 qry = createPQExpBuffer ( ) ;
 appendPQExpBuffer ( qry , "SET search_path = %s" , fmtId ( schemaName ) ) ;
 if ( strcmp ( schemaName , "pg_catalog" ) != 0 ) appendPQExpBufferStr ( qry , ", pg_catalog" ) ;
 if ( RestoringToDB ( AH ) ) {
 PGresult * res ;
 res = PQexec ( AH -> connection , qry -> data ) ;
 if ( ! res || PQresultStatus ( res ) != PGRES_COMMAND_OK ) warn_or_exit_horribly ( AH , modulename , "could not set search_path to \"%s\": %s" , schemaName , PQerrorMessage ( AH -> connection ) ) ;
 PQclear ( res ) ;
 }
 else ahprintf ( AH , "%s;
\n\n" , qry -> data ) ;
 if ( AH -> currSchema ) free ( AH -> currSchema ) ;
 AH -> currSchema = pg_strdup ( schemaName ) ;
 destroyPQExpBuffer ( qry ) ;
 }