static void die_on_query_failure ( ArchiveHandle * AH , const char * modulename , const char * query ) {
 write_msg ( modulename , "query failed: %s" , PQerrorMessage ( AH -> connection ) ) ;
 exit_horribly ( modulename , "query was: %s\n" , query ) ;
 }