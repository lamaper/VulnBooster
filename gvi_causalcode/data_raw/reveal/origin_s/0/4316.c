static const char * fix_for_comment ( const char * ident ) {
 static char buf [ 1024 ] ;
 char c , * s = buf ;
 while ( ( c = * s ++ = * ident ++ ) ) {
 if ( s >= buf + sizeof ( buf ) - 10 ) {
 strmov ( s , "..." ) ;
 break ;
 }
 if ( c == '\n' ) s = strmov ( s , "-- " ) ;
 }
 return buf ;
 }