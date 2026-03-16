int __glob_pattern_type ( pattern , quote ) const char * pattern ;
 int quote ;
 {
 register const char * p ;
 int ret = 0 ;
 for ( p = pattern ;
 * p != '\0' ;
 ++ p ) switch ( * p ) {
 case '?' : case '*' : return 1 ;
 case '\\' : if ( quote ) {
 if ( p [ 1 ] != '\0' ) ++ p ;
 ret |= 2 ;
 }
 break ;
 case '[' : ret |= 4 ;
 break ;
 case ']' : if ( ret & 4 ) return 1 ;
 break ;
 }
 return ret ;
 }