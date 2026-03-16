int ExecuteSqlCommandBuf ( Archive * AHX , const char * buf , size_t bufLen ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 if ( AH -> outputKind == OUTPUT_COPYDATA ) {
 if ( AH -> pgCopyIn && PQputCopyData ( AH -> connection , buf , bufLen ) <= 0 ) exit_horribly ( modulename , "error returned by PQputCopyData: %s" , PQerrorMessage ( AH -> connection ) ) ;
 }
 else if ( AH -> outputKind == OUTPUT_OTHERDATA ) {
 ExecuteSimpleCommands ( AH , buf , bufLen ) ;
 }
 else {
 if ( buf [ bufLen ] == '\0' ) ExecuteSqlCommand ( AH , buf , "could not execute query" ) ;
 else {
 char * str = ( char * ) pg_malloc ( bufLen + 1 ) ;
 memcpy ( str , buf , bufLen ) ;
 str [ bufLen ] = '\0' ;
 ExecuteSqlCommand ( AH , str , "could not execute query" ) ;
 free ( str ) ;
 }
 }
 return bufLen ;
 }