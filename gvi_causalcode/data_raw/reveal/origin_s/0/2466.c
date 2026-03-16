static int http_should_fail ( struct connectdata * conn ) {
 struct Curl_easy * data ;
 int httpcode ;
 DEBUGASSERT ( conn ) ;
 data = conn -> data ;
 DEBUGASSERT ( data ) ;
 httpcode = data -> req . httpcode ;
 if ( ! data -> set . http_fail_on_error ) return 0 ;
 if ( httpcode < 400 ) return 0 ;
 if ( ( httpcode != 401 ) && ( httpcode != 407 ) ) return 1 ;
 DEBUGASSERT ( ( httpcode == 401 ) || ( httpcode == 407 ) ) ;
 if ( ( httpcode == 401 ) && ! conn -> bits . user_passwd ) return TRUE ;
 if ( ( httpcode == 407 ) && ! conn -> bits . proxy_user_passwd ) return TRUE ;
 return data -> state . authproblem ;
 }