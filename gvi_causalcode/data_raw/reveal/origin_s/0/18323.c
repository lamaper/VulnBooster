char * curl_easy_escape ( struct Curl_easy * data , const char * string , int inlength ) {
 size_t alloc ;
 char * ns ;
 char * testing_ptr = NULL ;
 unsigned char in ;
 size_t newlen ;
 size_t strindex = 0 ;
 size_t length ;
 CURLcode result ;
 if ( inlength < 0 ) return NULL ;
 alloc = ( inlength ? ( size_t ) inlength : strlen ( string ) ) + 1 ;
 newlen = alloc ;
 ns = malloc ( alloc ) ;
 if ( ! ns ) return NULL ;
 length = alloc - 1 ;
 while ( length -- ) {
 in = * string ;
 if ( Curl_isunreserved ( in ) ) ns [ strindex ++ ] = in ;
 else {
 newlen += 2 ;
 if ( newlen > alloc ) {
 alloc *= 2 ;
 testing_ptr = realloc ( ns , alloc ) ;
 if ( ! testing_ptr ) {
 free ( ns ) ;
 return NULL ;
 }
 else {
 ns = testing_ptr ;
 }
 }
 result = Curl_convert_to_network ( data , & in , 1 ) ;
 if ( result ) {
 free ( ns ) ;
 return NULL ;
 }
 snprintf ( & ns [ strindex ] , 4 , "%%%02X" , in ) ;
 strindex += 3 ;
 }
 string ++ ;
 }
 ns [ strindex ] = 0 ;
 return ns ;
 }