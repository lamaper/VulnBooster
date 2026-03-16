bool chal_reply_h ( connection_t * c ) {
 char hishash [ MAX_STRING_SIZE ] ;
 char myhash [ EVP_MAX_MD_SIZE ] ;
 EVP_MD_CTX * ctx ;
 if ( sscanf ( c -> buffer , "%*d " MAX_STRING , hishash ) != 1 ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s)" , "CHAL_REPLY" , c -> name , c -> hostname ) ;
 return false ;
 }
 if ( strlen ( hishash ) != ( size_t ) EVP_MD_size ( c -> outdigest ) * 2 ) {
 logger ( LOG_ERR , "Possible intruder %s (%s): %s" , c -> name , c -> hostname , "wrong challenge reply length" ) ;
 return false ;
 }
 if ( ! hex2bin ( hishash , hishash , EVP_MD_size ( c -> outdigest ) ) ) {
 logger ( LOG_ERR , "Got bad %s from %s(%s): %s" , "CHAL_REPLY" , c -> name , c -> hostname , "invalid hash" ) ;
 return false ;
 }
 ctx = EVP_MD_CTX_create ( ) ;
 if ( ! ctx ) {
 abort ( ) ;
 }
 if ( ! EVP_DigestInit ( ctx , c -> outdigest ) || ! EVP_DigestUpdate ( ctx , c -> hischallenge , RSA_size ( c -> rsa_key ) ) || ! EVP_DigestFinal ( ctx , ( unsigned char * ) myhash , NULL ) ) {
 EVP_MD_CTX_destroy ( ctx ) ;
 logger ( LOG_ERR , "Error during calculation of response from %s (%s): %s" , c -> name , c -> hostname , ERR_error_string ( ERR_get_error ( ) , NULL ) ) ;
 return false ;
 }
 EVP_MD_CTX_destroy ( ctx ) ;
 if ( memcmp ( hishash , myhash , EVP_MD_size ( c -> outdigest ) ) ) {
 logger ( LOG_ERR , "Possible intruder %s (%s): %s" , c -> name , c -> hostname , "wrong challenge reply" ) ;
 ifdebug ( SCARY_THINGS ) {
 bin2hex ( myhash , hishash , SHA_DIGEST_LENGTH ) ;
 hishash [ SHA_DIGEST_LENGTH * 2 ] = '\0' ;
 logger ( LOG_DEBUG , "Expected challenge reply: %s" , hishash ) ;
 }
 return false ;
 }
 c -> allow_request = ACK ;
 if ( ! c -> outgoing ) {
 send_chal_reply ( c ) ;
 }
 return send_ack ( c ) ;
 }