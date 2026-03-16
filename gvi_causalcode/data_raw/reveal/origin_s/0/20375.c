void appendPsqlMetaConnect ( PQExpBuffer buf , const char * dbname ) {
 const char * s ;
 bool complex ;
 complex = false ;
 for ( s = dbname ;
 * s ;
 s ++ ) {
 if ( * s == '\n' || * s == '\r' ) {
 fprintf ( stderr , _ ( "database name contains a newline or carriage return: \"%s\"\n" ) , dbname ) ;
 exit ( EXIT_FAILURE ) ;
 }
 if ( ! ( ( * s >= 'a' && * s <= 'z' ) || ( * s >= 'A' && * s <= 'Z' ) || ( * s >= '0' && * s <= '9' ) || * s == '_' || * s == '.' ) ) {
 complex = true ;
 }
 }
 appendPQExpBufferStr ( buf , "\\connect " ) ;
 if ( complex ) {
 PQExpBufferData connstr ;
 initPQExpBuffer ( & connstr ) ;
 appendPQExpBuffer ( & connstr , "dbname=" ) ;
 appendConnStrVal ( & connstr , dbname ) ;
 appendPQExpBuffer ( buf , "-reuse-previous=on " ) ;
 appendPQExpBufferStr ( buf , fmtId ( connstr . data ) ) ;
 termPQExpBuffer ( & connstr ) ;
 }
 else appendPQExpBufferStr ( buf , fmtId ( dbname ) ) ;
 appendPQExpBufferChar ( buf , '\n' ) ;
 }