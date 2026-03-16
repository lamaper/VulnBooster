char * curl_easy_unescape ( struct Curl_easy * data , const char * string , int length , int * olen ) {
 char * str = NULL ;
 if ( length >= 0 ) {
 size_t inputlen = length ;
 size_t outputlen ;
 CURLcode res = Curl_urldecode ( data , string , inputlen , & str , & outputlen , FALSE ) ;
 if ( res ) return NULL ;
 if ( olen ) {
 if ( outputlen <= ( size_t ) INT_MAX ) * olen = curlx_uztosi ( outputlen ) ;
 else Curl_safefree ( str ) ;
 }
 }
 return str ;
 }