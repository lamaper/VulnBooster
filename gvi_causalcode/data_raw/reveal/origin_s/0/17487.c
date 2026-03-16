static CURLcode AddFormData ( struct FormData * * formp , enum formtype type , const void * line , size_t length , curl_off_t * size ) {
 struct FormData * newform = malloc ( sizeof ( struct FormData ) ) ;
 if ( ! newform ) return CURLE_OUT_OF_MEMORY ;
 newform -> next = NULL ;
 if ( type <= FORM_CONTENT ) {
 if ( ! length ) length = strlen ( ( char * ) line ) ;
 newform -> line = malloc ( length + 1 ) ;
 if ( ! newform -> line ) {
 free ( newform ) ;
 return CURLE_OUT_OF_MEMORY ;
 }
 memcpy ( newform -> line , line , length ) ;
 newform -> length = length ;
 newform -> line [ length ] = 0 ;
 }
 else newform -> line = ( char * ) line ;
 newform -> type = type ;
 if ( * formp ) {
 ( * formp ) -> next = newform ;
 * formp = newform ;
 }
 else * formp = newform ;
 if ( size ) {
 if ( type != FORM_FILE ) * size += length ;
 else {
 if ( ! strequal ( "-" , newform -> line ) ) {
 struct_stat file ;
 if ( ! stat ( newform -> line , & file ) && ! S_ISDIR ( file . st_mode ) ) * size += filesize ( newform -> line , file ) ;
 else return CURLE_BAD_FUNCTION_ARGUMENT ;
 }
 }
 }
 return CURLE_OK ;
 }