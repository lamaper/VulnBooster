static char * fix_path_separator ( char * path ) {

 char * c ;
 result = pg_strdup ( path ) ;
 for ( c = result ;
 * c != '\0' ;
 c ++ ) if ( * c == '/' ) * c = '\\' ;
 return result ;

