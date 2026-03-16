static gpgme_error_t start ( engine_gpgsm_t gpgsm , const char * command ) {
 gpgme_error_t err ;
 assuan_fd_t afdlist [ 5 ] ;
 int fdlist [ 5 ] ;
 int nfds ;
 int i ;
 nfds = assuan_get_active_fds ( gpgsm -> assuan_ctx , 0 , afdlist , DIM ( afdlist ) ) ;
 if ( nfds < 1 ) return gpg_error ( GPG_ERR_GENERAL ) ;
 for ( i = 0 ;
 i < nfds ;
 i ++ ) fdlist [ i ] = ( int ) afdlist [ i ] ;
 gpgsm -> status_cb . fd = _gpgme_io_dup ( fdlist [ 0 ] ) ;
 if ( gpgsm -> status_cb . fd < 0 ) return gpg_error_from_syserror ( ) ;
 if ( _gpgme_io_set_close_notify ( gpgsm -> status_cb . fd , close_notify_handler , gpgsm ) ) {
 _gpgme_io_close ( gpgsm -> status_cb . fd ) ;
 gpgsm -> status_cb . fd = - 1 ;
 return gpg_error ( GPG_ERR_GENERAL ) ;
 }
 err = add_io_cb ( gpgsm , & gpgsm -> status_cb , status_handler ) ;
 if ( ! err && gpgsm -> input_cb . fd != - 1 ) err = add_io_cb ( gpgsm , & gpgsm -> input_cb , _gpgme_data_outbound_handler ) ;
 if ( ! err && gpgsm -> output_cb . fd != - 1 ) err = add_io_cb ( gpgsm , & gpgsm -> output_cb , _gpgme_data_inbound_handler ) ;
 if ( ! err && gpgsm -> message_cb . fd != - 1 ) err = add_io_cb ( gpgsm , & gpgsm -> message_cb , _gpgme_data_outbound_handler ) ;
 if ( ! err ) err = assuan_write_line ( gpgsm -> assuan_ctx , command ) ;
 if ( ! err ) gpgsm_io_event ( gpgsm , GPGME_EVENT_START , NULL ) ;
 return err ;
 }