static int read_pgpcrt_cn ( server_rec * s , apr_pool_t * p , gnutls_openpgp_crt_t cert , char * * cert_cn ) {
 int rv = 0 ;
 size_t data_len ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 * cert_cn = NULL ;
 data_len = 0 ;
 rv = gnutls_openpgp_crt_get_name ( cert , 0 , NULL , & data_len ) ;
 if ( rv == GNUTLS_E_SHORT_MEMORY_BUFFER && data_len > 1 ) {
 * cert_cn = apr_palloc ( p , data_len ) ;
 rv = gnutls_openpgp_crt_get_name ( cert , 0 , * cert_cn , & data_len ) ;
 }
 else {
 ap_log_error ( APLOG_MARK , APLOG_INFO , 0 , s , "No name found in PGP certificate for '%s:%d'." , s -> server_hostname , s -> port ) ;
 }
 return rv ;
 }