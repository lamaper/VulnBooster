char * evhttp_htmlescape ( const char * html ) {
 int i , new_size = 0 , old_size = strlen ( html ) ;
 char * escaped_html , * p ;
 char scratch_space [ 2 ] ;
 for ( i = 0 ;
 i < old_size ;
 ++ i ) new_size += strlen ( html_replace ( html [ i ] , scratch_space ) ) ;
 p = escaped_html = malloc ( new_size + 1 ) ;
 if ( escaped_html == NULL ) event_err ( 1 , "%s: malloc(%d)" , __func__ , new_size + 1 ) ;
 for ( i = 0 ;
 i < old_size ;
 ++ i ) {
 const char * replaced = html_replace ( html [ i ] , scratch_space ) ;
 strcpy ( p , replaced ) ;
 p += strlen ( replaced ) ;
 }
 * p = '\0' ;
 return ( escaped_html ) ;
 }