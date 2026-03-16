static gpgme_error_t gpgsm_set_fd ( engine_gpgsm_t gpgsm , fd_type_t fd_type , const char * opt ) {
 gpg_error_t err = 0 ;
 char line [ COMMANDLINELEN ] ;
 char * which ;
 iocb_data_t * iocb_data ;


 case INPUT_FD : which = "INPUT" ;
 iocb_data = & gpgsm -> input_cb ;
 break ;
 case OUTPUT_FD : which = "OUTPUT" ;
 iocb_data = & gpgsm -> output_cb ;
 break ;
 case MESSAGE_FD : which = "MESSAGE" ;
 iocb_data = & gpgsm -> message_cb ;
 break ;
 default : return gpg_error ( GPG_ERR_INV_VALUE ) ;
 }

 iocb_data -> server_fd = _gpgme_data_get_fd ( iocb_data -> data ) ;
 if ( iocb_data -> server_fd < 0 ) {
 int fds [ 2 ] ;
 if ( _gpgme_io_pipe ( fds , dir ) < 0 ) return gpg_error_from_syserror ( ) ;
 iocb_data -> fd = dir ? fds [ 0 ] : fds [ 1 ] ;
 iocb_data -> server_fd = dir ? fds [ 1 ] : fds [ 0 ] ;
 if ( _gpgme_io_set_close_notify ( iocb_data -> fd , close_notify_handler , gpgsm ) ) {
 err = gpg_error ( GPG_ERR_GENERAL ) ;
 goto leave_set_fd ;
 }
 }
 err = assuan_sendfd ( gpgsm -> assuan_ctx , iocb_data -> server_fd ) ;
 if ( err ) goto leave_set_fd ;
 _gpgme_io_close ( iocb_data -> server_fd ) ;
 iocb_data -> server_fd = - 1 ;
 if ( opt ) snprintf ( line , COMMANDLINELEN , "%s FD %s" , which , opt ) ;
 else snprintf ( line , COMMANDLINELEN , "%s FD" , which ) ;

 else snprintf ( line , COMMANDLINELEN , "%s FD=%s" , which , iocb_data -> server_fd_str ) ;


 _gpgme_io_close ( iocb_data -> fd ) ;
 iocb_data -> fd = - 1 ;
 if ( iocb_data -> server_fd != - 1 ) {
 _gpgme_io_close ( iocb_data -> server_fd ) ;
 iocb_data -> server_fd = - 1 ;
 }
 }

 }