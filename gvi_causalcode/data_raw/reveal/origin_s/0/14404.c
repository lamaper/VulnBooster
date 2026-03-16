mgs_srvconf_rec * mgs_find_sni_server ( gnutls_session_t session ) {
 int rv ;
 unsigned int sni_type ;
 size_t data_len = MAX_HOST_LEN ;
 char sni_name [ MAX_HOST_LEN ] ;
 mgs_handle_t * ctxt ;


 mgs_srvconf_rec * tsc ;

 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 ctxt = gnutls_transport_get_ptr ( session ) ;
 rv = gnutls_server_name_get ( ctxt -> session , sni_name , & data_len , & sni_type , 0 ) ;
 if ( rv != 0 ) {
 return NULL ;
 }
 if ( sni_type != GNUTLS_NAME_DNS ) {
 ap_log_error ( APLOG_MARK , APLOG_CRIT , 0 , ctxt -> c -> base_server , "GnuTLS: Unknown type '%d' for SNI: " "'%s'" , sni_type , sni_name ) ;
 return NULL ;
 }

 cbx . sc = NULL ;
 cbx . sni_name = sni_name ;
 rv = ap_vhost_iterate_given_conn ( ctxt -> c , vhost_cb , & cbx ) ;
 if ( rv == 1 ) {
 return cbx . sc ;
 }

 s ;
 s = s -> next ) {
 tsc = ( mgs_srvconf_rec * ) ap_get_module_config ( s -> module_config , & gnutls_module ) ;
 if ( tsc -> enabled != GNUTLS_ENABLED_TRUE ) {
 continue ;
 }
 if ( check_server_aliases ( x , s , tsc ) ) {
 return tsc ;
 }

 }
 static void create_gnutls_handle ( conn_rec * c ) {
 mgs_srvconf_rec * sc = ( mgs_srvconf_rec * ) ap_get_module_config ( c -> base_server -> module_config , & gnutls_module ) ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 mgs_handle_t * ctxt = ( mgs_handle_t * ) ap_get_module_config ( c -> conn_config , & gnutls_module ) ;
 if ( ctxt == NULL ) {
 ap_log_cerror ( APLOG_MARK , APLOG_DEBUG , 0 , c , "%s: allocating connection memory" , __func__ ) ;
 ctxt = apr_pcalloc ( c -> pool , sizeof ( * ctxt ) ) ;
 ap_set_module_config ( c -> conn_config , & gnutls_module , ctxt ) ;
 }
 ctxt -> enabled = GNUTLS_ENABLED_TRUE ;
 ctxt -> c = c ;
 ctxt -> sc = sc ;
 ctxt -> status = 0 ;
 ctxt -> input_rc = APR_SUCCESS ;
 ctxt -> input_bb = apr_brigade_create ( c -> pool , c -> bucket_alloc ) ;
 ctxt -> input_cbuf . length = 0 ;
 ctxt -> output_rc = APR_SUCCESS ;
 ctxt -> output_bb = apr_brigade_create ( c -> pool , c -> bucket_alloc ) ;
 ctxt -> output_blen = 0 ;
 ctxt -> output_length = 0 ;
 int err = gnutls_init ( & ctxt -> session , GNUTLS_SERVER ) ;
 if ( err != GNUTLS_E_SUCCESS ) ap_log_cerror ( APLOG_MARK , APLOG_ERR , err , c , "gnutls_init failed!" ) ;
 if ( session_ticket_key . data != NULL && ctxt -> sc -> tickets != 0 ) {
 err = gnutls_session_ticket_enable_server ( ctxt -> session , & session_ticket_key ) ;
 if ( err != GNUTLS_E_SUCCESS ) ap_log_cerror ( APLOG_MARK , APLOG_ERR , err , c , "gnutls_session_ticket_enable_server failed!" ) ;
 }
 err = gnutls_priority_set_direct ( ctxt -> session , "NORMAL" , NULL ) ;
 if ( err != GNUTLS_E_SUCCESS ) ap_log_cerror ( APLOG_MARK , APLOG_ERR , err , c , "gnutls_priority_set_direct failed!" ) ;
 gnutls_handshake_set_post_client_hello_function ( ctxt -> session , mgs_select_virtual_server_cb ) ;
 mgs_cache_session_init ( ctxt ) ;
 gnutls_transport_set_pull_function ( ctxt -> session , mgs_transport_read ) ;
 gnutls_transport_set_push_function ( ctxt -> session , mgs_transport_write ) ;
 gnutls_transport_set_ptr ( ctxt -> session , ctxt ) ;
 ctxt -> input_filter = ap_add_input_filter ( GNUTLS_INPUT_FILTER_NAME , ctxt , NULL , c ) ;
 ctxt -> output_filter = ap_add_output_filter ( GNUTLS_OUTPUT_FILTER_NAME , ctxt , NULL , c ) ;
 }
 int mgs_hook_pre_connection ( conn_rec * c , void * csd __attribute__ ( ( unused ) ) ) {
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 mgs_srvconf_rec * sc = ( mgs_srvconf_rec * ) ap_get_module_config ( c -> base_server -> module_config , & gnutls_module ) ;
 mgs_handle_t * ctxt = ( mgs_handle_t * ) ap_get_module_config ( c -> conn_config , & gnutls_module ) ;
 if ( ( sc && ( ! sc -> enabled || sc -> proxy_enabled == GNUTLS_ENABLED_TRUE ) ) || ( ctxt && ctxt -> enabled == GNUTLS_ENABLED_FALSE ) ) {
 ap_log_cerror ( APLOG_MARK , APLOG_DEBUG , 0 , c , "%s declined connection" , __func__ ) ;
 return DECLINED ;
 }
 create_gnutls_handle ( c ) ;
 return OK ;
 }
 int mgs_hook_fixups ( request_rec * r ) {
 unsigned char sbuf [ GNUTLS_MAX_SESSION_ID ] ;
 char buf [ AP_IOBUFSIZE ] ;
 const char * tmp ;
 size_t len ;
 mgs_handle_t * ctxt ;
 int rv = OK ;
 if ( r == NULL ) return DECLINED ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 apr_table_t * env = r -> subprocess_env ;
 ctxt = ap_get_module_config ( r -> connection -> conn_config , & gnutls_module ) ;
 if ( ! ctxt || ctxt -> enabled != GNUTLS_ENABLED_TRUE || ctxt -> session == NULL ) {
 ap_log_rerror ( APLOG_MARK , APLOG_DEBUG , 0 , r , "request declined in %s" , __func__ ) ;
 return DECLINED ;
 }
 apr_table_setn ( env , "HTTPS" , "on" ) ;
 apr_table_setn ( env , "SSL_VERSION_LIBRARY" , "GnuTLS/" LIBGNUTLS_VERSION ) ;
 apr_table_setn ( env , "SSL_VERSION_INTERFACE" , "mod_gnutls/" MOD_GNUTLS_VERSION ) ;
 apr_table_setn ( env , "SSL_PROTOCOL" , gnutls_protocol_get_name ( gnutls_protocol_get_version ( ctxt -> session ) ) ) ;
 apr_table_setn ( env , "SSL_CIPHER" , gnutls_cipher_suite_get_name ( gnutls_kx_get ( ctxt -> session ) , gnutls_cipher_get ( ctxt -> session ) , gnutls_mac_get ( ctxt -> session ) ) ) ;
 apr_table_setn ( env , "SSL_COMPRESS_METHOD" , gnutls_compression_get_name ( gnutls_compression_get ( ctxt -> session ) ) ) ;

 tmp = gnutls_srp_server_get_username ( ctxt -> session ) ;
 apr_table_setn ( env , "SSL_SRP_USER" , ( tmp != NULL ) ? tmp : "" ) ;
 }
 else {
 apr_table_unset ( env , "SSL_SRP_USER" ) ;
 }

 unsigned int key_size = 8 * gnutls_cipher_get_key_size ( gnutls_cipher_get ( ctxt -> session ) ) ;
 tmp = apr_psprintf ( r -> pool , "%u" , key_size ) ;
 apr_table_setn ( env , "SSL_CIPHER_USEKEYSIZE" , tmp ) ;
 apr_table_setn ( env , "SSL_CIPHER_ALGKEYSIZE" , tmp ) ;
 apr_table_setn ( env , "SSL_CIPHER_EXPORT" , ( key_size <= 40 ) ? "true" : "false" ) ;
 int dhsize = gnutls_dh_get_prime_bits ( ctxt -> session ) ;
 if ( dhsize > 0 ) {
 tmp = apr_psprintf ( r -> pool , "%d" , dhsize ) ;
 apr_table_setn ( env , "SSL_DH_PRIME_BITS" , tmp ) ;
 }
 len = sizeof ( sbuf ) ;
 gnutls_session_get_id ( ctxt -> session , sbuf , & len ) ;
 tmp = mgs_session_id2sz ( sbuf , len , buf , sizeof ( buf ) ) ;
 apr_table_setn ( env , "SSL_SESSION_ID" , apr_pstrdup ( r -> pool , tmp ) ) ;
 if ( gnutls_certificate_type_get ( ctxt -> session ) == GNUTLS_CRT_X509 ) {
 mgs_add_common_cert_vars ( r , ctxt -> sc -> certs_x509_chain [ 0 ] , 0 , ctxt -> sc -> export_certificates_size ) ;
 }
 else if ( gnutls_certificate_type_get ( ctxt -> session ) == GNUTLS_CRT_OPENPGP ) {
 mgs_add_common_pgpcert_vars ( r , ctxt -> sc -> cert_pgp , 0 , ctxt -> sc -> export_certificates_size ) ;
 }
 return rv ;
 }
 int mgs_hook_authz ( request_rec * r ) {
 int rv ;
 mgs_handle_t * ctxt ;
 mgs_dirconf_rec * dc ;
 if ( r == NULL ) return DECLINED ;
 dc = ap_get_module_config ( r -> per_dir_config , & gnutls_module ) ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 ctxt = ap_get_module_config ( r -> connection -> conn_config , & gnutls_module ) ;
 if ( ! ctxt || ctxt -> session == NULL ) {
 return DECLINED ;
 }
 if ( dc -> client_verify_mode == GNUTLS_CERT_IGNORE ) {
 ap_log_rerror ( APLOG_MARK , APLOG_DEBUG , 0 , r , "GnuTLS: Directory set to Ignore Client Certificate!" ) ;
 }
 else {
 if ( ctxt -> sc -> client_verify_mode < dc -> client_verify_mode ) {
 ap_log_rerror ( APLOG_MARK , APLOG_DEBUG , 0 , r , "GnuTLS: Attempting to rehandshake with peer. %d %d" , ctxt -> sc -> client_verify_mode , dc -> client_verify_mode ) ;
 rv = mgs_cert_verify ( r , ctxt ) ;
 if ( rv != DECLINED && rv != HTTP_FORBIDDEN ) return rv ;
 gnutls_certificate_server_set_request ( ctxt -> session , dc -> client_verify_mode ) ;
 if ( mgs_rehandshake ( ctxt ) != 0 ) {
 return HTTP_FORBIDDEN ;
 }
 }
 else if ( ctxt -> sc -> client_verify_mode == GNUTLS_CERT_IGNORE ) {


 }
 rv = mgs_cert_verify ( r , ctxt ) ;
 if ( rv != DECLINED && ( rv != HTTP_FORBIDDEN || dc -> client_verify_mode == GNUTLS_CERT_REQUIRE || ( dc -> client_verify_mode == - 1 && ctxt -> sc -> client_verify_mode == GNUTLS_CERT_REQUIRE ) ) ) {
 return rv ;
 }
 }
 return DECLINED ;
 }

 unsigned char sbuf [ 64 ] ;
 char buf [ AP_IOBUFSIZE ] ;
 const char * tmp ;
 char * tmp2 ;
 size_t len ;
 int ret , i ;
 if ( r == NULL ) return ;
 apr_table_t * env = r -> subprocess_env ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 if ( export_cert_size > 0 ) {
 len = 0 ;
 ret = gnutls_x509_crt_export ( cert , GNUTLS_X509_FMT_PEM , NULL , & len ) ;
 if ( ret == GNUTLS_E_SHORT_MEMORY_BUFFER ) {
 if ( len >= export_cert_size ) {
 apr_table_setn ( env , MGS_SIDE ( "_CERT" ) , "GNUTLS_CERTIFICATE_SIZE_LIMIT_EXCEEDED" ) ;
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Failed to export too-large X.509 certificate to environment" ) ;
 }
 else {
 char * cert_buf = apr_palloc ( r -> pool , len + 1 ) ;
 if ( cert_buf != NULL && gnutls_x509_crt_export ( cert , GNUTLS_X509_FMT_PEM , cert_buf , & len ) >= 0 ) {
 cert_buf [ len ] = 0 ;
 apr_table_setn ( env , MGS_SIDE ( "_CERT" ) , cert_buf ) ;
 }
 else {
 ap_log_rerror ( APLOG_MARK , APLOG_WARNING , 0 , r , "GnuTLS: failed to export X.509 certificate" ) ;
 }
 }
 }
 else {
 ap_log_rerror ( APLOG_MARK , APLOG_WARNING , 0 , r , "GnuTLS: dazed and confused about X.509 certificate size" ) ;
 }
 }
 len = sizeof ( buf ) ;
 gnutls_x509_crt_get_dn ( cert , buf , & len ) ;
 apr_table_setn ( env , MGS_SIDE ( "_S_DN" ) , apr_pstrmemdup ( r -> pool , buf , len ) ) ;
 len = sizeof ( buf ) ;
 gnutls_x509_crt_get_issuer_dn ( cert , buf , & len ) ;
 apr_table_setn ( env , MGS_SIDE ( "_I_DN" ) , apr_pstrmemdup ( r -> pool , buf , len ) ) ;
 len = sizeof ( sbuf ) ;
 gnutls_x509_crt_get_serial ( cert , sbuf , & len ) ;
 tmp = mgs_session_id2sz ( sbuf , len , buf , sizeof ( buf ) ) ;
 apr_table_setn ( env , MGS_SIDE ( "_M_SERIAL" ) , apr_pstrdup ( r -> pool , tmp ) ) ;
 ret = gnutls_x509_crt_get_version ( cert ) ;
 if ( ret > 0 ) apr_table_setn ( env , MGS_SIDE ( "_M_VERSION" ) , apr_psprintf ( r -> pool , "%u" , ret ) ) ;
 apr_table_setn ( env , MGS_SIDE ( "_CERT_TYPE" ) , "X.509" ) ;
 tmp = mgs_time2sz ( gnutls_x509_crt_get_expiration_time ( cert ) , buf , sizeof ( buf ) ) ;
 apr_table_setn ( env , MGS_SIDE ( "_V_END" ) , apr_pstrdup ( r -> pool , tmp ) ) ;
 tmp = mgs_time2sz ( gnutls_x509_crt_get_activation_time ( cert ) , buf , sizeof ( buf ) ) ;
 apr_table_setn ( env , MGS_SIDE ( "_V_START" ) , apr_pstrdup ( r -> pool , tmp ) ) ;
 ret = gnutls_x509_crt_get_signature_algorithm ( cert ) ;
 if ( ret >= 0 ) {
 apr_table_setn ( env , MGS_SIDE ( "_A_SIG" ) , gnutls_sign_algorithm_get_name ( ret ) ) ;
 }
 ret = gnutls_x509_crt_get_pk_algorithm ( cert , NULL ) ;
 if ( ret >= 0 ) {
 apr_table_setn ( env , MGS_SIDE ( "_A_KEY" ) , gnutls_pk_algorithm_get_name ( ret ) ) ;
 }
 for ( i = 0 ;
 ! ( ret < 0 ) ;
 i ++ ) {
 const char * san , * sanlabel ;
 len = 0 ;
 ret = gnutls_x509_crt_get_subject_alt_name ( cert , i , NULL , & len , NULL ) ;
 if ( ret == GNUTLS_E_SHORT_MEMORY_BUFFER && len > 1 ) {
 tmp2 = apr_palloc ( r -> pool , len + 1 ) ;
 ret = gnutls_x509_crt_get_subject_alt_name ( cert , i , tmp2 , & len , NULL ) ;
 tmp2 [ len ] = 0 ;
 sanlabel = apr_psprintf ( r -> pool , "%s%u" , MGS_SIDE ( "_S_AN" ) , i ) ;
 if ( ret == GNUTLS_SAN_DNSNAME ) {
 san = apr_psprintf ( r -> pool , "DNSNAME:%s" , tmp2 ) ;
 }
 else if ( ret == GNUTLS_SAN_RFC822NAME ) {
 san = apr_psprintf ( r -> pool , "RFC822NAME:%s" , tmp2 ) ;
 }
 else if ( ret == GNUTLS_SAN_URI ) {
 san = apr_psprintf ( r -> pool , "URI:%s" , tmp2 ) ;
 }
 else {
 san = "UNSUPPORTED" ;
 }
 apr_table_setn ( env , sanlabel , san ) ;
 }
 }
 }
 static void mgs_add_common_pgpcert_vars ( request_rec * r , gnutls_openpgp_crt_t cert , int side , size_t export_cert_size ) {
 unsigned char sbuf [ 64 ] ;
 char buf [ AP_IOBUFSIZE ] ;
 const char * tmp ;
 size_t len ;
 int ret ;
 if ( r == NULL ) return ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 apr_table_t * env = r -> subprocess_env ;
 if ( export_cert_size > 0 ) {
 len = 0 ;
 ret = gnutls_openpgp_crt_export ( cert , GNUTLS_OPENPGP_FMT_BASE64 , NULL , & len ) ;
 if ( ret == GNUTLS_E_SHORT_MEMORY_BUFFER ) {
 if ( len >= export_cert_size ) {
 apr_table_setn ( env , MGS_SIDE ( "_CERT" ) , "GNUTLS_CERTIFICATE_SIZE_LIMIT_EXCEEDED" ) ;
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Failed to export too-large OpenPGP certificate to environment" ) ;
 }
 else {
 char * cert_buf = apr_palloc ( r -> pool , len + 1 ) ;
 if ( cert_buf != NULL && gnutls_openpgp_crt_export ( cert , GNUTLS_OPENPGP_FMT_BASE64 , cert_buf , & len ) >= 0 ) {
 cert_buf [ len ] = 0 ;
 apr_table_setn ( env , MGS_SIDE ( "_CERT" ) , cert_buf ) ;
 }
 else {
 ap_log_rerror ( APLOG_MARK , APLOG_WARNING , 0 , r , "GnuTLS: failed to export OpenPGP certificate" ) ;
 }
 }
 }
 else {
 ap_log_rerror ( APLOG_MARK , APLOG_WARNING , 0 , r , "GnuTLS: dazed and confused about OpenPGP certificate size" ) ;
 }
 }
 len = sizeof ( buf ) ;
 gnutls_openpgp_crt_get_name ( cert , 0 , buf , & len ) ;
 apr_table_setn ( env , MGS_SIDE ( "_NAME" ) , apr_pstrmemdup ( r -> pool , buf , len ) ) ;
 len = sizeof ( sbuf ) ;
 gnutls_openpgp_crt_get_fingerprint ( cert , sbuf , & len ) ;
 tmp = mgs_session_id2sz ( sbuf , len , buf , sizeof ( buf ) ) ;
 apr_table_setn ( env , MGS_SIDE ( "_FINGERPRINT" ) , apr_pstrdup ( r -> pool , tmp ) ) ;
 ret = gnutls_openpgp_crt_get_version ( cert ) ;
 if ( ret > 0 ) apr_table_setn ( env , MGS_SIDE ( "_M_VERSION" ) , apr_psprintf ( r -> pool , "%u" , ret ) ) ;
 apr_table_setn ( env , MGS_SIDE ( "_CERT_TYPE" ) , "OPENPGP" ) ;
 tmp = mgs_time2sz ( gnutls_openpgp_crt_get_expiration_time ( cert ) , buf , sizeof ( buf ) ) ;
 apr_table_setn ( env , MGS_SIDE ( "_V_END" ) , apr_pstrdup ( r -> pool , tmp ) ) ;
 tmp = mgs_time2sz ( gnutls_openpgp_crt_get_creation_time ( cert ) , buf , sizeof ( buf ) ) ;
 apr_table_setn ( env , MGS_SIDE ( "_V_START" ) , apr_pstrdup ( r -> pool , tmp ) ) ;
 ret = gnutls_openpgp_crt_get_pk_algorithm ( cert , NULL ) ;
 if ( ret >= 0 ) {
 apr_table_setn ( env , MGS_SIDE ( "_A_KEY" ) , gnutls_pk_algorithm_get_name ( ret ) ) ;
 }
 }
 static int mgs_cert_verify ( request_rec * r , mgs_handle_t * ctxt ) {
 const gnutls_datum_t * cert_list ;
 unsigned int cert_list_size , status ;
 int rv = GNUTLS_E_NO_CERTIFICATE_FOUND , ret ;
 unsigned int ch_size = 0 ;
 union {
 gnutls_x509_crt_t x509 [ MAX_CHAIN_SIZE ] ;
 gnutls_openpgp_crt_t pgp ;
 }
 cert ;
 apr_time_t expiration_time , cur_time ;
 if ( r == NULL || ctxt == NULL || ctxt -> session == NULL ) return HTTP_FORBIDDEN ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 cert_list = gnutls_certificate_get_peers ( ctxt -> session , & cert_list_size ) ;
 if ( cert_list == NULL || cert_list_size == 0 ) {
 if ( ctxt -> sc -> client_verify_mode == GNUTLS_CERT_REQUEST ) return OK ;
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Failed to Verify Peer: " "Client did not submit a certificate" ) ;
 return HTTP_FORBIDDEN ;
 }
 if ( gnutls_certificate_type_get ( ctxt -> session ) == GNUTLS_CRT_X509 ) {
 ap_log_rerror ( APLOG_MARK , APLOG_DEBUG , 0 , r , "GnuTLS: A Chain of %d certificate(s) was provided for validation" , cert_list_size ) ;
 for ( ch_size = 0 ;
 ch_size < cert_list_size ;
 ch_size ++ ) {
 gnutls_x509_crt_init ( & cert . x509 [ ch_size ] ) ;
 rv = gnutls_x509_crt_import ( cert . x509 [ ch_size ] , & cert_list [ ch_size ] , GNUTLS_X509_FMT_DER ) ;
 if ( rv != GNUTLS_E_SUCCESS ) {
 if ( ch_size < 1 ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Failed to Verify Peer: " "Failed to import peer certificates." ) ;
 ret = HTTP_FORBIDDEN ;
 goto exit ;
 }
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Failed to import some peer certificates. Using %d certificates" , ch_size ) ;
 rv = GNUTLS_E_SUCCESS ;
 break ;
 }
 }
 }
 else if ( gnutls_certificate_type_get ( ctxt -> session ) == GNUTLS_CRT_OPENPGP ) {
 if ( cert_list_size > 1 ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Failed to Verify Peer: " "Chained Client Certificates are not supported." ) ;
 return HTTP_FORBIDDEN ;
 }
 gnutls_openpgp_crt_init ( & cert . pgp ) ;
 rv = gnutls_openpgp_crt_import ( cert . pgp , & cert_list [ 0 ] , GNUTLS_OPENPGP_FMT_RAW ) ;
 }
 else return HTTP_FORBIDDEN ;
 if ( rv < 0 ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Failed to Verify Peer: " "Failed to import peer certificates." ) ;
 ret = HTTP_FORBIDDEN ;
 goto exit ;
 }
 if ( gnutls_certificate_type_get ( ctxt -> session ) == GNUTLS_CRT_X509 ) {
 apr_time_ansi_put ( & expiration_time , gnutls_x509_crt_get_expiration_time ( cert . x509 [ 0 ] ) ) ;
 ap_log_rerror ( APLOG_MARK , APLOG_DEBUG , 0 , r , "GnuTLS: Verifying list of %d certificate(s) via method '%s'" , ch_size , mgs_readable_cvm ( ctxt -> sc -> client_verify_method ) ) ;
 switch ( ctxt -> sc -> client_verify_method ) {
 case mgs_cvm_cartel : rv = gnutls_x509_crt_list_verify ( cert . x509 , ch_size , ctxt -> sc -> ca_list , ctxt -> sc -> ca_list_size , NULL , 0 , 0 , & status ) ;
 break ;

 struct msv_response * resp = NULL ;
 struct msv_query q = {
 . context = "https" , . peertype = "client" , . pkctype = "x509pem" }
 ;
 msv_ctxt_t ctx = msv_ctxt_init ( NULL ) ;
 char cert_pem_buf [ 10 * 1024 ] ;
 size_t len = sizeof ( cert_pem_buf ) ;
 rv = 0 ;
 if ( gnutls_x509_crt_export ( cert . x509 [ 0 ] , GNUTLS_X509_FMT_PEM , cert_pem_buf , & len ) >= 0 ) {
 q . peername = mgs_x509_construct_uid ( r , cert . x509 [ 0 ] ) ;
 q . pkcdata = cert_pem_buf ;
 rv = msv_query_agent ( ctx , q , & resp ) ;
 if ( rv == LIBMSV_ERROR_SUCCESS ) {
 status = 0 ;
 }
 else if ( rv == LIBMSV_ERROR_INVALID ) {
 ap_log_rerror ( APLOG_MARK , APLOG_DEBUG , 0 , r , "GnuTLS: Monkeysphere validation failed: (message: %s)" , resp -> message ) ;
 status = GNUTLS_CERT_INVALID ;
 }
 else {
 ap_log_rerror ( APLOG_MARK , APLOG_DEBUG , 0 , r , "GnuTLS: Error communicating with the Monkeysphere Validation Agent: (%d) %s" , rv , msv_strerror ( ctx , rv ) ) ;
 status = GNUTLS_CERT_INVALID ;
 rv = - 1 ;
 }
 }
 else {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Could not convert the client certificate to PEM format" ) ;
 status = GNUTLS_CERT_INVALID ;
 rv = GNUTLS_E_ASN1_ELEMENT_NOT_FOUND ;
 }
 msv_response_destroy ( resp ) ;
 msv_ctxt_destroy ( ctx ) ;
 }
 break ;

 }
 }
 else {
 apr_time_ansi_put ( & expiration_time , gnutls_openpgp_crt_get_expiration_time ( cert . pgp ) ) ;
 switch ( ctxt -> sc -> client_verify_method ) {
 case mgs_cvm_cartel : rv = gnutls_openpgp_crt_verify_ring ( cert . pgp , ctxt -> sc -> pgp_list , 0 , & status ) ;
 break ;

 rv = GNUTLS_E_UNIMPLEMENTED_FEATURE ;
 break ;

 }
 }
 if ( rv < 0 ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Failed to Verify Peer certificate: (%d) %s" , rv , gnutls_strerror ( rv ) ) ;
 if ( rv == GNUTLS_E_NO_CERTIFICATE_FOUND ) ap_log_rerror ( APLOG_MARK , APLOG_EMERG , 0 , r , "GnuTLS: No certificate was found for verification. Did you set the GnuTLSX509CAFile or GnuTLSPGPKeyringFile directives?" ) ;
 ret = HTTP_FORBIDDEN ;
 goto exit ;
 }
 cur_time = apr_time_now ( ) ;
 if ( status & GNUTLS_CERT_SIGNER_NOT_FOUND ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Could not find Signer for Peer Certificate" ) ;
 }
 if ( status & GNUTLS_CERT_SIGNER_NOT_CA ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Peer's Certificate signer is not a CA" ) ;
 }
 if ( status & GNUTLS_CERT_INSECURE_ALGORITHM ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Peer's Certificate is using insecure algorithms" ) ;
 }
 if ( status & GNUTLS_CERT_EXPIRED || status & GNUTLS_CERT_NOT_ACTIVATED ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Peer's Certificate signer is expired or not yet activated" ) ;
 }
 if ( status & GNUTLS_CERT_INVALID ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Peer Certificate is invalid." ) ;
 }
 else if ( status & GNUTLS_CERT_REVOKED ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Peer Certificate is revoked." ) ;
 }
 if ( gnutls_certificate_type_get ( ctxt -> session ) == GNUTLS_CRT_X509 ) mgs_add_common_cert_vars ( r , cert . x509 [ 0 ] , 1 , ctxt -> sc -> export_certificates_size ) ;
 else if ( gnutls_certificate_type_get ( ctxt -> session ) == GNUTLS_CRT_OPENPGP ) mgs_add_common_pgpcert_vars ( r , cert . pgp , 1 , ctxt -> sc -> export_certificates_size ) ;
 {
 unsigned long remain = ( apr_time_sec ( expiration_time ) - apr_time_sec ( cur_time ) ) / 86400 ;
 apr_table_setn ( r -> subprocess_env , "SSL_CLIENT_V_REMAIN" , apr_psprintf ( r -> pool , "%lu" , remain ) ) ;
 }
 if ( status == 0 ) {
 apr_table_setn ( r -> subprocess_env , "SSL_CLIENT_VERIFY" , "SUCCESS" ) ;
 ret = OK ;
 }
 else {
 apr_table_setn ( r -> subprocess_env , "SSL_CLIENT_VERIFY" , "FAILED" ) ;
 if ( ctxt -> sc -> client_verify_mode == GNUTLS_CERT_REQUEST ) ret = OK ;
 else ret = HTTP_FORBIDDEN ;
 }
 exit : if ( gnutls_certificate_type_get ( ctxt -> session ) == GNUTLS_CRT_X509 ) {
 unsigned int i ;
 for ( i = 0 ;
 i < ch_size ;
 i ++ ) {
 gnutls_x509_crt_deinit ( cert . x509 [ i ] ) ;
 }
 }
 else if ( gnutls_certificate_type_get ( ctxt -> session ) == GNUTLS_CRT_OPENPGP ) gnutls_openpgp_crt_deinit ( cert . pgp ) ;
 return ret ;
 }

 int rv = GNUTLS_E_SUCCESS , i ;
 size_t sz = 0 , lastsz = 0 ;
 char * data = NULL ;
 i = - 1 ;
 while ( rv != GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE ) {
 i ++ ;
 lastsz = sz ;
 sz = 0 ;
 rv = gnutls_x509_crt_get_dn_by_oid ( cert , oid , i , 0 , NULL , & sz ) ;
 }
 if ( i > 0 ) {
 data = apr_palloc ( pool , lastsz ) ;
 sz = lastsz ;
 rv = gnutls_x509_crt_get_dn_by_oid ( cert , oid , i - 1 , 0 , data , & sz ) ;
 if ( rv == GNUTLS_E_SUCCESS ) return data ;
 }
 return NULL ;
 }
 static const char * mgs_x509_first_type_from_san ( apr_pool_t * pool , gnutls_x509_subject_alt_name_t target , gnutls_x509_crt_t cert ) {
 int rv = GNUTLS_E_SUCCESS ;
 size_t sz ;
 char * data = NULL ;
 unsigned int i ;
 gnutls_x509_subject_alt_name_t thistype ;
 i = 0 ;
 while ( rv != GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE ) {
 sz = 0 ;
 rv = gnutls_x509_crt_get_subject_alt_name2 ( cert , i , NULL , & sz , & thistype , NULL ) ;
 if ( rv == GNUTLS_E_SHORT_MEMORY_BUFFER && thistype == target ) {
 data = apr_palloc ( pool , sz ) ;
 rv = gnutls_x509_crt_get_subject_alt_name2 ( cert , i , data , & sz , & thistype , NULL ) ;
 if ( rv >= 0 && ( thistype == target ) ) return data ;
 }
 i ++ ;
 }
 return NULL ;
 }
 static const char * mgs_x509_construct_uid ( request_rec * r , gnutls_x509_crt_t cert ) {
 apr_pool_t * pool = r -> pool ;
 const char * name = NULL , * comment = NULL , * email = NULL ;
 const char * ret = NULL ;
 apr_pool_t * sp = NULL ;
 if ( APR_SUCCESS != apr_pool_create ( & sp , pool ) ) return NULL ;
 name = mgs_x509_leaf_oid_from_dn ( sp , GNUTLS_OID_X520_COMMON_NAME , cert ) ;
 comment = mgs_x509_leaf_oid_from_dn ( sp , GNUTLS_OID_X520_PSEUDONYM , cert ) ;
 email = mgs_x509_first_type_from_san ( sp , GNUTLS_SAN_RFC822NAME , cert ) ;
 if ( email == NULL ) email = mgs_x509_leaf_oid_from_dn ( sp , GNUTLS_OID_PKCS9_EMAIL , cert ) ;
 if ( name == NULL && email == NULL ) {
 ap_log_rerror ( APLOG_MARK , APLOG_INFO , 0 , r , "GnuTLS: Need either a name or an e-mail address to get a User ID from an X.509 certificate." ) ;
 goto end ;
 }
 if ( name ) {
 if ( comment ) {
 if ( email ) {
 ret = apr_psprintf ( pool , "%s (%s) <%s>" , name , comment , email ) ;
 }
 else {
 ret = apr_psprintf ( pool , "%s (%s)" , name , comment ) ;
 }
 }
 else {
 if ( email ) {
 ret = apr_psprintf ( pool , "%s <%s>" , name , email ) ;
 }
 else {
 ret = apr_pstrdup ( pool , name ) ;
 }
 }
 }
 else {
 if ( comment ) {
 ret = apr_psprintf ( pool , "(%s) <%s>" , comment , email ) ;
 }
 else {
 ret = apr_psprintf ( pool , "<%s>" , email ) ;
 }
 }
 end : apr_pool_destroy ( sp ) ;
 return ret ;
 }

 mgs_srvconf_rec * sc ;
 if ( r == NULL ) return OK ;
 sc = ( mgs_srvconf_rec * ) ap_get_module_config ( r -> server -> module_config , & gnutls_module ) ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 ap_rputs ( "<hr>\n" , r ) ;
 ap_rputs ( "<h2>GnuTLS Information:</h2>\n<dl>\n" , r ) ;
 ap_rprintf ( r , "<dt>GnuTLS version:</dt><dd>%s</dd>\n" , gnutls_check_version ( NULL ) ) ;
 ap_rputs ( "<dt>Built against:</dt><dd>" GNUTLS_VERSION "</dd>\n" , r ) ;
 ap_rprintf ( r , "<dt>using TLS:</dt><dd>%s</dd>\n" , ( sc -> enabled == GNUTLS_ENABLED_FALSE ? "no" : "yes" ) ) ;
 if ( sc -> enabled != GNUTLS_ENABLED_FALSE ) {
 mgs_handle_t * ctxt ;
 ctxt = ap_get_module_config ( r -> connection -> conn_config , & gnutls_module ) ;
 if ( ctxt && ctxt -> session != NULL ) {


 z = gnutls_session_get_desc ( ctxt -> session ) ;
 if ( z ) {
 ap_rprintf ( r , "<dt>This TLS Session:</dt><dd>%s</dd>\n" , z ) ;
 gnutls_free ( z ) ;
 }

 }
 ap_rputs ( "</dl>\n" , r ) ;
 return OK ;
 }