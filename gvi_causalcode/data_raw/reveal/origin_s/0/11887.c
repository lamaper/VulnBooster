char * Curl_formpostheader ( void * formp , size_t * len ) {
 char * header ;
 struct Form * form = ( struct Form * ) formp ;
 if ( ! form -> data ) return 0 ;
 header = form -> data -> line ;
 * len = form -> data -> length ;
 form -> data = form -> data -> next ;
 return header ;
 }