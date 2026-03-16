static char * alnumerize ( char * name ) {
 char * r = name ;
 char * w = name ;
 char c ;
 for ( ;
 ( c = * r ) ;
 r ++ ) {
 if ( g_ascii_isalnum ( c ) || c == '_' || c == '-' || c == '.' ) {
 * ( w ++ ) = c ;
 }
 }
 * w = '\0' ;
 return name ;
 }