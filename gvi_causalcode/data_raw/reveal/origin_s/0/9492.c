static int cert_status_cb ( SSL * s , void * arg ) {
 tlsextstatusctx * srctx = arg ;
 BIO * err = srctx -> err ;
 char * host , * port , * path ;
 int use_ssl ;
 unsigned char * rspder = NULL ;
 int rspderlen ;
 STACK_OF ( OPENSSL_STRING ) * aia = NULL ;
 X509 * x = NULL ;
 X509_STORE_CTX inctx ;
 X509_OBJECT obj ;
 OCSP_REQUEST * req = NULL ;
 OCSP_RESPONSE * resp = NULL ;
 OCSP_CERTID * id = NULL ;
 STACK_OF ( X509_EXTENSION ) * exts ;
 int ret = SSL_TLSEXT_ERR_NOACK ;
 int i ;

 SSL_get_tlsext_status_ids ( s , & ids ) ;
 BIO_printf ( err , "cert_status: received %d ids\n" , sk_OCSP_RESPID_num ( ids ) ) ;

 x = SSL_get_certificate ( s ) ;
 aia = X509_get1_ocsp ( x ) ;
 if ( aia ) {
 if ( ! OCSP_parse_url ( sk_OPENSSL_STRING_value ( aia , 0 ) , & host , & port , & path , & use_ssl ) ) {
 BIO_puts ( err , "cert_status: can't parse AIA URL\n" ) ;
 goto err ;
 }
 if ( srctx -> verbose ) BIO_printf ( err , "cert_status: AIA URL: %s\n" , sk_OPENSSL_STRING_value ( aia , 0 ) ) ;
 }
 else {
 if ( ! srctx -> host ) {
 BIO_puts ( srctx -> err , "cert_status: no AIA and no default responder URL\n" ) ;
 goto done ;
 }
 host = srctx -> host ;
 path = srctx -> path ;
 port = srctx -> port ;
 use_ssl = srctx -> use_ssl ;
 }
 if ( ! X509_STORE_CTX_init ( & inctx , SSL_CTX_get_cert_store ( SSL_get_SSL_CTX ( s ) ) , NULL , NULL ) ) goto err ;
 if ( X509_STORE_get_by_subject ( & inctx , X509_LU_X509 , X509_get_issuer_name ( x ) , & obj ) <= 0 ) {
 BIO_puts ( err , "cert_status: Can't retrieve issuer certificate.\n" ) ;
 X509_STORE_CTX_cleanup ( & inctx ) ;
 goto done ;
 }
 req = OCSP_REQUEST_new ( ) ;
 if ( ! req ) goto err ;
 id = OCSP_cert_to_id ( NULL , x , obj . data . x509 ) ;
 X509_free ( obj . data . x509 ) ;
 X509_STORE_CTX_cleanup ( & inctx ) ;
 if ( ! id ) goto err ;
 if ( ! OCSP_request_add0_id ( req , id ) ) goto err ;
 id = NULL ;
 SSL_get_tlsext_status_exts ( s , & exts ) ;
 for ( i = 0 ;
 i < sk_X509_EXTENSION_num ( exts ) ;
 i ++ ) {
 X509_EXTENSION * ext = sk_X509_EXTENSION_value ( exts , i ) ;
 if ( ! OCSP_REQUEST_add_ext ( req , ext , - 1 ) ) goto err ;
 }
 resp = process_responder ( err , req , host , path , port , use_ssl , NULL , srctx -> timeout ) ;
 if ( ! resp ) {
 BIO_puts ( err , "cert_status: error querying responder\n" ) ;
 goto done ;
 }
 rspderlen = i2d_OCSP_RESPONSE ( resp , & rspder ) ;
 if ( rspderlen <= 0 ) goto err ;
 SSL_set_tlsext_status_ocsp_resp ( s , rspder , rspderlen ) ;
 if ( srctx -> verbose ) {
 BIO_puts ( err , "cert_status: ocsp response sent:\n" ) ;
 OCSP_RESPONSE_print ( err , resp , 2 ) ;
 }
 ret = SSL_TLSEXT_ERR_OK ;
 done : if ( ret != SSL_TLSEXT_ERR_OK ) ERR_print_errors ( err ) ;
 if ( aia ) {
 OPENSSL_free ( host ) ;
 OPENSSL_free ( path ) ;
 OPENSSL_free ( port ) ;
 X509_email_free ( aia ) ;
 }
 if ( id ) OCSP_CERTID_free ( id ) ;
 if ( req ) OCSP_REQUEST_free ( req ) ;
 if ( resp ) OCSP_RESPONSE_free ( resp ) ;
 return ret ;
 err : ret = SSL_TLSEXT_ERR_ALERT_FATAL ;
 goto done ;
 }

 unsigned char * data ;
 unsigned int len ;
 }
 tlsextnextprotoctx ;
 static int next_proto_cb ( SSL * s , const unsigned char * * data , unsigned int * len , void * arg ) {
 tlsextnextprotoctx * next_proto = arg ;
 * data = next_proto -> data ;
 * len = next_proto -> len ;
 return SSL_TLSEXT_ERR_OK ;
 }





 X509_VERIFY_PARAM * vpm = NULL ;
 int badarg = 0 ;
 short port = PORT ;
 char * CApath = NULL , * CAfile = NULL ;
 unsigned char * context = NULL ;
 char * dhfile = NULL ;


 int ret = 1 ;
 int off = 0 ;
 int no_tmp_rsa = 0 , no_dhe = 0 , nocert = 0 ;


 const SSL_METHOD * meth = NULL ;
 int socket_type = SOCK_STREAM ;
 ENGINE * e = NULL ;
 char * inrand = NULL ;
 int s_cert_format = FORMAT_PEM , s_key_format = FORMAT_PEM ;
 char * passarg = NULL , * pass = NULL ;
 char * dpassarg = NULL , * dpass = NULL ;
 int s_dcert_format = FORMAT_PEM , s_dkey_format = FORMAT_PEM ;
 X509 * s_cert = NULL , * s_dcert = NULL ;
 EVP_PKEY * s_key = NULL , * s_dkey = NULL ;
 int no_cache = 0 ;

 X509 * s_cert2 = NULL ;
 tlsextctx tlsextcbp = {
 NULL , NULL , SSL_TLSEXT_ERR_ALERT_WARNING }
 ;

 tlsextnextprotoctx next_proto ;


 char * srp_verifier_file = NULL ;

 local_argc = argc ;
 local_argv = argv ;
 apps_startup ( ) ;


 if ( ! load_config ( bio_err , NULL ) ) goto end ;
 verify_depth = 0 ;


 argc -- ;
 argv ++ ;
 while ( argc >= 1 ) {
 if ( ( strcmp ( * argv , "-port" ) == 0 ) || ( strcmp ( * argv , "-accept" ) == 0 ) ) {
 if ( -- argc < 1 ) goto bad ;
 if ( ! extract_port ( * ( ++ argv ) , & port ) ) goto bad ;
 }
 else if ( strcmp ( * argv , "-verify" ) == 0 ) {
 s_server_verify = SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE ;
 if ( -- argc < 1 ) goto bad ;
 verify_depth = atoi ( * ( ++ argv ) ) ;
 BIO_printf ( bio_err , "verify depth is %d\n" , verify_depth ) ;
 }
 else if ( strcmp ( * argv , "-Verify" ) == 0 ) {
 s_server_verify = SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT | SSL_VERIFY_CLIENT_ONCE ;
 if ( -- argc < 1 ) goto bad ;
 verify_depth = atoi ( * ( ++ argv ) ) ;
 BIO_printf ( bio_err , "verify depth is %d, must return a certificate\n" , verify_depth ) ;
 }
 else if ( strcmp ( * argv , "-context" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 context = ( unsigned char * ) * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-cert" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 s_cert_file = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-certform" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 s_cert_format = str2fmt ( * ( ++ argv ) ) ;
 }
 else if ( strcmp ( * argv , "-key" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 s_key_file = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-keyform" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 s_key_format = str2fmt ( * ( ++ argv ) ) ;
 }
 else if ( strcmp ( * argv , "-pass" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 passarg = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-dhparam" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 dhfile = * ( ++ argv ) ;
 }

 if ( -- argc < 1 ) goto bad ;
 named_curve = * ( ++ argv ) ;
 }

 if ( -- argc < 1 ) goto bad ;
 s_dcert_format = str2fmt ( * ( ++ argv ) ) ;
 }
 else if ( strcmp ( * argv , "-dcert" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 s_dcert_file = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-dkeyform" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 s_dkey_format = str2fmt ( * ( ++ argv ) ) ;
 }
 else if ( strcmp ( * argv , "-dpass" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 dpassarg = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-dkey" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 s_dkey_file = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-nocert" ) == 0 ) {
 nocert = 1 ;
 }
 else if ( strcmp ( * argv , "-CApath" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 CApath = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-no_cache" ) == 0 ) no_cache = 1 ;
 else if ( args_verify ( & argv , & argc , & badarg , bio_err , & vpm ) ) {
 if ( badarg ) goto bad ;
 continue ;
 }
 else if ( strcmp ( * argv , "-verify_return_error" ) == 0 ) verify_return_error = 1 ;
 else if ( strcmp ( * argv , "-serverpref" ) == 0 ) {
 off |= SSL_OP_CIPHER_SERVER_PREFERENCE ;
 }
 else if ( strcmp ( * argv , "-legacy_renegotiation" ) == 0 ) off |= SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION ;
 else if ( strcmp ( * argv , "-cipher" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 cipher = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-CAfile" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 CAfile = * ( ++ argv ) ;
 }

 s_nbio = 1 ;
 }



 }
 else if ( strcmp ( * argv , "-debug" ) == 0 ) {
 s_debug = 1 ;
 }

 else if ( strcmp ( * argv , "-status" ) == 0 ) s_tlsextstatus = 1 ;
 else if ( strcmp ( * argv , "-status_verbose" ) == 0 ) {
 s_tlsextstatus = 1 ;
 tlscstatp . verbose = 1 ;
 }
 else if ( ! strcmp ( * argv , "-status_timeout" ) ) {
 s_tlsextstatus = 1 ;
 if ( -- argc < 1 ) goto bad ;
 tlscstatp . timeout = atoi ( * ( ++ argv ) ) ;
 }
 else if ( ! strcmp ( * argv , "-status_url" ) ) {
 s_tlsextstatus = 1 ;
 if ( -- argc < 1 ) goto bad ;
 if ( ! OCSP_parse_url ( * ( ++ argv ) , & tlscstatp . host , & tlscstatp . port , & tlscstatp . path , & tlscstatp . use_ssl ) ) {
 BIO_printf ( bio_err , "Error parsing URL\n" ) ;
 goto bad ;
 }
 }

 s_msg = 1 ;
 }
 else if ( strcmp ( * argv , "-hack" ) == 0 ) {
 hack = 1 ;
 }
 else if ( strcmp ( * argv , "-state" ) == 0 ) {
 state = 1 ;
 }
 else if ( strcmp ( * argv , "-crlf" ) == 0 ) {
 s_crlf = 1 ;
 }
 else if ( strcmp ( * argv , "-quiet" ) == 0 ) {
 s_quiet = 1 ;
 }
 else if ( strcmp ( * argv , "-bugs" ) == 0 ) {
 bugs = 1 ;
 }
 else if ( strcmp ( * argv , "-no_tmp_rsa" ) == 0 ) {
 no_tmp_rsa = 1 ;
 }
 else if ( strcmp ( * argv , "-no_dhe" ) == 0 ) {
 no_dhe = 1 ;
 }

 no_ecdhe = 1 ;
 }

 if ( -- argc < 1 ) goto bad ;
 psk_identity_hint = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-psk" ) == 0 ) {
 size_t i ;
 if ( -- argc < 1 ) goto bad ;
 psk_key = * ( ++ argv ) ;
 for ( i = 0 ;
 i < strlen ( psk_key ) ;
 i ++ ) {
 if ( isxdigit ( ( unsigned char ) psk_key [ i ] ) ) continue ;
 BIO_printf ( bio_err , "Not a hex number '%s'\n" , * argv ) ;
 goto bad ;
 }
 }

 if ( -- argc < 1 ) goto bad ;
 srp_verifier_file = * ( ++ argv ) ;
 meth = TLSv1_server_method ( ) ;
 }
 else if ( strcmp ( * argv , "-srpuserseed" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 srpuserseed = * ( ++ argv ) ;
 meth = TLSv1_server_method ( ) ;
 }

 www = 1 ;
 }
 else if ( strcmp ( * argv , "-WWW" ) == 0 ) {
 www = 2 ;
 }
 else if ( strcmp ( * argv , "-HTTP" ) == 0 ) {
 www = 3 ;
 }
 else if ( strcmp ( * argv , "-no_ssl2" ) == 0 ) {
 off |= SSL_OP_NO_SSLv2 ;
 }
 else if ( strcmp ( * argv , "-no_ssl3" ) == 0 ) {
 off |= SSL_OP_NO_SSLv3 ;
 }
 else if ( strcmp ( * argv , "-no_tls1" ) == 0 ) {
 off |= SSL_OP_NO_TLSv1 ;
 }
 else if ( strcmp ( * argv , "-no_tls1_1" ) == 0 ) {
 off |= SSL_OP_NO_TLSv1_1 ;
 }
 else if ( strcmp ( * argv , "-no_tls1_2" ) == 0 ) {
 off |= SSL_OP_NO_TLSv1_2 ;
 }
 else if ( strcmp ( * argv , "-no_comp" ) == 0 ) {
 off |= SSL_OP_NO_COMPRESSION ;
 }

 off |= SSL_OP_NO_TICKET ;
 }

 meth = SSLv2_server_method ( ) ;
 }

 meth = SSLv3_server_method ( ) ;
 }

 meth = TLSv1_server_method ( ) ;
 }
 else if ( strcmp ( * argv , "-tls1_1" ) == 0 ) {
 meth = TLSv1_1_server_method ( ) ;
 }
 else if ( strcmp ( * argv , "-tls1_2" ) == 0 ) {
 meth = TLSv1_2_server_method ( ) ;
 }

 meth = DTLSv1_server_method ( ) ;
 socket_type = SOCK_DGRAM ;
 }
 else if ( strcmp ( * argv , "-timeout" ) == 0 ) enable_timeouts = 1 ;
 else if ( strcmp ( * argv , "-mtu" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 socket_mtu = atol ( * ( ++ argv ) ) ;
 }
 else if ( strcmp ( * argv , "-chain" ) == 0 ) cert_chain = 1 ;

 if ( -- argc < 1 ) goto bad ;
 session_id_prefix = * ( ++ argv ) ;
 }

 if ( -- argc < 1 ) goto bad ;
 engine_id = * ( ++ argv ) ;
 }

 if ( -- argc < 1 ) goto bad ;
 inrand = * ( ++ argv ) ;
 }

 if ( -- argc < 1 ) goto bad ;
 tlsextcbp . servername = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-servername_fatal" ) == 0 ) {
 tlsextcbp . extension_error = SSL_TLSEXT_ERR_ALERT_FATAL ;
 }
 else if ( strcmp ( * argv , "-cert2" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 s_cert_file2 = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-key2" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 s_key_file2 = * ( ++ argv ) ;
 }

 if ( -- argc < 1 ) goto bad ;
 next_proto_neg_in = * ( ++ argv ) ;
 }

 if ( -- argc < 1 ) goto bad ;
 jpake_secret = * ( ++ argv ) ;
 }

 if ( -- argc < 1 ) goto bad ;
 srtp_profiles = * ( ++ argv ) ;
 }

 if ( -- argc < 1 ) goto bad ;
 keymatexportlabel = * ( ++ argv ) ;
 }
 else if ( strcmp ( * argv , "-keymatexportlen" ) == 0 ) {
 if ( -- argc < 1 ) goto bad ;
 keymatexportlen = atoi ( * ( ++ argv ) ) ;
 if ( keymatexportlen == 0 ) goto bad ;
 }
 else {
 BIO_printf ( bio_err , "unknown option %s\n" , * argv ) ;
 badop = 1 ;
 break ;
 }
 argc -- ;
 argv ++ ;
 }
 if ( badop ) {
 bad : sv_usage ( ) ;
 goto end ;
 }

 BIO_printf ( bio_err , "Can't use -HTTP, -www or -WWW with DTLS\n" ) ;
 goto end ;
 }

 if ( psk_key ) {
 BIO_printf ( bio_err , "Can't use JPAKE and PSK together\n" ) ;
 goto end ;
 }
 psk_identity = "JPAKE" ;
 if ( cipher ) {
 BIO_printf ( bio_err , "JPAKE sets cipher to PSK\n" ) ;
 goto end ;
 }
 cipher = "PSK" ;
 }

 OpenSSL_add_ssl_algorithms ( ) ;


 BIO_printf ( bio_err , "Error getting password\n" ) ;
 goto end ;
 }
 if ( s_key_file == NULL ) s_key_file = s_cert_file ;


 s_key = load_key ( bio_err , s_key_file , s_key_format , 0 , pass , e , "server certificate private key file" ) ;
 if ( ! s_key ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 s_cert = load_cert ( bio_err , s_cert_file , s_cert_format , NULL , e , "server certificate file" ) ;
 if ( ! s_cert ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }

 s_key2 = load_key ( bio_err , s_key_file2 , s_key_format , 0 , pass , e , "second server certificate private key file" ) ;
 if ( ! s_key2 ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 s_cert2 = load_cert ( bio_err , s_cert_file2 , s_cert_format , NULL , e , "second server certificate file" ) ;
 if ( ! s_cert2 ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 }


 unsigned short len ;
 next_proto . data = next_protos_parse ( & len , next_proto_neg_in ) ;
 if ( next_proto . data == NULL ) goto end ;
 next_proto . len = len ;
 }
 else {
 next_proto . data = NULL ;
 }

 if ( s_dkey_file == NULL ) s_dkey_file = s_dcert_file ;
 s_dkey = load_key ( bio_err , s_dkey_file , s_dkey_format , 0 , dpass , e , "second certificate private key file" ) ;
 if ( ! s_dkey ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 s_dcert = load_cert ( bio_err , s_dcert_file , s_dcert_format , NULL , e , "second server certificate file" ) ;
 if ( ! s_dcert ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 }
 if ( ! app_RAND_load_file ( NULL , bio_err , 1 ) && inrand == NULL && ! RAND_status ( ) ) {
 BIO_printf ( bio_err , "warning, not much extra random data, consider using the -rand option\n" ) ;
 }
 if ( inrand != NULL ) BIO_printf ( bio_err , "%ld semi-random bytes loaded\n" , app_RAND_load_files ( inrand ) ) ;
 if ( bio_s_out == NULL ) {
 if ( s_quiet && ! s_debug && ! s_msg ) {
 bio_s_out = BIO_new ( BIO_s_null ( ) ) ;
 }
 else {
 if ( bio_s_out == NULL ) bio_s_out = BIO_new_fp ( stdout , BIO_NOCLOSE ) ;
 }
 }

 s_cert_file = NULL ;
 s_key_file = NULL ;
 s_dcert_file = NULL ;
 s_dkey_file = NULL ;

 s_key_file2 = NULL ;

 ctx = SSL_CTX_new ( meth ) ;
 if ( ctx == NULL ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 if ( session_id_prefix ) {
 if ( strlen ( session_id_prefix ) >= 32 ) BIO_printf ( bio_err , "warning: id_prefix is too long, only one new session will be possible\n" ) ;
 else if ( strlen ( session_id_prefix ) >= 16 ) BIO_printf ( bio_err , "warning: id_prefix is too long if you use SSLv2\n" ) ;
 if ( ! SSL_CTX_set_generate_session_id ( ctx , generate_session_id ) ) {
 BIO_printf ( bio_err , "error setting 'id_prefix'\n" ) ;
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 BIO_printf ( bio_err , "id_prefix '%s' set.\n" , session_id_prefix ) ;
 }
 SSL_CTX_set_quiet_shutdown ( ctx , 1 ) ;
 if ( bugs ) SSL_CTX_set_options ( ctx , SSL_OP_ALL ) ;
 if ( hack ) SSL_CTX_set_options ( ctx , SSL_OP_NETSCAPE_DEMO_CIPHER_CHANGE_BUG ) ;
 SSL_CTX_set_options ( ctx , off ) ;
 if ( state ) SSL_CTX_set_info_callback ( ctx , apps_ssl_info_callback ) ;
 if ( no_cache ) SSL_CTX_set_session_cache_mode ( ctx , SSL_SESS_CACHE_OFF ) ;
 else SSL_CTX_sess_set_cache_size ( ctx , 128 ) ;



 BIO_printf ( bio_err , "You must specify a certificate file for the server to use\n" ) ;
 goto end ;
 }

 ERR_print_errors ( bio_err ) ;
 }
 if ( vpm ) SSL_CTX_set1_param ( ctx , vpm ) ;

 ctx2 = SSL_CTX_new ( meth ) ;
 if ( ctx2 == NULL ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 }
 if ( ctx2 ) {
 BIO_printf ( bio_s_out , "Setting secondary ctx parameters\n" ) ;
 if ( session_id_prefix ) {
 if ( strlen ( session_id_prefix ) >= 32 ) BIO_printf ( bio_err , "warning: id_prefix is too long, only one new session will be possible\n" ) ;
 else if ( strlen ( session_id_prefix ) >= 16 ) BIO_printf ( bio_err , "warning: id_prefix is too long if you use SSLv2\n" ) ;
 if ( ! SSL_CTX_set_generate_session_id ( ctx2 , generate_session_id ) ) {
 BIO_printf ( bio_err , "error setting 'id_prefix'\n" ) ;
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 BIO_printf ( bio_err , "id_prefix '%s' set.\n" , session_id_prefix ) ;
 }
 SSL_CTX_set_quiet_shutdown ( ctx2 , 1 ) ;
 if ( bugs ) SSL_CTX_set_options ( ctx2 , SSL_OP_ALL ) ;
 if ( hack ) SSL_CTX_set_options ( ctx2 , SSL_OP_NETSCAPE_DEMO_CIPHER_CHANGE_BUG ) ;
 SSL_CTX_set_options ( ctx2 , off ) ;
 if ( state ) SSL_CTX_set_info_callback ( ctx2 , apps_ssl_info_callback ) ;
 if ( no_cache ) SSL_CTX_set_session_cache_mode ( ctx2 , SSL_SESS_CACHE_OFF ) ;
 else SSL_CTX_sess_set_cache_size ( ctx2 , 128 ) ;
 if ( ( ! SSL_CTX_load_verify_locations ( ctx2 , CAfile , CApath ) ) || ( ! SSL_CTX_set_default_verify_paths ( ctx2 ) ) ) {
 ERR_print_errors ( bio_err ) ;
 }
 if ( vpm ) SSL_CTX_set1_param ( ctx2 , vpm ) ;
 }


 DH * dh = NULL ;
 if ( dhfile ) dh = load_dh_param ( dhfile ) ;
 else if ( s_cert_file ) dh = load_dh_param ( s_cert_file ) ;
 if ( dh != NULL ) {
 BIO_printf ( bio_s_out , "Setting temp DH parameters\n" ) ;
 }
 else {
 BIO_printf ( bio_s_out , "Using default temp DH parameters\n" ) ;
 dh = get_dh2048 ( ) ;
 if ( dh == NULL ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 }
 ( void ) BIO_flush ( bio_s_out ) ;
 SSL_CTX_set_tmp_dh ( ctx , dh ) ;

 if ( ! dhfile ) {
 DH * dh2 = load_dh_param ( s_cert_file2 ) ;
 if ( dh2 != NULL ) {
 BIO_printf ( bio_s_out , "Setting temp DH parameters\n" ) ;
 ( void ) BIO_flush ( bio_s_out ) ;
 DH_free ( dh ) ;
 dh = dh2 ;
 }
 }
 SSL_CTX_set_tmp_dh ( ctx2 , dh ) ;
 }

 }

 EC_KEY * ecdh = NULL ;
 if ( named_curve ) {
 int nid = OBJ_sn2nid ( named_curve ) ;
 if ( nid == 0 ) {
 BIO_printf ( bio_err , "unknown curve name (%s)\n" , named_curve ) ;
 goto end ;
 }
 ecdh = EC_KEY_new_by_curve_name ( nid ) ;
 if ( ecdh == NULL ) {
 BIO_printf ( bio_err , "unable to create curve (%s)\n" , named_curve ) ;
 goto end ;
 }
 }
 if ( ecdh != NULL ) {
 BIO_printf ( bio_s_out , "Setting temp ECDH parameters\n" ) ;
 }
 else {
 BIO_printf ( bio_s_out , "Using default temp ECDH parameters\n" ) ;
 ecdh = EC_KEY_new_by_curve_name ( NID_X9_62_prime256v1 ) ;
 if ( ecdh == NULL ) {
 BIO_printf ( bio_err , "unable to create curve (nistp256)\n" ) ;
 goto end ;
 }
 }
 ( void ) BIO_flush ( bio_s_out ) ;
 SSL_CTX_set_tmp_ecdh ( ctx , ecdh ) ;


 }



 if ( ! set_cert_key_stuff ( ctx , s_dcert , s_dkey ) ) goto end ;
 }

 SSL_CTX_set_tmp_rsa_callback ( ctx , tmp_rsa_cb ) ;



 RSA * rsa ;
 BIO_printf ( bio_s_out , "Generating temp (512 bit) RSA key..." ) ;
 BIO_flush ( bio_s_out ) ;
 rsa = RSA_generate_key ( 512 , RSA_F4 , NULL ) ;
 if ( ! SSL_CTX_set_tmp_rsa ( ctx , rsa ) ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }

 if ( ! SSL_CTX_set_tmp_rsa ( ctx2 , rsa ) ) {
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }
 }

 BIO_printf ( bio_s_out , "\n" ) ;
 }

 if ( s_debug ) BIO_printf ( bio_s_out , "PSK key given or JPAKE in use, setting server callback\n" ) ;
 SSL_CTX_set_psk_server_callback ( ctx , psk_server_cb ) ;
 }
 if ( ! SSL_CTX_use_psk_identity_hint ( ctx , psk_identity_hint ) ) {
 BIO_printf ( bio_err , "error setting PSK identity hint to context\n" ) ;
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }

 if ( ! SSL_CTX_set_cipher_list ( ctx , cipher ) ) {
 BIO_printf ( bio_err , "error setting cipher list\n" ) ;
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }

 BIO_printf ( bio_err , "error setting cipher list\n" ) ;
 ERR_print_errors ( bio_err ) ;
 goto end ;
 }

 SSL_CTX_set_verify ( ctx , s_server_verify , verify_callback ) ;
 SSL_CTX_set_session_id_context ( ctx , ( void * ) & s_server_session_id_context , sizeof s_server_session_id_context ) ;
 SSL_CTX_set_cookie_generate_cb ( ctx , generate_cookie_callback ) ;
 SSL_CTX_set_cookie_verify_cb ( ctx , verify_cookie_callback ) ;

 SSL_CTX_set_verify ( ctx2 , s_server_verify , verify_callback ) ;
 SSL_CTX_set_session_id_context ( ctx2 , ( void * ) & s_server_session_id_context , sizeof s_server_session_id_context ) ;
 tlsextcbp . biodebug = bio_s_out ;
 SSL_CTX_set_tlsext_servername_callback ( ctx2 , ssl_servername_cb ) ;
 SSL_CTX_set_tlsext_servername_arg ( ctx2 , & tlsextcbp ) ;
 SSL_CTX_set_tlsext_servername_callback ( ctx , ssl_servername_cb ) ;
 SSL_CTX_set_tlsext_servername_arg ( ctx , & tlsextcbp ) ;
 }

 srp_callback_parm . vb = SRP_VBASE_new ( srpuserseed ) ;
 srp_callback_parm . user = NULL ;
 srp_callback_parm . login = NULL ;
 if ( ( ret = SRP_VBASE_init ( srp_callback_parm . vb , srp_verifier_file ) ) != SRP_NO_ERROR ) {
 BIO_printf ( bio_err , "Cannot initialize SRP verifier file \"%s\":ret=%d\n" , srp_verifier_file , ret ) ;
 goto end ;
 }
 SSL_CTX_set_verify ( ctx , SSL_VERIFY_NONE , verify_callback ) ;
 SSL_CTX_set_srp_cb_arg ( ctx , & srp_callback_parm ) ;
 SSL_CTX_set_srp_username_callback ( ctx , ssl_srp_server_param_cb ) ;
 }
 else # endif if ( CAfile != NULL ) {
 SSL_CTX_set_client_CA_list ( ctx , SSL_load_client_CA_file ( CAfile ) ) ;


 BIO_printf ( bio_s_out , "ACCEPT\n" ) ;
 ( void ) BIO_flush ( bio_s_out ) ;
 if ( www ) do_server ( port , socket_type , & accept_socket , www_body , context ) ;
 else do_server ( port , socket_type , & accept_socket , sv_body , context ) ;
 print_stats ( bio_s_out , ctx ) ;
 ret = 0 ;
 end : if ( ctx != NULL ) SSL_CTX_free ( ctx ) ;
 if ( s_cert ) X509_free ( s_cert ) ;
 if ( s_dcert ) X509_free ( s_dcert ) ;
 if ( s_key ) EVP_PKEY_free ( s_key ) ;
 if ( s_dkey ) EVP_PKEY_free ( s_dkey ) ;
 if ( pass ) OPENSSL_free ( pass ) ;
 if ( dpass ) OPENSSL_free ( dpass ) ;
 if ( vpm ) X509_VERIFY_PARAM_free ( vpm ) ;

 if ( tlscstatp . port ) OPENSSL_free ( tlscstatp . port ) ;
 if ( tlscstatp . path ) OPENSSL_free ( tlscstatp . path ) ;
 if ( ctx2 != NULL ) SSL_CTX_free ( ctx2 ) ;
 if ( s_cert2 ) X509_free ( s_cert2 ) ;
 if ( s_key2 ) EVP_PKEY_free ( s_key2 ) ;

 BIO_free ( bio_s_out ) ;
 bio_s_out = NULL ;
 }
 apps_shutdown ( ) ;
 OPENSSL_EXIT ( ret ) ;
 }
 static void print_stats ( BIO * bio , SSL_CTX * ssl_ctx ) {
 BIO_printf ( bio , "%4ld items in the session cache\n" , SSL_CTX_sess_number ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld client connects (SSL_connect())\n" , SSL_CTX_sess_connect ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld client renegotiates (SSL_connect())\n" , SSL_CTX_sess_connect_renegotiate ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld client connects that finished\n" , SSL_CTX_sess_connect_good ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld server accepts (SSL_accept())\n" , SSL_CTX_sess_accept ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld server renegotiates (SSL_accept())\n" , SSL_CTX_sess_accept_renegotiate ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld server accepts that finished\n" , SSL_CTX_sess_accept_good ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld session cache hits\n" , SSL_CTX_sess_hits ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld session cache misses\n" , SSL_CTX_sess_misses ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld session cache timeouts\n" , SSL_CTX_sess_timeouts ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld callback cache hits\n" , SSL_CTX_sess_cb_hits ( ssl_ctx ) ) ;
 BIO_printf ( bio , "%4ld cache full overflows (%ld allowed)\n" , SSL_CTX_sess_cache_full ( ssl_ctx ) , SSL_CTX_sess_get_cache_size ( ssl_ctx ) ) ;
 }
 static int sv_body ( char * hostname , int s , unsigned char * context ) {
 char * buf = NULL ;
 fd_set readfds ;
 int ret = 1 , width ;
 int k , i ;
 unsigned long l ;
 SSL * con = NULL ;
 BIO * sbio ;





 BIO_printf ( bio_err , "out of memory\n" ) ;
 goto err ;
 }

 unsigned long sl = 1 ;
 if ( ! s_quiet ) BIO_printf ( bio_err , "turning on non blocking io\n" ) ;
 if ( BIO_socket_ioctl ( s , FIONBIO , & sl ) < 0 ) ERR_print_errors ( bio_err ) ;
 }

 con = SSL_new ( ctx ) ;

 SSL_set_tlsext_debug_callback ( con , tlsext_cb ) ;
 SSL_set_tlsext_debug_arg ( con , bio_s_out ) ;
 }
 if ( s_tlsextstatus ) {
 SSL_CTX_set_tlsext_status_cb ( ctx , cert_status_cb ) ;
 tlscstatp . err = bio_err ;
 SSL_CTX_set_tlsext_status_arg ( ctx , & tlscstatp ) ;
 }

 SSL_set0_kssl_ctx ( con , kctx ) ;
 kssl_ctx_setstring ( kctx , KSSL_SERVICE , KRB5SVC ) ;
 kssl_ctx_setstring ( kctx , KSSL_KEYTAB , KRB5KEYTAB ) ;
 }

 }
 SSL_clear ( con ) ;


 sbio = BIO_new_dgram ( s , BIO_NOCLOSE ) ;
 if ( enable_timeouts ) {
 timeout . tv_sec = 0 ;
 timeout . tv_usec = DGRAM_RCV_TIMEOUT ;
 BIO_ctrl ( sbio , BIO_CTRL_DGRAM_SET_RECV_TIMEOUT , 0 , & timeout ) ;
 timeout . tv_sec = 0 ;
 timeout . tv_usec = DGRAM_SND_TIMEOUT ;
 BIO_ctrl ( sbio , BIO_CTRL_DGRAM_SET_SEND_TIMEOUT , 0 , & timeout ) ;
 }
 if ( socket_mtu ) {
 if ( socket_mtu < DTLS_get_link_min_mtu ( con ) ) {
 BIO_printf ( bio_err , "MTU too small. Must be at least %ld\n" , DTLS_get_link_min_mtu ( con ) ) ;
 ret = - 1 ;
 BIO_free ( sbio ) ;
 goto err ;
 }
 SSL_set_options ( con , SSL_OP_NO_QUERY_MTU ) ;
 if ( ! DTLS_set_link_mtu ( con , socket_mtu ) ) {
 BIO_printf ( bio_err , "Failed to set MTU\n" ) ;
 ret = - 1 ;
 BIO_free ( sbio ) ;
 goto err ;
 }
 }
 else BIO_ctrl ( sbio , BIO_CTRL_DGRAM_MTU_DISCOVER , 0 , NULL ) ;
 SSL_set_options ( con , SSL_OP_COOKIE_EXCHANGE ) ;
 }
 else sbio = BIO_new_socket ( s , BIO_NOCLOSE ) ;
 if ( s_nbio_test ) {
 BIO * test ;
 test = BIO_new ( BIO_f_nbio_test ( ) ) ;
 sbio = BIO_push ( test , sbio ) ;
 }


 SSL_set_accept_state ( con ) ;
 if ( s_debug ) {
 SSL_set_debug ( con , 1 ) ;
 BIO_set_callback ( SSL_get_rbio ( con ) , bio_dump_callback ) ;
 BIO_set_callback_arg ( SSL_get_rbio ( con ) , ( char * ) bio_s_out ) ;
 }
 if ( s_msg ) {
 SSL_set_msg_callback ( con , msg_cb ) ;
 SSL_set_msg_callback_arg ( con , bio_s_out ) ;
 }

 SSL_set_tlsext_debug_callback ( con , tlsext_cb ) ;
 SSL_set_tlsext_debug_arg ( con , bio_s_out ) ;
 }

 for ( ;
 ;
 ) {
 int read_from_terminal ;
 int read_from_sslcon ;
 read_from_terminal = 0 ;
 read_from_sslcon = SSL_pending ( con ) ;
 if ( ! read_from_sslcon ) {
 FD_ZERO ( & readfds ) ;



 tv . tv_usec = 0 ;
 i = select ( width , ( void * ) & readfds , NULL , NULL , & tv ) ;
 if ( ( i < 0 ) || ( ! i && ! _kbhit ( ) ) ) continue ;
 if ( _kbhit ( ) ) read_from_terminal = 1 ;

 tv . tv_usec = 0 ;
 ( void ) fcntl ( fileno ( stdin ) , F_SETFL , O_NONBLOCK ) ;
 i = select ( width , ( void * ) & readfds , NULL , NULL , & tv ) ;
 if ( ( i < 0 ) || ( ! i && read ( fileno ( stdin ) , buf , 0 ) < 0 ) ) continue ;
 if ( read ( fileno ( stdin ) , buf , 0 ) >= 0 ) read_from_terminal = 1 ;
 ( void ) fcntl ( fileno ( stdin ) , F_SETFL , 0 ) ;

 else timeoutp = NULL ;
 i = select ( width , ( void * ) & readfds , NULL , NULL , timeoutp ) ;
 if ( ( SSL_version ( con ) == DTLS1_VERSION ) && DTLSv1_handle_timeout ( con ) > 0 ) {
 BIO_printf ( bio_err , "TIMEOUT occured\n" ) ;
 }
 if ( i <= 0 ) continue ;
 if ( FD_ISSET ( fileno ( stdin ) , & readfds ) ) read_from_terminal = 1 ;

 }
 if ( read_from_terminal ) {
 if ( s_crlf ) {
 int j , lf_num ;
 i = raw_read_stdin ( buf , bufsize / 2 ) ;
 lf_num = 0 ;
 for ( j = 0 ;
 j < i ;
 j ++ ) if ( buf [ j ] == '\n' ) lf_num ++ ;
 for ( j = i - 1 ;
 j >= 0 ;
 j -- ) {
 buf [ j + lf_num ] = buf [ j ] ;
 if ( buf [ j ] == '\n' ) {
 lf_num -- ;
 i ++ ;
 buf [ j + lf_num ] = '\r' ;
 }
 }
 assert ( lf_num == 0 ) ;
 }
 else i = raw_read_stdin ( buf , bufsize ) ;
 if ( ! s_quiet ) {
 if ( ( i <= 0 ) || ( buf [ 0 ] == 'Q' ) ) {
 BIO_printf ( bio_s_out , "DONE\n" ) ;
 SHUTDOWN ( s ) ;
 close_accept_socket ( ) ;
 ret = - 11 ;
 goto err ;
 }
 if ( ( i <= 0 ) || ( buf [ 0 ] == 'q' ) ) {
 BIO_printf ( bio_s_out , "DONE\n" ) ;
 if ( SSL_version ( con ) != DTLS1_VERSION ) SHUTDOWN ( s ) ;
 goto err ;
 }

 BIO_printf ( bio_err , "HEARTBEATING\n" ) ;
 SSL_heartbeat ( con ) ;
 i = 0 ;
 continue ;
 }

 SSL_renegotiate ( con ) ;
 i = SSL_do_handshake ( con ) ;
 printf ( "SSL_do_handshake -> %d\n" , i ) ;
 i = 0 ;
 continue ;
 }
 if ( ( buf [ 0 ] == 'R' ) && ( ( buf [ 1 ] == '\n' ) || ( buf [ 1 ] == '\r' ) ) ) {
 SSL_set_verify ( con , SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE , NULL ) ;
 SSL_renegotiate ( con ) ;
 i = SSL_do_handshake ( con ) ;
 printf ( "SSL_do_handshake -> %d\n" , i ) ;
 i = 0 ;
 continue ;
 }
 if ( buf [ 0 ] == 'P' ) {
 static const char * str = "Lets print some clear text\n" ;
 BIO_write ( SSL_get_wbio ( con ) , str , strlen ( str ) ) ;
 }
 if ( buf [ 0 ] == 'S' ) {
 print_stats ( bio_s_out , SSL_get_SSL_CTX ( con ) ) ;
 }
 }


 for ( ;
 ;
 ) {

 static count = 0 ;
 if ( ++ count == 100 ) {
 count = 0 ;
 SSL_renegotiate ( con ) ;
 }
 }


 BIO_printf ( bio_s_out , "LOOKUP renego during write\n" ) ;
 SRP_user_pwd_free ( srp_callback_parm . user ) ;
 srp_callback_parm . user = SRP_VBASE_get1_by_user ( srp_callback_parm . vb , srp_callback_parm . login ) ;
 if ( srp_callback_parm . user ) BIO_printf ( bio_s_out , "LOOKUP done %s\n" , srp_callback_parm . user -> info ) ;
 else BIO_printf ( bio_s_out , "LOOKUP not successful\n" ) ;
 k = SSL_write ( con , & ( buf [ l ] ) , ( unsigned int ) i ) ;
 }

 case SSL_ERROR_NONE : break ;
 case SSL_ERROR_WANT_WRITE : case SSL_ERROR_WANT_READ : case SSL_ERROR_WANT_X509_LOOKUP : BIO_printf ( bio_s_out , "Write BLOCK\n" ) ;
 break ;
 case SSL_ERROR_SYSCALL : case SSL_ERROR_SSL : BIO_printf ( bio_s_out , "ERROR\n" ) ;
 ERR_print_errors ( bio_err ) ;
 ret = 1 ;
 goto err ;
 case SSL_ERROR_ZERO_RETURN : BIO_printf ( bio_s_out , "DONE\n" ) ;
 ret = 1 ;
 goto err ;
 }
 if ( k > 0 ) {
 l += k ;
 i -= k ;
 }
 if ( i <= 0 ) break ;
 }
 }
 if ( read_from_sslcon ) {
 if ( ! SSL_is_init_finished ( con ) ) {
 i = init_ssl_connection ( con ) ;
 if ( i < 0 ) {
 ret = 0 ;
 goto err ;
 }
 else if ( i == 0 ) {
 ret = 1 ;
 goto err ;
 }
 }
 else {
 again : i = SSL_read ( con , ( char * ) buf , bufsize ) ;

 BIO_printf ( bio_s_out , "LOOKUP renego during read\n" ) ;
 SRP_user_pwd_free ( srp_callback_parm . user ) ;
 srp_callback_parm . user = SRP_VBASE_get1_by_user ( srp_callback_parm . vb , srp_callback_parm . login ) ;
 if ( srp_callback_parm . user ) BIO_printf ( bio_s_out , "LOOKUP done %s\n" , srp_callback_parm . user -> info ) ;
 else BIO_printf ( bio_s_out , "LOOKUP not successful\n" ) ;
 i = SSL_read ( con , ( char * ) buf , bufsize ) ;
 }

 case SSL_ERROR_NONE : # ifdef CHARSET_EBCDIC ascii2ebcdic ( buf , buf , i ) ;

 if ( SSL_pending ( con ) ) goto again ;
 break ;
 case SSL_ERROR_WANT_WRITE : case SSL_ERROR_WANT_READ : BIO_printf ( bio_s_out , "Read BLOCK\n" ) ;
 break ;
 case SSL_ERROR_SYSCALL : case SSL_ERROR_SSL : BIO_printf ( bio_s_out , "ERROR\n" ) ;
 ERR_print_errors ( bio_err ) ;
 ret = 1 ;
 goto err ;
 case SSL_ERROR_ZERO_RETURN : BIO_printf ( bio_s_out , "DONE\n" ) ;
 ret = 1 ;
 goto err ;
 }
 }
 }
 }
 err : if ( con != NULL ) {
 BIO_printf ( bio_s_out , "shutting down SSL\n" ) ;



 }
 BIO_printf ( bio_s_out , "CONNECTION CLOSED\n" ) ;
 if ( buf != NULL ) {
 OPENSSL_cleanse ( buf , bufsize ) ;
 OPENSSL_free ( buf ) ;
 }
 if ( ret >= 0 ) BIO_printf ( bio_s_out , "ACCEPT\n" ) ;
 return ( ret ) ;
 }
 static void close_accept_socket ( void ) {
 BIO_printf ( bio_err , "shutdown accept socket\n" ) ;
 if ( accept_socket >= 0 ) {
 SHUTDOWN2 ( accept_socket ) ;
 }
 }
 static int init_ssl_connection ( SSL * con ) {
 int i ;
 const char * str ;
 X509 * peer ;
 long verify_error ;
 MS_STATIC char buf [ BUFSIZ ] ;


 unsigned next_proto_neg_len ;

 i = SSL_accept ( con ) ;

 BIO_printf ( bio_s_out , "LOOKUP during accept %s\n" , srp_callback_parm . login ) ;
 SRP_user_pwd_free ( srp_callback_parm . user ) ;
 srp_callback_parm . user = SRP_VBASE_get1_by_user ( srp_callback_parm . vb , srp_callback_parm . login ) ;
 if ( srp_callback_parm . user ) BIO_printf ( bio_s_out , "LOOKUP done %s\n" , srp_callback_parm . user -> info ) ;
 else BIO_printf ( bio_s_out , "LOOKUP not successful\n" ) ;
 i = SSL_accept ( con ) ;
 }

 if ( BIO_sock_should_retry ( i ) ) {
 BIO_printf ( bio_s_out , "DELAY\n" ) ;
 return ( 1 ) ;
 }
 BIO_printf ( bio_err , "ERROR\n" ) ;
 verify_error = SSL_get_verify_result ( con ) ;
 if ( verify_error != X509_V_OK ) {
 BIO_printf ( bio_err , "verify error:%s\n" , X509_verify_cert_error_string ( verify_error ) ) ;
 }
 else ERR_print_errors ( bio_err ) ;
 return ( 0 ) ;
 }
 PEM_write_bio_SSL_SESSION ( bio_s_out , SSL_get_session ( con ) ) ;
 peer = SSL_get_peer_certificate ( con ) ;
 if ( peer != NULL ) {
 BIO_printf ( bio_s_out , "Client certificate\n" ) ;
 PEM_write_bio_X509 ( bio_s_out , peer ) ;
 X509_NAME_oneline ( X509_get_subject_name ( peer ) , buf , sizeof buf ) ;
 BIO_printf ( bio_s_out , "subject=%s\n" , buf ) ;
 X509_NAME_oneline ( X509_get_issuer_name ( peer ) , buf , sizeof buf ) ;
 BIO_printf ( bio_s_out , "issuer=%s\n" , buf ) ;
 X509_free ( peer ) ;
 }
 if ( SSL_get_shared_ciphers ( con , buf , sizeof buf ) != NULL ) BIO_printf ( bio_s_out , "Shared ciphers:%s\n" , buf ) ;
 str = SSL_CIPHER_get_name ( SSL_get_current_cipher ( con ) ) ;
 BIO_printf ( bio_s_out , "CIPHER is %s\n" , ( str != NULL ) ? str : "(NONE)" ) ;

 if ( next_proto_neg ) {
 BIO_printf ( bio_s_out , "NEXTPROTO is " ) ;
 BIO_write ( bio_s_out , next_proto_neg , next_proto_neg_len ) ;
 BIO_printf ( bio_s_out , "\n" ) ;
 }

 SRTP_PROTECTION_PROFILE * srtp_profile = SSL_get_selected_srtp_profile ( con ) ;
 if ( srtp_profile ) BIO_printf ( bio_s_out , "SRTP Extension negotiated, profile=%s\n" , srtp_profile -> name ) ;
 }

 if ( SSL_ctrl ( con , SSL_CTRL_GET_FLAGS , 0 , NULL ) & TLS1_FLAGS_TLS_PADDING_BUG ) BIO_printf ( bio_s_out , "Peer has incorrect TLSv1 block padding\n" ) ;

 if ( client_princ != NULL ) {
 BIO_printf ( bio_s_out , "Kerberos peer principal is %s\n" , client_princ ) ;
 }

 if ( keymatexportlabel != NULL ) {
 BIO_printf ( bio_s_out , "Keying material exporter:\n" ) ;
 BIO_printf ( bio_s_out , " Label: '%s'\n" , keymatexportlabel ) ;
 BIO_printf ( bio_s_out , " Length: %i bytes\n" , keymatexportlen ) ;
 exportedkeymat = OPENSSL_malloc ( keymatexportlen ) ;
 if ( exportedkeymat != NULL ) {
 if ( ! SSL_export_keying_material ( con , exportedkeymat , keymatexportlen , keymatexportlabel , strlen ( keymatexportlabel ) , NULL , 0 , 0 ) ) {
 BIO_printf ( bio_s_out , " Error\n" ) ;
 }
 else {
 BIO_printf ( bio_s_out , " Keying material: " ) ;
 for ( i = 0 ;
 i < keymatexportlen ;
 i ++ ) BIO_printf ( bio_s_out , "%02X" , exportedkeymat [ i ] ) ;
 BIO_printf ( bio_s_out , "\n" ) ;
 }
 OPENSSL_free ( exportedkeymat ) ;
 }
 }
 return ( 1 ) ;
 }

 DH * ret = NULL ;
 BIO * bio ;
 if ( ( bio = BIO_new_file ( dhfile , "r" ) ) == NULL ) goto err ;
 ret = PEM_read_bio_DHparams ( bio , NULL , NULL , NULL ) ;
 err : if ( bio != NULL ) BIO_free ( bio ) ;
 return ( ret ) ;
 }


 FILE * in ;
 X509 * x = NULL ;
 if ( ( in = fopen ( file , "r" ) ) == NULL ) return ( 0 ) ;
 for ( ;
 ;
 ) {
 if ( PEM_read_X509 ( in , & x , NULL ) == NULL ) break ;
 SSL_CTX_add_client_CA ( ctx , x ) ;
 }
 if ( x != NULL ) X509_free ( x ) ;
 fclose ( in ) ;
 return ( 1 ) ;
 }

 char * buf = NULL ;
 int ret = 1 ;
 int i , j , k , dot ;
 SSL * con ;
 const SSL_CIPHER * c ;
 BIO * io , * ssl_bio , * sbio ;


 if ( buf == NULL ) return ( 0 ) ;
 io = BIO_new ( BIO_f_buffer ( ) ) ;
 ssl_bio = BIO_new ( BIO_f_ssl ( ) ) ;
 if ( ( io == NULL ) || ( ssl_bio == NULL ) ) goto err ;

 unsigned long sl = 1 ;
 if ( ! s_quiet ) BIO_printf ( bio_err , "turning on non blocking io\n" ) ;
 if ( BIO_socket_ioctl ( s , FIONBIO , & sl ) < 0 ) ERR_print_errors ( bio_err ) ;
 }

 if ( ( con = SSL_new ( ctx ) ) == NULL ) goto err ;

 SSL_set_tlsext_debug_callback ( con , tlsext_cb ) ;
 SSL_set_tlsext_debug_arg ( con , bio_s_out ) ;
 }

 kssl_ctx_setstring ( kctx , KSSL_SERVICE , KRB5SVC ) ;
 kssl_ctx_setstring ( kctx , KSSL_KEYTAB , KRB5KEYTAB ) ;
 }

 sbio = BIO_new_socket ( s , BIO_NOCLOSE ) ;
 if ( s_nbio_test ) {
 BIO * test ;
 test = BIO_new ( BIO_f_nbio_test ( ) ) ;
 sbio = BIO_push ( test , sbio ) ;
 }
 SSL_set_bio ( con , sbio , sbio ) ;
 SSL_set_accept_state ( con ) ;
 BIO_set_ssl ( ssl_bio , con , BIO_CLOSE ) ;
 BIO_push ( io , ssl_bio ) ;


 SSL_set_debug ( con , 1 ) ;
 BIO_set_callback ( SSL_get_rbio ( con ) , bio_dump_callback ) ;
 BIO_set_callback_arg ( SSL_get_rbio ( con ) , ( char * ) bio_s_out ) ;
 }
 if ( s_msg ) {
 SSL_set_msg_callback ( con , msg_cb ) ;
 SSL_set_msg_callback_arg ( con , bio_s_out ) ;
 }
 for ( ;
 ;
 ) {
 if ( hack ) {
 i = SSL_accept ( con ) ;

 BIO_printf ( bio_s_out , "LOOKUP during accept %s\n" , srp_callback_parm . login ) ;
 SRP_user_pwd_free ( srp_callback_parm . user ) ;
 srp_callback_parm . user = SRP_VBASE_get1_by_user ( srp_callback_parm . vb , srp_callback_parm . login ) ;
 if ( srp_callback_parm . user ) BIO_printf ( bio_s_out , "LOOKUP done %s\n" , srp_callback_parm . user -> info ) ;
 else BIO_printf ( bio_s_out , "LOOKUP not successful\n" ) ;
 i = SSL_accept ( con ) ;
 }

 case SSL_ERROR_NONE : break ;
 case SSL_ERROR_WANT_WRITE : case SSL_ERROR_WANT_READ : case SSL_ERROR_WANT_X509_LOOKUP : continue ;
 case SSL_ERROR_SYSCALL : case SSL_ERROR_SSL : case SSL_ERROR_ZERO_RETURN : ret = 1 ;
 goto err ;
 }
 SSL_renegotiate ( con ) ;
 SSL_write ( con , NULL , 0 ) ;
 }
 i = BIO_gets ( io , buf , bufsize - 1 ) ;
 if ( i < 0 ) {
 if ( ! BIO_should_retry ( io ) ) {
 if ( ! s_quiet ) ERR_print_errors ( bio_err ) ;
 goto err ;
 }
 else {
 BIO_printf ( bio_s_out , "read R BLOCK\n" ) ;

 BIO_printf ( bio_s_out , "LOOKUP renego during read\n" ) ;
 SRP_user_pwd_free ( srp_callback_parm . user ) ;
 srp_callback_parm . user = SRP_VBASE_get1_by_user ( srp_callback_parm . vb , srp_callback_parm . login ) ;
 if ( srp_callback_parm . user ) BIO_printf ( bio_s_out , "LOOKUP done %s\n" , srp_callback_parm . user -> info ) ;
 else BIO_printf ( bio_s_out , "LOOKUP not successful\n" ) ;
 continue ;
 }



 }
 }
 else if ( i == 0 ) {
 ret = 1 ;
 goto end ;
 }
 if ( ( ( www == 1 ) && ( strncmp ( "GET " , buf , 4 ) == 0 ) ) || ( ( www == 2 ) && ( strncmp ( "GET /stats " , buf , 11 ) == 0 ) ) ) {
 char * p ;
 X509 * peer ;
 STACK_OF ( SSL_CIPHER ) * sk ;
 static const char * space = " " ;
 BIO_puts ( io , "HTTP/1.0 200 ok\r\nContent-type: text/html\r\n\r\n" ) ;
 BIO_puts ( io , "<HTML><BODY BGCOLOR=\"#ffffff\">\n" ) ;
 BIO_puts ( io , "<pre>\n" ) ;
 BIO_puts ( io , "\n" ) ;
 for ( i = 0 ;
 i < local_argc ;
 i ++ ) {
 BIO_puts ( io , local_argv [ i ] ) ;
 BIO_write ( io , " " , 1 ) ;
 }
 BIO_puts ( io , "\n" ) ;
 BIO_printf ( io , "Secure Renegotiation IS%s supported\n" , SSL_get_secure_renegotiation_support ( con ) ? "" : " NOT" ) ;
 BIO_printf ( io , "Ciphers supported in s_server binary\n" ) ;
 sk = SSL_get_ciphers ( con ) ;
 j = sk_SSL_CIPHER_num ( sk ) ;
 for ( i = 0 ;
 i < j ;
 i ++ ) {
 c = sk_SSL_CIPHER_value ( sk , i ) ;
 BIO_printf ( io , "%-11s:%-25s" , SSL_CIPHER_get_version ( c ) , SSL_CIPHER_get_name ( c ) ) ;
 if ( ( ( ( i + 1 ) % 2 ) == 0 ) && ( i + 1 != j ) ) BIO_puts ( io , "\n" ) ;
 }
 BIO_puts ( io , "\n" ) ;
 p = SSL_get_shared_ciphers ( con , buf , bufsize ) ;
 if ( p != NULL ) {
 BIO_printf ( io , "---\nCiphers common between both SSL end points:\n" ) ;
 j = i = 0 ;
 while ( * p ) {
 if ( * p == ':' ) {
 BIO_write ( io , space , 26 - j ) ;
 i ++ ;
 j = 0 ;
 BIO_write ( io , ( ( i % 3 ) ? " " : "\n" ) , 1 ) ;
 }
 else {
 BIO_write ( io , p , 1 ) ;
 j ++ ;
 }
 p ++ ;
 }
 BIO_puts ( io , "\n" ) ;
 }
 BIO_printf ( io , ( SSL_cache_hit ( con ) ? "---\nReused, " : "---\nNew, " ) ) ;
 c = SSL_get_current_cipher ( con ) ;
 BIO_printf ( io , "%s, Cipher is %s\n" , SSL_CIPHER_get_version ( c ) , SSL_CIPHER_get_name ( c ) ) ;
 SSL_SESSION_print ( io , SSL_get_session ( con ) ) ;
 BIO_printf ( io , "---\n" ) ;
 print_stats ( io , SSL_get_SSL_CTX ( con ) ) ;
 BIO_printf ( io , "---\n" ) ;
 peer = SSL_get_peer_certificate ( con ) ;
 if ( peer != NULL ) {
 BIO_printf ( io , "Client certificate\n" ) ;
 X509_print ( io , peer ) ;
 PEM_write_bio_X509 ( io , peer ) ;
 }
 else BIO_puts ( io , "no client certificate available\n" ) ;
 BIO_puts ( io , "</BODY></HTML>\r\n\r\n" ) ;
 break ;
 }
 else if ( ( www == 2 || www == 3 ) && ( strncmp ( "GET /" , buf , 5 ) == 0 ) ) {
 BIO * file ;
 char * p , * e ;
 static const char * text = "HTTP/1.0 200 ok\r\nContent-type: text/plain\r\n\r\n" ;
 p = & ( buf [ 5 ] ) ;
 dot = 1 ;
 for ( e = p ;
 * e != '\0' ;
 e ++ ) {
 if ( e [ 0 ] == ' ' ) break ;
 switch ( dot ) {
 case 1 : dot = ( e [ 0 ] == '.' ) ? 2 : 0 ;
 break ;
 case 2 : dot = ( e [ 0 ] == '.' ) ? 3 : 0 ;
 break ;
 case 3 : dot = ( e [ 0 ] == '/' ) ? - 1 : 0 ;
 break ;
 }
 if ( dot == 0 ) dot = ( e [ 0 ] == '/' ) ? 1 : 0 ;
 }
 dot = ( dot == 3 ) || ( dot == - 1 ) ;
 if ( * e == '\0' ) {
 BIO_puts ( io , text ) ;
 BIO_printf ( io , "'%s' is an invalid file name\r\n" , p ) ;
 break ;
 }
 * e = '\0' ;
 if ( dot ) {
 BIO_puts ( io , text ) ;
 BIO_printf ( io , "'%s' contains '..' reference\r\n" , p ) ;
 break ;
 }
 if ( * p == '/' ) {
 BIO_puts ( io , text ) ;
 BIO_printf ( io , "'%s' is an invalid path\r\n" , p ) ;
 break ;
 }




 BIO_printf ( io , "'%s' is a directory\r\n" , p ) ;
 break ;

 if ( ( file = BIO_new_file ( p , "r" ) ) == NULL ) {
 BIO_puts ( io , text ) ;
 BIO_printf ( io , "Error opening '%s'\r\n" , p ) ;
 ERR_print_errors ( io ) ;
 break ;
 }
 if ( ! s_quiet ) BIO_printf ( bio_err , "FILE:%s\n" , p ) ;
 if ( www == 2 ) {
 i = strlen ( p ) ;
 if ( ( ( i > 5 ) && ( strcmp ( & ( p [ i - 5 ] ) , ".html" ) == 0 ) ) || ( ( i > 4 ) && ( strcmp ( & ( p [ i - 4 ] ) , ".php" ) == 0 ) ) || ( ( i > 4 ) && ( strcmp ( & ( p [ i - 4 ] ) , ".htm" ) == 0 ) ) ) BIO_puts ( io , "HTTP/1.0 200 ok\r\nContent-type: text/html\r\n\r\n" ) ;
 else BIO_puts ( io , "HTTP/1.0 200 ok\r\nContent-type: text/plain\r\n\r\n" ) ;
 }
 for ( ;
 ;
 ) {
 i = BIO_read ( file , buf , bufsize ) ;
 if ( i <= 0 ) break ;

 fprintf ( stderr , "%d\n" , i ) ;
 if ( total_bytes > 3 * 1024 ) {
 total_bytes = 0 ;
 fprintf ( stderr , "RENEGOTIATE\n" ) ;
 SSL_renegotiate ( con ) ;
 }

 j < i ;
 ) {

 static count = 0 ;
 if ( ++ count == 13 ) {
 SSL_renegotiate ( con ) ;
 }
 }

 if ( k <= 0 ) {
 if ( ! BIO_should_retry ( io ) ) goto write_error ;
 else {
 BIO_printf ( bio_s_out , "rwrite W BLOCK\n" ) ;
 }
 }
 else {
 j += k ;
 }
 }
 }
 write_error : BIO_free ( file ) ;
 break ;
 }
 }
 for ( ;
 ;
 ) {
 i = ( int ) BIO_flush ( io ) ;
 if ( i <= 0 ) {
 if ( ! BIO_should_retry ( io ) ) break ;
 }
 else break ;
 }
 end : # if 1 SSL_set_shutdown ( con , SSL_SENT_SHUTDOWN | SSL_RECEIVED_SHUTDOWN ) ;

 if ( buf != NULL ) OPENSSL_free ( buf ) ;
 if ( io != NULL ) BIO_free_all ( io ) ;
 return ( ret ) ;
 }

 BIGNUM * bn = NULL ;
 static RSA * rsa_tmp = NULL ;
 if ( ! rsa_tmp && ( ( bn = BN_new ( ) ) == NULL ) ) BIO_printf ( bio_err , "Allocation error in generating RSA key\n" ) ;
 if ( ! rsa_tmp && bn ) {
 if ( ! s_quiet ) {
 BIO_printf ( bio_err , "Generating temp (%d bit) RSA key..." , keylength ) ;
 ( void ) BIO_flush ( bio_err ) ;
 }
 if ( ! BN_set_word ( bn , RSA_F4 ) || ( ( rsa_tmp = RSA_new ( ) ) == NULL ) || ! RSA_generate_key_ex ( rsa_tmp , keylength , bn , NULL ) ) {
 if ( rsa_tmp ) RSA_free ( rsa_tmp ) ;
 rsa_tmp = NULL ;
 }
 if ( ! s_quiet ) {
 BIO_printf ( bio_err , "\n" ) ;
 ( void ) BIO_flush ( bio_err ) ;
 }
 BN_free ( bn ) ;
 }
 return ( rsa_tmp ) ;
 }

 unsigned int count = 0 ;
 do {
 if ( RAND_pseudo_bytes ( id , * id_len ) < 0 ) return 0 ;
 memcpy ( id , session_id_prefix , ( strlen ( session_id_prefix ) < * id_len ) ? strlen ( session_id_prefix ) : * id_len ) ;
 }
 while ( SSL_has_matching_session_id ( ssl , id , * id_len ) && ( ++ count < MAX_SESSION_ID_ATTEMPTS ) ) ;
 if ( count >= MAX_SESSION_ID_ATTEMPTS ) return 0 ;
 return 1 ;
 }