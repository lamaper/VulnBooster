static size_t unquote_string ( const char * string , size_t length , unsigned char * buf ) {
 int esc = 0 ;
 const unsigned char * s = ( const unsigned char * ) string ;
 unsigned char * d = buf ;
 size_t n = length ;
 for ( ;
 n ;
 n -- , s ++ ) {
 if ( esc ) {
 switch ( * s ) {
 case 'b' : * d ++ = '\b' ;
 break ;
 case 't' : * d ++ = '\t' ;
 break ;
 case 'v' : * d ++ = '\v' ;
 break ;
 case 'n' : * d ++ = '\n' ;
 break ;
 case 'f' : * d ++ = '\f' ;
 break ;
 case 'r' : * d ++ = '\r' ;
 break ;
 case '"' : * d ++ = '\"' ;
 break ;
 case '\'' : * d ++ = '\'' ;
 break ;
 case '\\' : * d ++ = '\\' ;
 break ;
 case '\r' : if ( n > 1 && s [ 1 ] == '\n' ) {
 s ++ ;
 n -- ;
 }
 break ;
 case '\n' : if ( n > 1 && s [ 1 ] == '\r' ) {
 s ++ ;
 n -- ;
 }
 break ;
 case 'x' : if ( n > 2 && hexdigitp ( s + 1 ) && hexdigitp ( s + 2 ) ) {
 s ++ ;
 n -- ;
 * d ++ = xtoi_2 ( s ) ;
 s ++ ;
 n -- ;
 }
 break ;
 default : if ( n > 2 && octdigitp ( s ) && octdigitp ( s + 1 ) && octdigitp ( s + 2 ) ) {
 * d ++ = ( atoi_1 ( s ) * 64 ) + ( atoi_1 ( s + 1 ) * 8 ) + atoi_1 ( s + 2 ) ;
 s += 2 ;
 n -= 2 ;
 }
 break ;
 }
 esc = 0 ;
 }
 else if ( * s == '\\' ) esc = 1 ;
 else * d ++ = * s ;
 }
 return d - buf ;
 }