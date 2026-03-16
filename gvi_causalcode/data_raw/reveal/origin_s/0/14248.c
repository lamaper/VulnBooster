static uint nr_of_decimals ( const char * str , const char * end ) {
 const char * decimal_point ;
 for ( ;
 ;
 ) {
 if ( str == end ) return 0 ;
 if ( * str == 'e' || * str == 'E' ) return NOT_FIXED_DEC ;
 if ( * str ++ == '.' ) break ;
 }
 decimal_point = str ;
 for ( ;
 str < end && my_isdigit ( system_charset_info , * str ) ;
 str ++ ) ;
 if ( str < end && ( * str == 'e' || * str == 'E' ) ) return NOT_FIXED_DEC ;
 return ( uint ) ( str - decimal_point ) ;
 }