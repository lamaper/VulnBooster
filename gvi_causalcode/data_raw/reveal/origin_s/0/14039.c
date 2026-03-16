err_status_t srtp_init ( ) {
 err_status_t status ;
 status = crypto_kernel_init ( ) ;
 if ( status ) return status ;
 status = crypto_kernel_load_debug_module ( & mod_srtp ) ;
 if ( status ) return status ;
 return err_status_ok ;
 }