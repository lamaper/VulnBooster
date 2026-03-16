static int mgs_select_virtual_server_cb ( gnutls_session_t session ) {
 mgs_handle_t * ctxt = NULL ;
 mgs_srvconf_rec * tsc = NULL ;
 int ret = 0 ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 ctxt = gnutls_transport_get_ptr ( session ) ;
 tsc = mgs_find_sni_server ( session ) ;
 if ( tsc != NULL ) {
 ctxt -> sc = tsc ;
 }
 gnutls_certificate_server_set_request ( session , ctxt -> sc -> client_verify_mode ) ;
 gnutls_credentials_set ( session , GNUTLS_CRD_CERTIFICATE , ctxt -> sc -> certs ) ;
 gnutls_credentials_set ( session , GNUTLS_CRD_ANON , ctxt -> sc -> anon_creds ) ;

 gnutls_credentials_set ( session , GNUTLS_CRD_SRP , ctxt -> sc -> srp_creds ) ;
 }

 return ret ;
 }