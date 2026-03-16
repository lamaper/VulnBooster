static uint8 * StringToBytes ( struct psstack * stackel , int * len ) {
 char * pt ;
 uint8 * upt , * base , * ret ;
 int half , sofar , val , nesting ;
 int i , j ;
 pt = stackel -> u . str ;
 if ( stackel -> type == ps_instr ) {
 while ( isspace ( * pt ) ) ++ pt ;
 if ( * pt == '{
' || * pt == '[' ) ++ pt ;
 while ( isspace ( * pt ) ) ++ pt ;
 }
 else if ( stackel -> type != ps_string ) return ( NULL ) ;
 upt = base = malloc ( 65536 + 1 ) ;
 if ( * pt == '(' ) {
 ++ pt ;
 nesting = 0 ;
 while ( * pt != '\0' && ( nesting != 0 || * pt != ')' ) ) {
 if ( * pt == '(' ) {
 ++ nesting ;
 * upt ++ = * pt ++ ;
 }
 else if ( * pt == ')' ) {
 -- nesting ;
 * upt ++ = * pt ++ ;
 }
 else if ( * pt == '\r' || * pt == '\n' ) {
 if ( * pt == '\r' && pt [ 1 ] == '\n' ) ++ pt ;
 * upt ++ = '\n' ;
 ++ pt ;
 }
 else if ( * pt != '\\' ) {
 * upt ++ = * pt ++ ;
 }
 else {
 ++ pt ;
 if ( * pt == '\r' || * pt == '\n' ) {
 if ( * pt == '\r' && pt [ 1 ] == '\n' ) ++ pt ;
 ++ pt ;
 }
 else if ( * pt == 'n' ) {
 * upt ++ = '\n' ;
 ++ pt ;
 }
 else if ( * pt == 'r' ) {
 * upt ++ = '\r' ;
 ++ pt ;
 }
 else if ( * pt == 't' ) {
 * upt ++ = '\t' ;
 ++ pt ;
 }
 else if ( * pt == 'b' ) {
 * upt ++ = '\b' ;
 ++ pt ;
 }
 else if ( * pt == 'f' ) {
 * upt ++ = '\f' ;
 ++ pt ;
 }
 else if ( * pt >= '0' && * pt <= '7' ) {
 if ( pt [ 1 ] < '0' || pt [ 1 ] > '7' ) * upt ++ = * pt ++ - '0' ;
 else if ( pt [ 2 ] < '0' || pt [ 2 ] > '7' ) {
 * upt ++ = ( ( * pt - '0' ) << 3 ) + ( pt [ 1 ] - '0' ) ;
 pt += 2 ;
 }
 else {
 * upt ++ = ( ( * pt - '0' ) << 6 ) + ( ( pt [ 1 ] - '0' ) << 3 ) + ( pt [ 2 ] - '0' ) ;
 pt += 3 ;
 }
 }
 else if ( * pt == '(' || * pt == ')' || * pt == '\\' ) * upt ++ = * pt ++ ;
 else {
 LogError ( _ ( "Unknown character after backslash in literal string.\n" ) ) ;
 * upt ++ = * pt ++ ;
 }
 }
 }
 }
 else if ( * pt != '<' ) {
 LogError ( _ ( "Unknown string type\n" ) ) ;
 free ( base ) ;
 return ( NULL ) ;
 }
 else if ( pt [ 1 ] != '~' ) {
 half = sofar = 0 ;
 ++ pt ;
 while ( * pt != '>' && * pt != '\0' ) {
 if ( * pt >= 'a' && * pt <= 'f' ) val = * pt ++ - 'a' + 10 ;
 else if ( * pt >= 'A' && * pt <= 'F' ) val = * pt ++ - 'A' + 10 ;
 else if ( isdigit ( * pt ) ) val = * pt ++ - '0' ;
 else {
 ++ pt ;
 continue ;
 }
 if ( ! half ) {
 half = true ;
 sofar = val << 4 ;
 }
 else {
 * upt ++ = sofar | val ;
 half = false ;
 }
 }
 if ( half ) * upt ++ = sofar ;
 }
 else {
 pt += 2 ;
 while ( * pt != '\0' && * pt != '~' ) {
 if ( upt - base + 4 > 65536 ) break ;
 if ( * pt == 'z' ) {
 * upt ++ = 0 ;
 * upt ++ = 0 ;
 * upt ++ = 0 ;
 * upt ++ = 0 ;
 ++ pt ;
 }
 else if ( * pt >= '!' && * pt <= 'u' ) {
 val = 0 ;
 for ( i = 0 ;
 i < 5 && * pt >= '!' && * pt <= 'u' ;
 ++ i ) val = ( val * 85 ) + * pt ++ - '!' ;
 for ( j = i ;
 j < 5 ;
 ++ j ) val *= 85 ;
 * upt ++ = val >> 24 ;
 if ( i > 2 ) * upt ++ = ( val >> 16 ) & 0xff ;
 if ( i > 3 ) * upt ++ = ( val >> 8 ) & 0xff ;
 if ( i > 4 ) * upt ++ = val & 0xff ;
 if ( i < 5 ) break ;
 }
 else if ( isspace ( * pt ) ) {
 ++ pt ;
 }
 else break ;
 }
 }
 * len = upt - base ;
 ret = malloc ( upt - base ) ;
 memcpy ( ret , base , upt - base ) ;
 free ( base ) ;
 return ( ret ) ;
 }