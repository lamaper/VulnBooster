int curl_formget ( struct curl_httppost * form , void * arg , curl_formget_callback append ) {
 CURLcode result ;
 curl_off_t size ;
 struct FormData * data , * ptr ;
 result = Curl_getformdata ( NULL , & data , form , NULL , & size ) ;
 if ( result ) return ( int ) result ;
 for ( ptr = data ;
 ptr ;
 ptr = ptr -> next ) {
 if ( ( ptr -> type == FORM_FILE ) || ( ptr -> type == FORM_CALLBACK ) ) {
 char buffer [ 8192 ] ;
 size_t nread ;
 struct Form temp ;
 Curl_FormInit ( & temp , ptr ) ;
 do {
 nread = readfromfile ( & temp , buffer , sizeof ( buffer ) ) ;
 if ( ( nread == ( size_t ) - 1 ) || ( nread > sizeof ( buffer ) ) || ( nread != append ( arg , buffer , nread ) ) ) {
 if ( temp . fp ) fclose ( temp . fp ) ;
 Curl_formclean ( & data ) ;
 return - 1 ;
 }
 }
 while ( nread ) ;
 }
 else {
 if ( ptr -> length != append ( arg , ptr -> line , ptr -> length ) ) {
 Curl_formclean ( & data ) ;
 return - 1 ;
 }
 }
 }
 Curl_formclean ( & data ) ;
 return 0 ;
 }