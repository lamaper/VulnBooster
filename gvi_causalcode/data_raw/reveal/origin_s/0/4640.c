apr_status_t mgs_cleanup_pre_config ( void * data __attribute__ ( ( unused ) ) ) {
 gnutls_free ( session_ticket_key . data ) ;
 session_ticket_key . data = NULL ;
 session_ticket_key . size = 0 ;
 gnutls_global_deinit ( ) ;
 return APR_SUCCESS ;
 }