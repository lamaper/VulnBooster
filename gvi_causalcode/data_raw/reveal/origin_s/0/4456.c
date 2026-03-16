static int strip_surrounding ( char * str , char c1 , char c2 ) {
 char * ptr = str ;
 while ( * ptr && my_isspace ( charset_info , * ptr ) ) ptr ++ ;
 if ( * ptr == c1 ) {
 * ptr = ' ' ;
 ptr = strend ( str ) - 1 ;
 while ( * ptr && my_isspace ( charset_info , * ptr ) ) ptr -- ;
 if ( * ptr == c2 ) {
 * ptr = 0 ;
 }
 else {
 return 1 ;
 }
 }
 return 0 ;
 }