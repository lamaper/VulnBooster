err_status_t srtp_shutdown ( ) {
 err_status_t status ;
 status = crypto_kernel_shutdown ( ) ;
 if ( status ) return status ;
 return err_status_ok ;
 }