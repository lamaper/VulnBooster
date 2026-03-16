err_status_t srtp_kdf_init ( srtp_kdf_t * kdf , cipher_type_id_t cipher_id , const uint8_t * key , int length ) {
 err_status_t stat ;
 stat = crypto_kernel_alloc_cipher ( cipher_id , & kdf -> cipher , length , 0 ) ;
 if ( stat ) return stat ;
 stat = cipher_init ( kdf -> cipher , key ) ;
 if ( stat ) {
 cipher_dealloc ( kdf -> cipher ) ;
 return stat ;
 }
 return err_status_ok ;
 }