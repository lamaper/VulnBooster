static int read_crt_cn ( server_rec * s , apr_pool_t * p , gnutls_x509_crt_t cert , char * * cert_cn ) {
 int rv = 0 , i ;
 size_t data_len ;
 _gnutls_log ( debug_log_fp , "%s: %d\n" , __func__ , __LINE__ ) ;
 * cert_cn = NULL ;
 data_len = 0 ;
 rv = gnutls_x509_crt_get_dn_by_oid ( cert , GNUTLS_OID_X520_COMMON_NAME , 0 , 0 , NULL , & data_len ) ;
 if ( rv == GNUTLS_E_SHORT_MEMORY_BUFFER && data_len > 1 ) {
 * cert_cn = apr_palloc ( p , data_len ) ;
 rv = gnutls_x509_crt_get_dn_by_oid ( cert , GNUTLS_OID_X520_COMMON_NAME , 0 , 0 , * cert_cn , & data_len ) ;
 }
 else {
 ap_log_error ( APLOG_MARK , APLOG_DEBUG , 0 , s , "No common name found in certificate for '%s:%d'. Looking for subject alternative name..." , s -> server_hostname , s -> port ) ;
 rv = 0 ;
 for ( i = 0 ;
 ! ( rv < 0 ) ;
 i ++ ) {
 data_len = 0 ;
 rv = gnutls_x509_crt_get_subject_alt_name ( cert , i , NULL , & data_len , NULL ) ;
 if ( rv == GNUTLS_E_SHORT_MEMORY_BUFFER && data_len > 1 ) {
 * cert_cn = apr_palloc ( p , data_len + 1 ) ;
 rv = gnutls_x509_crt_get_subject_alt_name ( cert , i , * cert_cn , & data_len , NULL ) ;
 ( * cert_cn ) [ data_len ] = 0 ;
 if ( rv == GNUTLS_SAN_DNSNAME ) break ;
 }
 }
 }
 return rv ;
 }