PGresult * ExecuteSqlQueryForSingleRow ( Archive * fout , char * query ) {
 PGresult * res ;
 int ntups ;
 res = ExecuteSqlQuery ( fout , query , PGRES_TUPLES_OK ) ;
 ntups = PQntuples ( res ) ;
 if ( ntups != 1 ) exit_horribly ( NULL , ngettext ( "query returned %d row instead of one: %s\n" , "query returned %d rows instead of one: %s\n" , ntups ) , ntups , query ) ;
 return res ;
 }