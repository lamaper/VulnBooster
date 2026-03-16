bool challenge_h ( connection_t * c ) {
 char buffer [ MAX_STRING_SIZE ] ;
 int len ;
 if ( sscanf ( c -> buffer , "%*d " MAX_STRING , buffer ) != 1 ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s)" , "CHALLENGE" , c -> name , c -> hostname ) ;
 return false ;
 }
 len = RSA_size ( myself -> connection -> rsa_key ) ;
 if ( strlen ( buffer ) != ( size_t ) len * 2 ) {
 logger ( LOG_ERR , "Possible intruder %s (%s): %s" , c -> name , c -> hostname , "wrong challenge length" ) ;
 return false ;
 }
 c -> mychallenge = xrealloc ( c -> mychallenge , len ) ;
 if ( ! hex2bin ( buffer , c -> mychallenge , len ) ) {
 logger ( LOG_ERR , "Got bad %s from %s(%s): %s" , "CHALLENGE" , c -> name , c -> hostname , "invalid challenge" ) ;
 return false ;
 }
 c -> allow_request = CHAL_REPLY ;
 if ( c -> outgoing ) {
 return send_chal_reply ( c ) ;
 }
 else {
 return true ;
 }
 }