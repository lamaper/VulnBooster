static int nextpstoken ( IO * wrapper , real * val , char * tokbuf , int tbsize ) {
 int ch , r , i ;
 char * pt , * end ;
 float mf2pt_advance_width ;
 pt = tokbuf ;
 end = pt + tbsize - 1 ;
 while ( 1 ) {
 while ( isspace ( ch = nextch ( wrapper ) ) ) ;
 if ( ch != '%' ) break ;
 while ( ( ch = nextch ( wrapper ) ) != EOF && ch != '\r' && ch != '\n' && ch != '\f' ) if ( pt < end ) * pt ++ = ch ;
 * pt = '\0' ;
 if ( sscanf ( tokbuf , " MF2PT1: bbox %*g %*g %g %*g" , & mf2pt_advance_width ) == 1 ) wrapper -> advance_width = mf2pt_advance_width ;
 else if ( sscanf ( tokbuf , " MF2PT1: glyph_dimensions %*g %*g %g %*g" , & mf2pt_advance_width ) == 1 ) wrapper -> advance_width = mf2pt_advance_width ;
 pt = tokbuf ;
 }
 if ( ch == EOF ) return ( pt_eof ) ;
 pt = tokbuf ;
 end = pt + tbsize - 1 ;
 * pt ++ = ch ;
 * pt = '\0' ;
 if ( ch == '(' ) {
 int nest = 1 , quote = 0 ;
 while ( ( ch = nextch ( wrapper ) ) != EOF ) {
 if ( pt < end ) * pt ++ = ch ;
 if ( quote ) quote = 0 ;
 else if ( ch == '(' ) ++ nest ;
 else if ( ch == ')' ) {
 if ( -- nest == 0 ) break ;
 }
 else if ( ch == '\\' ) quote = 1 ;
 }
 * pt = '\0' ;
 return ( pt_string ) ;
 }
 else if ( ch == '<' ) {
 ch = nextch ( wrapper ) ;
 if ( pt < end ) * pt ++ = ch ;
 if ( ch == '>' ) ;
 else if ( ch != '~' ) {
 while ( ( ch = nextch ( wrapper ) ) != EOF && ch != '>' ) if ( pt < end ) * pt ++ = ch ;
 }
 else {
 int twiddle = 0 ;
 while ( ( ch = nextch ( wrapper ) ) != EOF ) {
 if ( pt < end ) * pt ++ = ch ;
 if ( ch == '~' ) twiddle = 1 ;
 else if ( twiddle && ch == '>' ) break ;
 else twiddle = 0 ;
 }
 }
 * pt = '\0' ;
 return ( pt_string ) ;
 }
 else if ( ch == ')' || ch == '>' || ch == '[' || ch == ']' || ch == '{
' || ch == '}
' ) {
 if ( ch == '{
' ) return ( pt_opencurly ) ;
 else if ( ch == '}
' ) return ( pt_closecurly ) ;
 if ( ch == '[' ) return ( pt_openarray ) ;
 else if ( ch == ']' ) return ( pt_closearray ) ;
 return ( pt_unknown ) ;
 }
 else if ( ch == '/' ) {
 pt = tokbuf ;
 while ( ( ch = nextch ( wrapper ) ) != EOF && ! isspace ( ch ) && ch != '%' && ch != '(' && ch != ')' && ch != '<' && ch != '>' && ch != '[' && ch != ']' && ch != '{
' && ch != '}
' && ch != '/' ) if ( pt < tokbuf + tbsize - 2 ) * pt ++ = ch ;
 * pt = '\0' ;
 unnextch ( ch , wrapper ) ;
 return ( pt_namelit ) ;
 }
 else {
 while ( ( ch = nextch ( wrapper ) ) != EOF && ! isspace ( ch ) && ch != '%' && ch != '(' && ch != ')' && ch != '<' && ch != '>' && ch != '[' && ch != ']' && ch != '{
' && ch != '}
' && ch != '/' ) {
 if ( pt < tokbuf + tbsize - 2 ) * pt ++ = ch ;
 }
 * pt = '\0' ;
 unnextch ( ch , wrapper ) ;
 r = strtol ( tokbuf , & end , 10 ) ;
 pt = end ;
 if ( * pt == '\0' ) {
 * val = r ;
 return ( pt_number ) ;
 }
 else if ( * pt == '#' ) {
 r = strtol ( pt + 1 , & end , r ) ;
 if ( * end == '\0' ) {
 * val = r ;
 return ( pt_number ) ;
 }
 }
 else {
 * val = strtod ( tokbuf , & end ) ;
 if ( ! isfinite ( * val ) ) {
 LogError ( _ ( "Bad number, infinity or nan: %s\n" ) , tokbuf ) ;
 * val = 0 ;
 }
 if ( * end == '\0' ) return ( pt_number ) ;
 }
 for ( i = 0 ;
 toknames [ i ] != NULL ;
 ++ i ) if ( strcmp ( tokbuf , toknames [ i ] ) == 0 ) return ( i ) ;
 return ( pt_unknown ) ;
 }
 }