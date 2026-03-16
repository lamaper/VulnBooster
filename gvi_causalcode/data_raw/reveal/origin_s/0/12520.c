CURLcode Curl_http_input_auth ( struct connectdata * conn , bool proxy , const char * auth ) {
 struct Curl_easy * data = conn -> data ;


 struct auth * authp ;
 if ( proxy ) {
 availp = & data -> info . proxyauthavail ;
 authp = & data -> state . authproxy ;
 }
 else {
 availp = & data -> info . httpauthavail ;
 authp = & data -> state . authhost ;
 }
 while ( * auth ) {

 if ( ( authp -> avail & CURLAUTH_NEGOTIATE ) || Curl_auth_is_spnego_supported ( ) ) {
 * availp |= CURLAUTH_NEGOTIATE ;
 authp -> avail |= CURLAUTH_NEGOTIATE ;
 if ( authp -> picked == CURLAUTH_NEGOTIATE ) {
 if ( negdata -> state == GSS_AUTHSENT || negdata -> state == GSS_AUTHNONE ) {
 CURLcode result = Curl_input_negotiate ( conn , proxy , auth ) ;
 if ( ! result ) {
 DEBUGASSERT ( ! data -> req . newurl ) ;
 data -> req . newurl = strdup ( data -> change . url ) ;
 if ( ! data -> req . newurl ) return CURLE_OUT_OF_MEMORY ;
 data -> state . authproblem = FALSE ;
 negdata -> state = GSS_AUTHRECV ;
 }
 else data -> state . authproblem = TRUE ;
 }
 }
 }
 }
 else # endif # ifdef USE_NTLM if ( checkprefix ( "NTLM" , auth ) ) {
 if ( ( authp -> avail & CURLAUTH_NTLM ) || ( authp -> avail & CURLAUTH_NTLM_WB ) || Curl_auth_is_ntlm_supported ( ) ) {
 * availp |= CURLAUTH_NTLM ;
 authp -> avail |= CURLAUTH_NTLM ;
 if ( authp -> picked == CURLAUTH_NTLM || authp -> picked == CURLAUTH_NTLM_WB ) {
 CURLcode result = Curl_input_ntlm ( conn , proxy , auth ) ;
 if ( ! result ) {
 data -> state . authproblem = FALSE ;

 * availp &= ~ CURLAUTH_NTLM ;
 authp -> avail &= ~ CURLAUTH_NTLM ;
 * availp |= CURLAUTH_NTLM_WB ;
 authp -> avail |= CURLAUTH_NTLM_WB ;
 while ( * auth && ISSPACE ( * auth ) ) auth ++ ;
 if ( checkprefix ( "NTLM" , auth ) ) {
 auth += strlen ( "NTLM" ) ;
 while ( * auth && ISSPACE ( * auth ) ) auth ++ ;
 if ( * auth ) if ( ( conn -> challenge_header = strdup ( auth ) ) == NULL ) return CURLE_OUT_OF_MEMORY ;
 }
 }

 else {
 infof ( data , "Authentication problem. Ignoring this.\n" ) ;
 data -> state . authproblem = TRUE ;
 }
 }
 }
 }
 else # endif # ifndef CURL_DISABLE_CRYPTO_AUTH if ( checkprefix ( "Digest" , auth ) ) {
 if ( ( authp -> avail & CURLAUTH_DIGEST ) != 0 ) infof ( data , "Ignoring duplicate digest auth header.\n" ) ;
 else if ( Curl_auth_is_digest_supported ( ) ) {
 CURLcode result ;
 * availp |= CURLAUTH_DIGEST ;
 authp -> avail |= CURLAUTH_DIGEST ;
 result = Curl_input_digest ( conn , proxy , auth ) ;
 if ( result ) {
 infof ( data , "Authentication problem. Ignoring this.\n" ) ;
 data -> state . authproblem = TRUE ;
 }
 }
 }
 else # endif if ( checkprefix ( "Basic" , auth ) ) {
 * availp |= CURLAUTH_BASIC ;
 authp -> avail |= CURLAUTH_BASIC ;
 if ( authp -> picked == CURLAUTH_BASIC ) {
 authp -> avail = CURLAUTH_NONE ;
 infof ( data , "Authentication problem. Ignoring this.\n" ) ;
 data -> state . authproblem = TRUE ;
 }
 }
 while ( * auth && * auth != ',' ) auth ++ ;
 if ( * auth == ',' ) auth ++ ;
 while ( * auth && ISSPACE ( * auth ) ) auth ++ ;
 }
 return CURLE_OK ;
 }