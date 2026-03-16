static int convert_to_string ( const unsigned char * s , size_t len , char * dest ) {
 if ( dest ) {
 char * p = dest ;
 * p ++ = '\"' ;
 for ( ;
 len ;
 len -- , s ++ ) {
 switch ( * s ) {
 case '\b' : * p ++ = '\\' ;
 * p ++ = 'b' ;
 break ;
 case '\t' : * p ++ = '\\' ;
 * p ++ = 't' ;
 break ;
 case '\v' : * p ++ = '\\' ;
 * p ++ = 'v' ;
 break ;
 case '\n' : * p ++ = '\\' ;
 * p ++ = 'n' ;
 break ;
 case '\f' : * p ++ = '\\' ;
 * p ++ = 'f' ;
 break ;
 case '\r' : * p ++ = '\\' ;
 * p ++ = 'r' ;
 break ;
 case '\"' : * p ++ = '\\' ;
 * p ++ = '\"' ;
 break ;
 case '\'' : * p ++ = '\\' ;
 * p ++ = '\'' ;
 break ;
 case '\\' : * p ++ = '\\' ;
 * p ++ = '\\' ;
 break ;
 default : if ( ( * s < 0x20 || ( * s >= 0x7f && * s <= 0xa0 ) ) ) {
 sprintf ( p , "\\x%02x" , * s ) ;
 p += 4 ;
 }
 else * p ++ = * s ;
 }
 }
 * p ++ = '\"' ;
 return p - dest ;
 }
 else {
 int count = 2 ;
 for ( ;
 len ;
 len -- , s ++ ) {
 switch ( * s ) {
 case '\b' : case '\t' : case '\v' : case '\n' : case '\f' : case '\r' : case '\"' : case '\'' : case '\\' : count += 2 ;
 break ;
 default : if ( ( * s < 0x20 || ( * s >= 0x7f && * s <= 0xa0 ) ) ) count += 4 ;
 else count ++ ;
 }
 }
 return count ;
 }
 }