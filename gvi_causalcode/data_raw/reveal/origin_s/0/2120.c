void appendShellString ( PQExpBuffer buf , const char * str ) {
 const char * p ;

 for ( p = str ;
 * p ;
 p ++ ) {
 if ( * p == '\n' || * p == '\r' ) {
 fprintf ( stderr , _ ( "shell command argument contains a newline or carriage return: \"%s\"\n" ) , str ) ;
 exit ( EXIT_FAILURE ) ;
 }
 if ( * p == '\'' ) appendPQExpBufferStr ( buf , "'\"'\"'" ) ;
 else appendPQExpBufferChar ( buf , * p ) ;
 }
 appendPQExpBufferChar ( buf , '\'' ) ;

 appendPQExpBufferStr ( buf , "^\"" ) ;
 for ( p = str ;
 * p ;
 p ++ ) {
 if ( * p == '\n' || * p == '\r' ) {
 fprintf ( stderr , _ ( "shell command argument contains a newline or carriage return: \"%s\"\n" ) , str ) ;
 exit ( EXIT_FAILURE ) ;
 }
 if ( * p == '"' ) {
 while ( backslash_run_length ) {
 appendPQExpBufferStr ( buf , "^\\" ) ;
 backslash_run_length -- ;
 }
 appendPQExpBufferStr ( buf , "^\\" ) ;
 }
 else if ( * p == '\\' ) backslash_run_length ++ ;
 else backslash_run_length = 0 ;
 if ( ! ( ( * p >= 'a' && * p <= 'z' ) || ( * p >= 'A' && * p <= 'Z' ) || ( * p >= '0' && * p <= '9' ) ) ) appendPQExpBufferChar ( buf , '^' ) ;
 appendPQExpBufferChar ( buf , * p ) ;
 }
 while ( backslash_run_length ) {
 appendPQExpBufferStr ( buf , "^\\" ) ;
 backslash_run_length -- ;
 }
 appendPQExpBufferStr ( buf , "^\"" ) ;
