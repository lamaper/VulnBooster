static gpgme_error_t gpgsm_getauditlog ( void * engine , gpgme_data_t output , unsigned int flags ) {
 engine_gpgsm_t gpgsm = engine ;
 gpgme_error_t err = 0 ;
 if ( ! gpgsm || ! output ) return gpg_error ( GPG_ERR_INV_VALUE ) ;

 err = gpgsm_set_fd ( gpgsm , OUTPUT_FD , 0 ) ;
 if ( err ) return err ;
 gpgsm_clear_fd ( gpgsm , INPUT_FD ) ;
 gpgsm_clear_fd ( gpgsm , MESSAGE_FD ) ;
 gpgsm -> inline_data = NULL ;

 gpgsm_clear_fd ( gpgsm , INPUT_FD ) ;
 gpgsm_clear_fd ( gpgsm , MESSAGE_FD ) ;
 gpgsm -> inline_data = output ;

 return err ;
 }