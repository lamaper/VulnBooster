static int cert_retrieve_fn ( gnutls_session_t session , const gnutls_datum_t * req_ca_rdn __attribute__ ( ( unused ) ) , int nreqs __attribute__ ( ( unused ) ) , const gnutls_pk_algorithm_t * pk_algos __attribute__ ( ( unused ) ) , int pk_algos_length __attribute__ ( ( unused ) ) , gnutls_retr2_st * ret ) {
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 mgs_handle_t * ctxt ;
 if ( session == NULL ) {
 ret -> ncerts = 0 ;
 ret -> deinit_all = 1 ;
 return - 1 ;
 }
 ctxt = gnutls_transport_get_ptr ( session ) ;
 if ( gnutls_certificate_type_get ( session ) == GNUTLS_CRT_X509 ) {
 ret -> cert_type = GNUTLS_CRT_X509 ;
 ret -> key_type = GNUTLS_PRIVKEY_X509 ;
 ret -> ncerts = ctxt -> sc -> certs_x509_chain_num ;
 ret -> deinit_all = 0 ;
 ret -> cert . x509 = ctxt -> sc -> certs_x509_chain ;
 ret -> key . x509 = ctxt -> sc -> privkey_x509 ;
 return 0 ;
 }
 else if ( gnutls_certificate_type_get ( session ) == GNUTLS_CRT_OPENPGP ) {
 ret -> cert_type = GNUTLS_CRT_OPENPGP ;
 ret -> key_type = GNUTLS_PRIVKEY_OPENPGP ;
 ret -> ncerts = 1 ;
 ret -> deinit_all = 0 ;
 ret -> cert . pgp = ctxt -> sc -> cert_pgp ;
 ret -> key . pgp = ctxt -> sc -> privkey_pgp ;
 return 0 ;
 }
 else {
 ret -> ncerts = 0 ;
 ret -> deinit_all = 1 ;
 return - 1 ;
 }
 }