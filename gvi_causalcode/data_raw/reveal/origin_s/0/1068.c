const char * TSRedirectUrlGet ( TSHttpTxn txnp , int * url_len_ptr ) {
 return TSHttpTxnRedirectUrlGet ( txnp , url_len_ptr ) ;
 }