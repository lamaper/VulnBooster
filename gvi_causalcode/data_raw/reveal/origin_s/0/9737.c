static int init_nss_crypto ( struct crypto_instance * instance ) {
 if ( ! cipher_to_nss [ instance -> crypto_cipher_type ] ) {
 return 0 ;
 }
 instance -> nss_sym_key = import_symmetric_key ( instance , SYM_KEY_TYPE_CRYPT ) ;
 if ( instance -> nss_sym_key == NULL ) {
 return - 1 ;
 }
 return 0 ;
 }