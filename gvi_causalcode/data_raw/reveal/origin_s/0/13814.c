void check_pghost_envvar ( void ) {
 PQconninfoOption * option ;
 PQconninfoOption * start ;
 start = PQconndefaults ( ) ;
 if ( ! start ) pg_fatal ( "out of memory\n" ) ;
 for ( option = start ;
 option -> keyword != NULL ;
 option ++ ) {
 if ( option -> envvar && ( strcmp ( option -> envvar , "PGHOST" ) == 0 || strcmp ( option -> envvar , "PGHOSTADDR" ) == 0 ) ) {
 const char * value = getenv ( option -> envvar ) ;
 if ( value && strlen ( value ) > 0 && ( strcmp ( value , "localhost" ) != 0 && strcmp ( value , "127.0.0.1" ) != 0 && strcmp ( value , "::1" ) != 0 && value [ 0 ] != '/' ) ) pg_fatal ( "libpq environment variable %s has a non-local server value: %s\n" , option -> envvar , value ) ;
 }
 }
 PQconninfoFree ( start ) ;
 }