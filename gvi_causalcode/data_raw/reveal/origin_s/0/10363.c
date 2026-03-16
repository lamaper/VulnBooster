static char * constructConnStr ( const char * * keywords , const char * * values ) {
 PQExpBuffer buf = createPQExpBuffer ( ) ;
 char * connstr ;
 int i ;
 bool firstkeyword = true ;
 for ( i = 0 ;
 keywords [ i ] != NULL ;
 i ++ ) {
 if ( strcmp ( keywords [ i ] , "dbname" ) == 0 || strcmp ( keywords [ i ] , "password" ) == 0 || strcmp ( keywords [ i ] , "fallback_application_name" ) == 0 ) continue ;
 if ( ! firstkeyword ) appendPQExpBufferChar ( buf , ' ' ) ;
 firstkeyword = false ;
 appendPQExpBuffer ( buf , "%s=" , keywords [ i ] ) ;
 appendConnStrVal ( buf , values [ i ] ) ;
 }
 connstr = pg_strdup ( buf -> data ) ;
 destroyPQExpBuffer ( buf ) ;
 return connstr ;
 }