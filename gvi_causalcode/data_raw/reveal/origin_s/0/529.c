bool send_challenge ( connection_t * c ) {
 int len = RSA_size ( c -> rsa_key ) ;
 char buffer [ 2 * len + 1 ] ;
 c -> hischallenge = xrealloc ( c -> hischallenge , len ) ;
 if ( 1 != RAND_bytes ( ( unsigned char * ) c -> hischallenge , len ) ) {
 int err = ERR_get_error ( ) ;
 logger ( LOG_ERR , "Failed to generate challenge (%s)" , ERR_error_string ( err , NULL ) ) ;
 return false ;
 }
 bin2hex ( c -> hischallenge , buffer , len ) ;
 buffer [ len * 2 ] = '\0' ;
 return send_request ( c , "%d %s" , CHALLENGE , buffer ) ;
 }