apr_port_t mgs_hook_default_port ( const request_rec * r ) {
 mgs_srvconf_rec * sc ;
 if ( r == NULL ) return 0 ;
 sc = ( mgs_srvconf_rec * ) ap_get_module_config ( r -> server -> module_config , & gnutls_module ) ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 if ( sc -> enabled == GNUTLS_ENABLED_FALSE ) {
 return 0 ;
 }
 return 443 ;
 }