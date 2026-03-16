static char * w_addchar ( char * buffer , size_t * actlen , size_t * maxlen , char ch ) {
 if ( * actlen == * maxlen ) {
 char * old_buffer = buffer ;
 assert ( buffer == NULL || * maxlen != 0 ) ;
 * maxlen += W_CHUNK ;
 buffer = ( char * ) realloc ( buffer , 1 + * maxlen ) ;
 if ( buffer == NULL ) free ( old_buffer ) ;
 }
 if ( buffer != NULL ) {
 buffer [ * actlen ] = ch ;
 buffer [ ++ ( * actlen ) ] = '\0' ;
 }
 return buffer ;
 }