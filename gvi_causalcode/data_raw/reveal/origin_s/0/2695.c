err_status_t srtp_kdf_clear ( srtp_kdf_t * kdf ) {
 err_status_t status ;
 status = cipher_dealloc ( kdf -> cipher ) ;
 if ( status ) return status ;
 kdf -> cipher = NULL ;
 return err_status_ok ;
 }