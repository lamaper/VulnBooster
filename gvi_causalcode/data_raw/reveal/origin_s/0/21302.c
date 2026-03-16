int mgs_hook_pre_config ( apr_pool_t * pconf , apr_pool_t * plog , apr_pool_t * ptemp __attribute__ ( ( unused ) ) ) {

 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 gnutls_global_set_log_level ( 9 ) ;
 gnutls_global_set_log_function ( gnutls_debug_log_all ) ;
 _gnutls_log ( debug_log_fp , "gnutls: %s\n" , gnutls_check_version ( NULL ) ) ;

 if ( gnutls_check_version ( LIBGNUTLS_VERSION ) == NULL ) {
 ap_log_perror ( APLOG_MARK , APLOG_EMERG , 0 , plog , "gnutls_check_version() failed. Required: " "gnutls-%s Found: gnutls-%s" , LIBGNUTLS_VERSION , gnutls_check_version ( NULL ) ) ;
 return DONE ;
 }
 ret = gnutls_global_init ( ) ;
 if ( ret < 0 ) {
 ap_log_perror ( APLOG_MARK , APLOG_EMERG , 0 , plog , "gnutls_global_init: %s" , gnutls_strerror ( ret ) ) ;
 return DONE ;
 }
 ret = gnutls_session_ticket_key_generate ( & session_ticket_key ) ;
 if ( ret < 0 ) {
 ap_log_perror ( APLOG_MARK , APLOG_EMERG , 0 , plog , "gnutls_session_ticket_key_generate: %s" , gnutls_strerror ( ret ) ) ;
 return DONE ;
 }
 AP_OPTIONAL_HOOK ( status_hook , mgs_status_hook , NULL , NULL , APR_HOOK_MIDDLE ) ;
 apr_pool_cleanup_register ( pconf , NULL , mgs_cleanup_pre_config , apr_pool_cleanup_null ) ;
 return OK ;
 }