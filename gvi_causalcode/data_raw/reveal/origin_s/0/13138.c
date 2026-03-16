bool send_ans_key ( node_t * to ) {
 to -> incipher = myself -> incipher ;
 to -> inkeylength = myself -> inkeylength ;
 to -> indigest = myself -> indigest ;
 to -> inmaclength = myself -> inmaclength ;
 to -> incompression = myself -> incompression ;
 to -> inkey = xrealloc ( to -> inkey , to -> inkeylength ) ;
 if ( 1 != RAND_bytes ( ( unsigned char * ) to -> inkey , to -> inkeylength ) ) {
 int err = ERR_get_error ( ) ;
 logger ( LOG_ERR , "Failed to generate random for key (%s)" , ERR_error_string ( err , NULL ) ) ;
 return false ;
 }
 if ( to -> incipher ) {
 EVP_DecryptInit_ex ( to -> inctx , to -> incipher , NULL , ( unsigned char * ) to -> inkey , ( unsigned char * ) to -> inkey + EVP_CIPHER_key_length ( to -> incipher ) ) ;
 }
 mykeyused = true ;
 to -> received_seqno = 0 ;
 if ( replaywin ) {
 memset ( to -> late , 0 , replaywin ) ;
 }
 char key [ 2 * to -> inkeylength + 1 ] ;
 bin2hex ( to -> inkey , key , to -> inkeylength ) ;
 key [ to -> inkeylength * 2 ] = '\0' ;
 return send_request ( to -> nexthop -> connection , "%d %s %s %s %d %d %d %d" , ANS_KEY , myself -> name , to -> name , key , to -> incipher ? EVP_CIPHER_nid ( to -> incipher ) : 0 , to -> indigest ? EVP_MD_type ( to -> indigest ) : 0 , to -> inmaclength , to -> incompression ) ;
 }