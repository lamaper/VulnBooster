int mgs_hook_post_config ( apr_pool_t * p , apr_pool_t * plog __attribute__ ( ( unused ) ) , apr_pool_t * ptemp __attribute__ ( ( unused ) ) , server_rec * base_server ) {
 int rv ;
 server_rec * s ;
 gnutls_dh_params_t dh_params = NULL ;
 mgs_srvconf_rec * sc ;
 mgs_srvconf_rec * sc_base ;
 void * data = NULL ;
 const char * userdata_key = "mgs_init" ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 apr_pool_userdata_get ( & data , userdata_key , base_server -> process -> pool ) ;
 if ( data == NULL ) {
 apr_pool_userdata_set ( ( const void * ) 1 , userdata_key , apr_pool_cleanup_null , base_server -> process -> pool ) ;
 }
 s = base_server ;
 sc_base = ( mgs_srvconf_rec * ) ap_get_module_config ( s -> module_config , & gnutls_module ) ;
 gnutls_dh_params_init ( & dh_params ) ;
 if ( sc_base -> dh_params == NULL ) {
 gnutls_datum_t pdata = {
 ( void * ) static_dh_params , sizeof ( static_dh_params ) }
 ;
 rv = gnutls_dh_params_import_pkcs3 ( dh_params , & pdata , GNUTLS_X509_FMT_PEM ) ;
 if ( rv < 0 ) {
 ap_log_error ( APLOG_MARK , APLOG_STARTUP , 0 , s , "GnuTLS: Unable to generate or load DH Params: (%d) %s" , rv , gnutls_strerror ( rv ) ) ;
 exit ( rv ) ;
 }
 }
 else {
 dh_params = sc_base -> dh_params ;
 }
 rv = mgs_cache_post_config ( p , s , sc_base ) ;
 if ( rv != 0 ) {
 ap_log_error ( APLOG_MARK , APLOG_STARTUP , rv , s , "GnuTLS: Post Config for GnuTLSCache Failed." " Shutting Down." ) ;
 exit ( - 1 ) ;
 }
 for ( s = base_server ;
 s ;
 s = s -> next ) {
 sc = ( mgs_srvconf_rec * ) ap_get_module_config ( s -> module_config , & gnutls_module ) ;
 sc -> cache_type = sc_base -> cache_type ;
 sc -> cache_config = sc_base -> cache_config ;
 sc -> cache_timeout = sc_base -> cache_timeout ;
 if ( sc -> enabled == GNUTLS_ENABLED_UNSET ) sc -> enabled = GNUTLS_ENABLED_FALSE ;
 if ( sc -> tickets == GNUTLS_ENABLED_UNSET ) sc -> tickets = GNUTLS_ENABLED_TRUE ;
 if ( sc -> export_certificates_size < 0 ) sc -> export_certificates_size = 0 ;
 if ( sc -> client_verify_mode == - 1 ) sc -> client_verify_mode = GNUTLS_CERT_IGNORE ;
 if ( sc -> client_verify_method == mgs_cvm_unset ) sc -> client_verify_method = mgs_cvm_cartel ;
 if ( sc -> priorities == NULL && sc -> enabled == GNUTLS_ENABLED_TRUE ) {
 ap_log_error ( APLOG_MARK , APLOG_STARTUP , 0 , s , "GnuTLS: Host '%s:%d' is missing the GnuTLSPriorities directive!" , s -> server_hostname , s -> port ) ;
 exit ( - 1 ) ;
 }
 if ( sc -> dh_params != NULL ) {
 gnutls_certificate_set_dh_params ( sc -> certs , sc -> dh_params ) ;
 gnutls_anon_set_server_dh_params ( sc -> anon_creds , sc -> dh_params ) ;
 }
 else if ( dh_params ) {
 gnutls_certificate_set_dh_params ( sc -> certs , dh_params ) ;
 gnutls_anon_set_server_dh_params ( sc -> anon_creds , dh_params ) ;
 }
 gnutls_certificate_set_retrieve_function ( sc -> certs , cert_retrieve_fn ) ;

 rv = gnutls_srp_set_server_credentials_file ( sc -> srp_creds , sc -> srp_tpasswd_file , sc -> srp_tpasswd_conf_file ) ;
 if ( rv < 0 && sc -> enabled == GNUTLS_ENABLED_TRUE ) {
 ap_log_error ( APLOG_MARK , APLOG_STARTUP , 0 , s , "[GnuTLS] - Host '%s:%d' is missing a " "SRP password or conf File!" , s -> server_hostname , s -> port ) ;
 exit ( - 1 ) ;
 }
 }

 ap_log_error ( APLOG_MARK , APLOG_STARTUP , 0 , s , "[GnuTLS] - Host '%s:%d' is missing a Certificate File!" , s -> server_hostname , s -> port ) ;
 exit ( - 1 ) ;
 }
 if ( sc -> enabled == GNUTLS_ENABLED_TRUE && ( ( sc -> certs_x509_chain != NULL && sc -> certs_x509_chain_num > 0 && sc -> privkey_x509 == NULL ) || ( sc -> cert_pgp != NULL && sc -> privkey_pgp == NULL ) ) ) {
 ap_log_error ( APLOG_MARK , APLOG_STARTUP , 0 , s , "[GnuTLS] - Host '%s:%d' is missing a Private Key File!" , s -> server_hostname , s -> port ) ;
 exit ( - 1 ) ;
 }
 if ( sc -> enabled == GNUTLS_ENABLED_TRUE ) {
 rv = - 1 ;
 if ( sc -> certs_x509_chain_num > 0 ) {
 rv = read_crt_cn ( s , p , sc -> certs_x509_chain [ 0 ] , & sc -> cert_cn ) ;
 }
 if ( rv < 0 && sc -> cert_pgp != NULL ) {
 rv = read_pgpcrt_cn ( s , p , sc -> cert_pgp , & sc -> cert_cn ) ;
 }
 if ( rv < 0 ) {
 ap_log_error ( APLOG_MARK , APLOG_STARTUP , 0 , s , "[GnuTLS] - Cannot find a certificate for host '%s:%d'!" , s -> server_hostname , s -> port ) ;
 sc -> cert_cn = NULL ;
 continue ;
 }
 }
 }
 ap_add_version_component ( p , "mod_gnutls/" MOD_GNUTLS_VERSION ) ;
 {
 const char * libvers = gnutls_check_version ( NULL ) ;
 char * gnutls_version = NULL ;
 if ( libvers && ( gnutls_version = apr_psprintf ( p , "GnuTLS/%s" , libvers ) ) ) {
 ap_add_version_component ( p , gnutls_version ) ;
 }
 else {
 ap_add_version_component ( p , "GnuTLS/" GNUTLS_VERSION "-static" ) ;
 }
 }
 return OK ;
 }