bool send_metakey ( connection_t * c ) {
 bool x ;
 int len = RSA_size ( c -> rsa_key ) ;
 char buffer [ 2 * len + 1 ] ;
 c -> outkey = xrealloc ( c -> outkey , len ) ;
 if ( ! c -> outctx ) {
 c -> outctx = EVP_CIPHER_CTX_new ( ) ;
 if ( ! c -> outctx ) {
 abort ( ) ;
 }
 }
 if ( 1 != RAND_bytes ( ( unsigned char * ) c -> outkey , len ) ) {
 int err = ERR_get_error ( ) ;
 logger ( LOG_ERR , "Failed to generate meta key (%s)" , ERR_error_string ( err , NULL ) ) ;
 return false ;
 }
 c -> outkey [ 0 ] &= 0x7F ;
 ifdebug ( SCARY_THINGS ) {
 bin2hex ( c -> outkey , buffer , len ) ;
 buffer [ len * 2 ] = '\0' ;
 logger ( LOG_DEBUG , "Generated random meta key (unencrypted): %s" , buffer ) ;
 }
 if ( RSA_public_encrypt ( len , ( unsigned char * ) c -> outkey , ( unsigned char * ) buffer , c -> rsa_key , RSA_NO_PADDING ) != len ) {
 logger ( LOG_ERR , "Error during encryption of meta key for %s (%s): %s" , c -> name , c -> hostname , ERR_error_string ( ERR_get_error ( ) , NULL ) ) ;
 return false ;
 }
 bin2hex ( buffer , buffer , len ) ;
 buffer [ len * 2 ] = '\0' ;
 x = send_request ( c , "%d %d %d %d %d %s" , METAKEY , c -> outcipher ? EVP_CIPHER_nid ( c -> outcipher ) : 0 , c -> outdigest ? EVP_MD_type ( c -> outdigest ) : 0 , c -> outmaclength , c -> outcompression , buffer ) ;
 if ( c -> outcipher ) {
 if ( ! EVP_EncryptInit ( c -> outctx , c -> outcipher , ( unsigned char * ) c -> outkey + len - EVP_CIPHER_key_length ( c -> outcipher ) , ( unsigned char * ) c -> outkey + len - EVP_CIPHER_key_length ( c -> outcipher ) - EVP_CIPHER_iv_length ( c -> outcipher ) ) ) {
 logger ( LOG_ERR , "Error during initialisation of cipher for %s (%s): %s" , c -> name , c -> hostname , ERR_error_string ( ERR_get_error ( ) , NULL ) ) ;
 return false ;
 }
 c -> outbudget = byte_budget ( c -> outcipher ) ;
 c -> status . encryptout = true ;
 }
 return x ;
 }