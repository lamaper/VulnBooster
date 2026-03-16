int keyring_is_writable ( void * token ) {
 KR_NAME r = token ;
 return r ? ( r -> read_only || ! access ( r -> fname , W_OK ) ) : 0 ;
 }