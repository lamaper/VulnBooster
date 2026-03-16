void ExecuteSqlStatement ( Archive * AHX , const char * query ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 PGresult * res ;
 res = PQexec ( AH -> connection , query ) ;
 if ( PQresultStatus ( res ) != PGRES_COMMAND_OK ) die_on_query_failure ( AH , modulename , query ) ;
 PQclear ( res ) ;
 }