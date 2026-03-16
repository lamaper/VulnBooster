int crypto_encrypt_and_sign ( struct crypto_instance * instance , const unsigned char * buf_in , const size_t buf_in_len , unsigned char * buf_out , size_t * buf_out_len ) {
 struct crypto_config_header * cch = ( struct crypto_config_header * ) buf_out ;
 int err ;
 cch -> crypto_cipher_type = CRYPTO_CIPHER_TYPE_2_3 ;
 cch -> crypto_hash_type = CRYPTO_HASH_TYPE_2_3 ;
 cch -> __pad0 = 0 ;
 cch -> __pad1 = 0 ;
 err = encrypt_and_sign_nss_2_3 ( instance , buf_in , buf_in_len , buf_out , buf_out_len ) ;
 return err ;
 }