static CURLcode glob_range ( URLGlob * glob , char * * patternp , size_t * posp , unsigned long * amount , int globindex ) {
 URLPattern * pat ;
 int rc ;
 char * pattern = * patternp ;
 char * c ;
 pat = & glob -> pattern [ glob -> size ] ;
 pat -> globindex = globindex ;
 if ( ISALPHA ( * pattern ) ) {
 char min_c ;
 char max_c ;
 int step = 1 ;
 pat -> type = UPTCharRange ;
 rc = sscanf ( pattern , "%c-%c" , & min_c , & max_c ) ;
 if ( ( rc == 2 ) && ( pattern [ 3 ] == ':' ) ) {
 char * endp ;
 unsigned long lstep ;
 errno = 0 ;
 lstep = strtoul ( & pattern [ 4 ] , & endp , 10 ) ;
 if ( errno || ( * endp != ']' ) ) step = - 1 ;
 else {
 pattern = endp + 1 ;
 step = ( int ) lstep ;
 if ( step > ( max_c - min_c ) ) step = - 1 ;
 }
 }
 else pattern += 4 ;
 * posp += ( pattern - * patternp ) ;
 if ( ( rc != 2 ) || ( min_c >= max_c ) || ( ( max_c - min_c ) > ( 'z' - 'a' ) ) || ( step <= 0 ) ) return GLOBERROR ( "bad range" , * posp , CURLE_URL_MALFORMAT ) ;
 pat -> content . CharRange . step = step ;
 pat -> content . CharRange . ptr_c = pat -> content . CharRange . min_c = min_c ;
 pat -> content . CharRange . max_c = max_c ;
 if ( multiply ( amount , ( pat -> content . CharRange . max_c - pat -> content . CharRange . min_c ) / pat -> content . CharRange . step + 1 ) ) return GLOBERROR ( "range overflow" , * posp , CURLE_URL_MALFORMAT ) ;
 }
 else if ( ISDIGIT ( * pattern ) ) {
 unsigned long min_n ;
 unsigned long max_n = 0 ;
 unsigned long step_n = 0 ;
 char * endp ;
 pat -> type = UPTNumRange ;
 pat -> content . NumRange . padlength = 0 ;
 if ( * pattern == '0' ) {
 c = pattern ;
 while ( ISDIGIT ( * c ) ) {
 c ++ ;
 ++ pat -> content . NumRange . padlength ;
 }
 }
 errno = 0 ;
 min_n = strtoul ( pattern , & endp , 10 ) ;
 if ( errno || ( endp == pattern ) ) endp = NULL ;
 else {
 if ( * endp != '-' ) endp = NULL ;
 else {
 pattern = endp + 1 ;
 errno = 0 ;
 max_n = strtoul ( pattern , & endp , 10 ) ;
 if ( errno || ( * endp == ':' ) ) {
 pattern = endp + 1 ;
 errno = 0 ;
 step_n = strtoul ( pattern , & endp , 10 ) ;
 if ( errno ) endp = NULL ;
 }
 else step_n = 1 ;
 if ( endp && ( * endp == ']' ) ) {
 pattern = endp + 1 ;
 }
 else endp = NULL ;
 }
 }
 * posp += ( pattern - * patternp ) ;
 if ( ! endp || ( min_n > max_n ) || ( step_n > ( max_n - min_n ) ) || ! step_n ) return GLOBERROR ( "bad range" , * posp , CURLE_URL_MALFORMAT ) ;
 pat -> content . NumRange . ptr_n = pat -> content . NumRange . min_n = min_n ;
 pat -> content . NumRange . max_n = max_n ;
 pat -> content . NumRange . step = step_n ;
 if ( multiply ( amount , ( pat -> content . NumRange . max_n - pat -> content . NumRange . min_n ) / pat -> content . NumRange . step + 1 ) ) return GLOBERROR ( "range overflow" , * posp , CURLE_URL_MALFORMAT ) ;
 }
 else return GLOBERROR ( "bad range specification" , * posp , CURLE_URL_MALFORMAT ) ;
 * patternp = pattern ;
 return CURLE_OK ;
 }