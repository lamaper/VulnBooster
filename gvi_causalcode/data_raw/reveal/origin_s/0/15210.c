CURLcode Curl_http_connect ( struct connectdata * conn , bool * done ) {
 CURLcode result ;
 connkeep ( conn , "HTTP default" ) ;
 result = Curl_proxy_connect ( conn ) ;
 if ( result ) return result ;
 if ( conn -> tunnel_state [ FIRSTSOCKET ] == TUNNEL_CONNECT ) return CURLE_OK ;
 if ( conn -> given -> flags & PROTOPT_SSL ) {
 result = https_connecting ( conn , done ) ;
 if ( result ) return result ;
 }
 else * done = TRUE ;
 return CURLE_OK ;
 }