CURLcode Curl_http_output_auth ( struct connectdata * conn , const char * request , const char * path , bool proxytunnel ) {
 CURLcode result = CURLE_OK ;
 struct Curl_easy * data = conn -> data ;
 struct auth * authhost ;
 struct auth * authproxy ;
 DEBUGASSERT ( data ) ;
 authhost = & data -> state . authhost ;
 authproxy = & data -> state . authproxy ;
 if ( ( conn -> bits . httpproxy && conn -> bits . proxy_user_passwd ) || conn -> bits . user_passwd ) ;
 else {
 authhost -> done = TRUE ;
 authproxy -> done = TRUE ;
 return CURLE_OK ;
 }
 if ( authhost -> want && ! authhost -> picked ) authhost -> picked = authhost -> want ;
 if ( authproxy -> want && ! authproxy -> picked ) authproxy -> picked = authproxy -> want ;

 result = output_auth_headers ( conn , authproxy , request , path , TRUE ) ;
 if ( result ) return result ;
 }
 else # else ( void ) proxytunnel ;

 if ( ! data -> state . this_is_a_follow || conn -> bits . netrc || ! data -> state . first_host || data -> set . http_disable_hostname_check_before_authentication || Curl_raw_equal ( data -> state . first_host , conn -> host . name ) ) {
 result = output_auth_headers ( conn , authhost , request , path , FALSE ) ;
 }
 else authhost -> done = TRUE ;
 return result ;
 }