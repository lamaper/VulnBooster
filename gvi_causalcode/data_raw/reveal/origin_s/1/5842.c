bool metakey_h ( connection_t * c ) {
 char buffer [ MAX_STRING_SIZE ] ;
 int cipher , digest , maclength , compression ;
 int len ;
 if ( sscanf ( c -> buffer , "%*d %d %d %d %d " MAX_STRING , & cipher , & digest , & maclength , & compression , buffer ) != 5 ) {
 logger ( LOG_ERR , "Got bad %s from %s (%s)" , "METAKEY" , c -> name , c -> hostname ) ;
 return false ;
 }
 len = RSA_size ( myself -> connection -> rsa_key ) ;
 if ( strlen ( buffer ) != ( size_t ) len * 2 ) {
 logger ( LOG_ERR , "Possible intruder %s (%s): %s" , c -> name , c -> hostname , "wrong keylength" ) ;
 return false ;
 }
 c -> inkey = xrealloc ( c -> inkey , len ) ;
 if ( ! c -> inctx ) {
 c -> inctx = EVP_CIPHER_CTX_new ( ) ;
 if ( ! c -> inctx ) {
 abort ( ) ;
 }
 }
 if ( ! hex2bin ( buffer , buffer , len ) ) {
 logger ( LOG_ERR , "Got bad %s from %s(%s): %s" , "METAKEY" , c -> name , c -> hostname , "invalid key" ) ;
 return false ;
 }
 if ( RSA_private_decrypt ( len , ( unsigned char * ) buffer , ( unsigned char * ) c -> inkey , myself -> connection -> rsa_key , RSA_NO_PADDING ) != len ) {
 logger ( LOG_ERR , "Error during decryption of meta key for %s (%s): %s" , c -> name , c -> hostname , ERR_error_string ( ERR_get_error ( ) , NULL ) ) ;
 return false ;
 }
 ifdebug ( SCARY_THINGS ) {
 bin2hex ( c -> inkey , buffer , len ) ;
 buffer [ len * 2 ] = '\0' ;
 logger ( LOG_DEBUG , "Received random meta key (unencrypted): %s" , buffer ) ;
 }
 if ( cipher ) {
 c -> incipher = EVP_get_cipherbynid ( cipher ) ;
 if ( ! c -> incipher ) {
 logger ( LOG_ERR , "%s (%s) uses unknown cipher!" , c -> name , c -> hostname ) ;
 return false ;
 }
 if ( ! EVP_DecryptInit ( c -> inctx , c -> incipher , ( unsigned char * ) c -> inkey + len - EVP_CIPHER_key_length ( c -> incipher ) , ( unsigned char * ) c -> inkey + len - EVP_CIPHER_key_length ( c -> incipher ) - EVP_CIPHER_iv_length ( c -> incipher ) ) ) {
 logger ( LOG_ERR , "Error during initialisation of cipher from %s (%s): %s" , c -> name , c -> hostname , ERR_error_string ( ERR_get_error ( ) , NULL ) ) ;
 return false ;
 }
 c -> inbudget = byte_budget ( c -> incipher ) ;
 c -> status . decryptin = true ;
 }
 else {
 c -> incipher = NULL ;
 }
 c -> inmaclength = maclength ;
 if ( digest ) {
 c -> indigest = EVP_get_digestbynid ( digest ) ;
 if ( ! c -> indigest ) {
 logger ( LOG_ERR , "Node %s (%s) uses unknown digest!" , c -> name , c -> hostname ) ;
 return false ;
 }
 if ( c -> inmaclength > EVP_MD_size ( c -> indigest ) || c -> inmaclength < 0 ) {
 logger ( LOG_ERR , "%s (%s) uses bogus MAC length!" , c -> name , c -> hostname ) ;
 return false ;
 }
 }
 else {
 c -> indigest = NULL ;
 }
 c -> incompression = compression ;
 c -> allow_request = CHALLENGE ;
 return send_challenge ( c ) ;
 }