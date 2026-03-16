err_status_t srtp_kdf_generate ( srtp_kdf_t * kdf , srtp_prf_label label , uint8_t * key , unsigned int length ) {
 v128_t nonce ;
 err_status_t status ;
 v128_set_to_zero ( & nonce ) ;
 nonce . v8 [ 7 ] = label ;
 status = cipher_set_iv ( kdf -> cipher , & nonce , direction_encrypt ) ;
 if ( status ) return status ;
 octet_string_set_to_zero ( key , length ) ;
 status = cipher_encrypt ( kdf -> cipher , key , & length ) ;
 if ( status ) return status ;
 return err_status_ok ;
 }