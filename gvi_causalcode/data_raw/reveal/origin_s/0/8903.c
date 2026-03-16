CURLcode glob_url ( URLGlob * * glob , char * url , unsigned long * urlnum , FILE * error ) {
 URLGlob * glob_expand ;
 unsigned long amount = 0 ;
 char * glob_buffer ;
 CURLcode res ;
 * glob = NULL ;
 glob_buffer = malloc ( strlen ( url ) + 1 ) ;
 if ( ! glob_buffer ) return CURLE_OUT_OF_MEMORY ;
 glob_expand = calloc ( 1 , sizeof ( URLGlob ) ) ;
 if ( ! glob_expand ) {
 Curl_safefree ( glob_buffer ) ;
 return CURLE_OUT_OF_MEMORY ;
 }
 glob_expand -> urllen = strlen ( url ) ;
 glob_expand -> glob_buffer = glob_buffer ;
 res = glob_parse ( glob_expand , url , 1 , & amount ) ;
 if ( ! res ) * urlnum = amount ;
 else {
 if ( error && glob_expand -> error ) {
 char text [ 128 ] ;
 const char * t ;
 if ( glob_expand -> pos ) {
 snprintf ( text , sizeof ( text ) , "%s in column %zu" , glob_expand -> error , glob_expand -> pos ) ;
 t = text ;
 }
 else t = glob_expand -> error ;
 fprintf ( error , "curl: (%d) [globbing] %s\n" , res , t ) ;
 }
 glob_cleanup ( glob_expand ) ;
 * urlnum = 1 ;
 return res ;
 }
 * glob = glob_expand ;
 return CURLE_OK ;
 }