PGresult * ExecuteSqlQuery ( Archive * AHX , const char * query , ExecStatusType status ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 PGresult * res ;
 res = PQexec ( AH -> connection , query ) ;
 if ( PQresultStatus ( res ) != status ) die_on_query_failure ( AH , modulename , query ) ;
 return res ;
 }