static int init_nss_hash ( struct crypto_instance * instance ) {
 if ( ! hash_to_nss [ instance -> crypto_hash_type ] ) {
 return 0 ;
 }
 instance -> nss_sym_key_sign = import_symmetric_key ( instance , SYM_KEY_TYPE_HASH ) ;
 if ( instance -> nss_sym_key_sign == NULL ) {
 return - 1 ;
 }
 return 0 ;
 }