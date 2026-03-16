char * ReadStr ( ArchiveHandle * AH ) {
 char * buf ;
 int l ;
 l = ReadInt ( AH ) ;
 if ( l < 0 ) buf = NULL ;
 else {
 buf = ( char * ) pg_malloc ( l + 1 ) ;
 ( * AH -> ReadBufPtr ) ( AH , ( void * ) buf , l ) ;
 buf [ l ] = '\0' ;
 }
 return buf ;
 }