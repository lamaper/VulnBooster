bool send_chal_reply ( connection_t * c ) {
 char hash [ EVP_MAX_MD_SIZE * 2 + 1 ] ;
 EVP_MD_CTX * ctx ;
 ctx = EVP_MD_CTX_create ( ) ;
 if ( ! ctx ) {
 abort ( ) ;
 }
 if ( ! EVP_DigestInit ( ctx , c -> indigest ) || ! EVP_DigestUpdate ( ctx , c -> mychallenge , RSA_size ( myself -> connection -> rsa_key ) ) || ! EVP_DigestFinal ( ctx , ( unsigned char * ) hash , NULL ) ) {
 EVP_MD_CTX_destroy ( ctx ) ;
 logger ( LOG_ERR , "Error during calculation of response for %s (%s): %s" , c -> name , c -> hostname , ERR_error_string ( ERR_get_error ( ) , NULL ) ) ;
 return false ;
 }
 EVP_MD_CTX_destroy ( ctx ) ;
 bin2hex ( hash , hash , EVP_MD_size ( c -> indigest ) ) ;
 hash [ EVP_MD_size ( c -> indigest ) * 2 ] = '\0' ;
 return send_request ( c , "%d %s" , CHAL_REPLY , hash ) ;
 }