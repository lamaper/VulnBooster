static char * replace_line_endings ( const char * str ) {
 char * result ;
 char * s ;
 result = pg_strdup ( str ) ;
 for ( s = result ;
 * s != '\0' ;
 s ++ ) {
 if ( * s == '\n' || * s == '\r' ) * s = ' ' ;
 }
 return result ;
 }