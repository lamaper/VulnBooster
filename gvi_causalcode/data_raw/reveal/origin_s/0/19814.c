void mgs_hook_child_init ( apr_pool_t * p , server_rec * s ) {
 apr_status_t rv = APR_SUCCESS ;
 mgs_srvconf_rec * sc = ap_get_module_config ( s -> module_config , & gnutls_module ) ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 if ( sc -> cache_type != mgs_cache_none ) {
 rv = mgs_cache_child_init ( p , s , sc ) ;
 if ( rv != APR_SUCCESS ) {
 ap_log_error ( APLOG_MARK , APLOG_EMERG , rv , s , "[GnuTLS] - Failed to run Cache Init" ) ;
 }
 }
 rv = apr_signal_block ( SIGPIPE ) ;
 if ( rv != APR_SUCCESS ) {
 ap_log_error ( APLOG_MARK , APLOG_EMERG , rv , s , "GnuTLS: Error Blocking SIGPIPE Signal!" ) ;
 }
 }