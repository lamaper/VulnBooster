CURLcode Curl_gmtime ( time_t intime , struct tm * store ) {
 const struct tm * tm ;


 if ( tm ) * store = * tm ;

 return CURLE_OK ;
 }