static char * formboundary ( struct SessionHandle * data ) {
 return aprintf ( "------------------------%08x%08x" , Curl_rand ( data ) , Curl_rand ( data ) ) ;
 }