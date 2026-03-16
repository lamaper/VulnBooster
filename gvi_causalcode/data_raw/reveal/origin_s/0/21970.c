err_status_t srtp_install_event_handler ( srtp_event_handler_func_t func ) {
 srtp_event_handler = func ;
 return err_status_ok ;
 }