static void doapr_outch ( char * * sbuffer , char * * buffer , size_t * currlen , size_t * maxlen , int c ) {
 assert ( * sbuffer != NULL || buffer != NULL ) ;
 assert ( * currlen <= * maxlen ) ;
 if ( buffer && * currlen == * maxlen ) {
 * maxlen += 1024 ;
 if ( * buffer == NULL ) {
 * buffer = OPENSSL_malloc ( * maxlen ) ;
 if ( ! * buffer ) {
 return ;
 }
 if ( * currlen > 0 ) {
 assert ( * sbuffer != NULL ) ;
 memcpy ( * buffer , * sbuffer , * currlen ) ;
 }
 * sbuffer = NULL ;
 }
 else {
 * buffer = OPENSSL_realloc ( * buffer , * maxlen ) ;
 if ( ! * buffer ) {
 return ;
 }
 }
 }
 if ( * currlen < * maxlen ) {
 if ( * sbuffer ) ( * sbuffer ) [ ( * currlen ) ++ ] = ( char ) c ;
 else ( * buffer ) [ ( * currlen ) ++ ] = ( char ) c ;
 }
 return ;
 }