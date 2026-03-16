static char * get_arg ( char * line , get_arg_mode mode ) {
 char * ptr , * start ;
 bool short_cmd = false ;
 char qtype = 0 ;
 ptr = line ;
 if ( mode == GET_NEXT ) {
 for ( ;
 * ptr ;
 ptr ++ ) ;
 if ( * ( ptr + 1 ) ) ptr ++ ;
 }
 else {
 while ( my_isspace ( charset_info , * ptr ) ) ptr ++ ;
 if ( ( short_cmd = * ptr == '\\' ) ) ptr += 2 ;
 else while ( * ptr && ! my_isspace ( charset_info , * ptr ) ) ptr ++ ;
 }
 if ( ! * ptr ) return NullS ;
 while ( my_isspace ( charset_info , * ptr ) ) ptr ++ ;
 if ( * ptr == '\'' || * ptr == '\"' || * ptr == '`' ) {
 qtype = * ptr ;
 ptr ++ ;
 }
 for ( start = ptr ;
 * ptr ;
 ptr ++ ) {
 if ( ( * ptr == '\\' && ptr [ 1 ] ) || ( ! short_cmd && qtype && * ptr == qtype && ptr [ 1 ] == qtype ) ) {
 if ( mode != CHECK ) strmov_overlapp ( ptr , ptr + 1 ) ;
 else ptr ++ ;
 }
 else if ( * ptr == ( qtype ? qtype : ' ' ) ) {
 qtype = 0 ;
 if ( mode != CHECK ) * ptr = 0 ;
 break ;
 }
 }
 return ptr != start && ! qtype ? start : NullS ;
 }