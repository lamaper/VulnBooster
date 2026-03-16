static int CheckCodePointsComment ( IO * wrapper ) {
 char commentbuffer [ 128 ] , * pt ;
 int ch ;
 while ( isspace ( ch = nextch ( wrapper ) ) ) ;
 if ( ch != '%' ) {
 unnextch ( ch , wrapper ) ;
 return ( false ) ;
 }
 pt = commentbuffer ;
 while ( ( ch = nextch ( wrapper ) ) != EOF && ch != '\r' && ch != '\n' && ch != '\f' ) {
 if ( pt - commentbuffer < ( ptrdiff_t ) sizeof ( commentbuffer ) - 1 ) * pt ++ = ch ;
 }
 * pt = '\0' ;
 if ( strcmp ( commentbuffer , " Use codepoints." ) == 0 ) return ( true ) ;
 return ( false ) ;
 }