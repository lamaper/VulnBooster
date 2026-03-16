MSG_PROCESS_RETURN tls_process_cert_verify ( SSL * s , PACKET * pkt ) {
 EVP_PKEY * pkey = NULL ;
 const unsigned char * sig , * data ;


 int type = 0 , j ;
 unsigned int len ;
 X509 * peer ;
 const EVP_MD * md = NULL ;
 long hdatalen = 0 ;
 void * hdata ;
 EVP_MD_CTX * mctx = EVP_MD_CTX_new ( ) ;
 if ( mctx == NULL ) {
 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , ERR_R_MALLOC_FAILURE ) ;
 al = SSL_AD_INTERNAL_ERROR ;
 goto f_err ;
 }
 peer = s -> session -> peer ;
 pkey = X509_get0_pubkey ( peer ) ;
 type = X509_certificate_type ( peer , pkey ) ;
 if ( ! ( type & EVP_PKT_SIGN ) ) {
 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , SSL_R_SIGNATURE_FOR_NON_SIGNING_CERTIFICATE ) ;
 al = SSL_AD_ILLEGAL_PARAMETER ;
 goto f_err ;
 }

 len = 64 ;
 }
 else # endif {
 if ( SSL_USE_SIGALGS ( s ) ) {
 int rv ;
 if ( ! PACKET_get_bytes ( pkt , & sig , 2 ) ) {
 al = SSL_AD_DECODE_ERROR ;
 goto f_err ;
 }
 rv = tls12_check_peer_sigalg ( & md , s , sig , pkey ) ;
 if ( rv == - 1 ) {
 al = SSL_AD_INTERNAL_ERROR ;
 goto f_err ;
 }
 else if ( rv == 0 ) {
 al = SSL_AD_DECODE_ERROR ;
 goto f_err ;
 }


 else {
 int idx = ssl_cert_type ( NULL , pkey ) ;
 if ( idx >= 0 ) md = s -> s3 -> tmp . md [ idx ] ;
 if ( md == NULL ) {
 al = SSL_AD_INTERNAL_ERROR ;
 goto f_err ;
 }
 }
 if ( ! PACKET_get_net_2 ( pkt , & len ) ) {
 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , SSL_R_LENGTH_MISMATCH ) ;
 al = SSL_AD_DECODE_ERROR ;
 goto f_err ;
 }
 }
 j = EVP_PKEY_size ( pkey ) ;
 if ( ( ( int ) len > j ) || ( ( int ) PACKET_remaining ( pkt ) > j ) || ( PACKET_remaining ( pkt ) == 0 ) ) {
 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , SSL_R_WRONG_SIGNATURE_SIZE ) ;
 al = SSL_AD_DECODE_ERROR ;
 goto f_err ;
 }
 if ( ! PACKET_get_bytes ( pkt , & data , len ) ) {
 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , SSL_R_LENGTH_MISMATCH ) ;
 al = SSL_AD_DECODE_ERROR ;
 goto f_err ;
 }
 hdatalen = BIO_get_mem_data ( s -> s3 -> handshake_buffer , & hdata ) ;
 if ( hdatalen <= 0 ) {
 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , ERR_R_INTERNAL_ERROR ) ;
 al = SSL_AD_INTERNAL_ERROR ;
 goto f_err ;
 }


 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , ERR_R_EVP_LIB ) ;
 al = SSL_AD_INTERNAL_ERROR ;
 goto f_err ;
 }

 int pktype = EVP_PKEY_id ( pkey ) ;
 if ( pktype == NID_id_GostR3410_2001 || pktype == NID_id_GostR3410_2012_256 || pktype == NID_id_GostR3410_2012_512 ) {
 if ( ( gost_data = OPENSSL_malloc ( len ) ) == NULL ) {
 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , ERR_R_MALLOC_FAILURE ) ;
 al = SSL_AD_INTERNAL_ERROR ;
 goto f_err ;
 }
 BUF_reverse ( gost_data , data , len ) ;
 data = gost_data ;
 }
 }

 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , ERR_R_EVP_LIB ) ;
 al = SSL_AD_INTERNAL_ERROR ;
 goto f_err ;
 }
 if ( EVP_VerifyFinal ( mctx , data , len , pkey ) <= 0 ) {
 al = SSL_AD_DECRYPT_ERROR ;
 SSLerr ( SSL_F_TLS_PROCESS_CERT_VERIFY , SSL_R_BAD_SIGNATURE ) ;
 goto f_err ;
 }
 ret = MSG_PROCESS_CONTINUE_PROCESSING ;
 if ( 0 ) {
 f_err : ssl3_send_alert ( s , SSL3_AL_FATAL , al ) ;
 ossl_statem_set_error ( s ) ;
 }
 BIO_free ( s -> s3 -> handshake_buffer ) ;
 s -> s3 -> handshake_buffer = NULL ;
 EVP_MD_CTX_free ( mctx ) ;


 }