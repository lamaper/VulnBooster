static void _becomeUser ( ArchiveHandle * AH , const char * user ) {
 if ( ! user ) user = "" ;
 if ( AH -> currUser && strcmp ( AH -> currUser , user ) == 0 ) return ;
 _doSetSessionAuth ( AH , user ) ;
 if ( AH -> currUser ) free ( AH -> currUser ) ;
 AH -> currUser = pg_strdup ( user ) ;
 }