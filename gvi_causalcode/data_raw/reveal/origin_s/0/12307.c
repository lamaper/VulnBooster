static bool checkhttpprefix ( struct Curl_easy * data , const char * s ) {
 struct curl_slist * head = data -> set . http200aliases ;
 bool rc = FALSE ;

 if ( NULL == scratch ) {
 failf ( data , "Failed to allocate memory for conversion!" ) ;
 return FALSE ;
 }
 if ( CURLE_OK != Curl_convert_from_network ( data , scratch , strlen ( s ) + 1 ) ) {
 free ( scratch ) ;
 return FALSE ;
 }
 s = scratch ;

 if ( checkprefix ( head -> data , s ) ) {
 rc = TRUE ;
 break ;
 }
 head = head -> next ;
 }
 if ( ! rc && ( checkprefix ( "HTTP/" , s ) ) ) rc = TRUE ;


 }