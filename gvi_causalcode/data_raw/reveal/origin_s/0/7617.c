void EndDBCopyMode ( Archive * AHX , const char * tocEntryTag ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 if ( AH -> pgCopyIn ) {
 PGresult * res ;
 if ( PQputCopyEnd ( AH -> connection , NULL ) <= 0 ) exit_horribly ( modulename , "error returned by PQputCopyEnd: %s" , PQerrorMessage ( AH -> connection ) ) ;
 res = PQgetResult ( AH -> connection ) ;
 if ( PQresultStatus ( res ) != PGRES_COMMAND_OK ) warn_or_exit_horribly ( AH , modulename , "COPY failed for table \"%s\": %s" , tocEntryTag , PQerrorMessage ( AH -> connection ) ) ;
 PQclear ( res ) ;
 if ( PQgetResult ( AH -> connection ) != NULL ) write_msg ( NULL , "WARNING: unexpected extra results during COPY of table \"%s\"\n" , tocEntryTag ) ;
 AH -> pgCopyIn = false ;
 }
 }