static char * memdup ( const char * src , size_t buffer_length ) {
 size_t length ;
 bool add = FALSE ;
 char * buffer ;
 if ( buffer_length ) length = buffer_length ;
 else if ( src ) {
 length = strlen ( src ) ;
 add = TRUE ;
 }
 else return strdup ( "" ) ;
 buffer = malloc ( length + add ) ;
 if ( ! buffer ) return NULL ;
 memcpy ( buffer , src , length ) ;
 if ( add ) buffer [ length ] = '\0' ;
 return buffer ;
 }