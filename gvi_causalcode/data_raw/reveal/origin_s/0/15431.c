int acl_getroot ( THD * thd , USER_RESOURCES * mqh , const char * passwd , uint passwd_len ) {
 ulong user_access = NO_ACCESS ;
 int res = 1 ;
 ACL_USER * acl_user = 0 ;
 Security_context * sctx = thd -> security_ctx ;
 DBUG_ENTER ( "acl_getroot" ) ;
 if ( ! initialized ) {
 sctx -> skip_grants ( ) ;
 bzero ( ( char * ) mqh , sizeof ( * mqh ) ) ;
 DBUG_RETURN ( 0 ) ;
 }
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 for ( uint i = 0 ;
 i < acl_users . elements ;
 i ++ ) {
 ACL_USER * acl_user_tmp = dynamic_element ( & acl_users , i , ACL_USER * ) ;
 if ( ! acl_user_tmp -> user || ! strcmp ( sctx -> user , acl_user_tmp -> user ) ) {
 if ( compare_hostname ( & acl_user_tmp -> host , sctx -> host , sctx -> ip ) ) {
 if ( passwd_len == acl_user_tmp -> salt_len ) {
 if ( acl_user_tmp -> salt_len == 0 || ( acl_user_tmp -> salt_len == SCRAMBLE_LENGTH ? check_scramble ( passwd , thd -> scramble , acl_user_tmp -> salt ) : check_scramble_323 ( passwd , thd -> scramble , ( ulong * ) acl_user_tmp -> salt ) ) == 0 ) {
 acl_user = acl_user_tmp ;
 res = 0 ;
 }
 }
 else if ( passwd_len == SCRAMBLE_LENGTH && acl_user_tmp -> salt_len == SCRAMBLE_LENGTH_323 ) res = - 1 ;
 else if ( passwd_len == SCRAMBLE_LENGTH_323 && acl_user_tmp -> salt_len == SCRAMBLE_LENGTH ) res = 2 ;
 break ;
 }
 }
 }
 if ( acl_user ) {

 SSL * ssl = ( SSL * ) vio -> ssl_arg ;
 X509 * cert ;

 case SSL_TYPE_NOT_SPECIFIED : case SSL_TYPE_NONE : user_access = acl_user -> access ;
 break ;

 break ;
 case SSL_TYPE_X509 : if ( vio_type ( vio ) == VIO_TYPE_SSL && SSL_get_verify_result ( ssl ) == X509_V_OK && ( cert = SSL_get_peer_certificate ( ssl ) ) ) {
 user_access = acl_user -> access ;
 X509_free ( cert ) ;
 }
 break ;
 case SSL_TYPE_SPECIFIED : if ( vio_type ( vio ) != VIO_TYPE_SSL || SSL_get_verify_result ( ssl ) != X509_V_OK ) break ;
 if ( acl_user -> ssl_cipher ) {
 DBUG_PRINT ( "info" , ( "comparing ciphers: '%s' and '%s'" , acl_user -> ssl_cipher , SSL_get_cipher ( ssl ) ) ) ;
 if ( ! strcmp ( acl_user -> ssl_cipher , SSL_get_cipher ( ssl ) ) ) user_access = acl_user -> access ;
 else {
 if ( global_system_variables . log_warnings ) sql_print_information ( "X509 ciphers mismatch: should be '%s' but is '%s'" , acl_user -> ssl_cipher , SSL_get_cipher ( ssl ) ) ;
 break ;
 }
 }
 DBUG_PRINT ( "info" , ( "checkpoint 1" ) ) ;
 if ( ! ( cert = SSL_get_peer_certificate ( ssl ) ) ) {
 user_access = NO_ACCESS ;
 break ;
 }
 DBUG_PRINT ( "info" , ( "checkpoint 2" ) ) ;
 if ( acl_user -> x509_issuer ) {
 DBUG_PRINT ( "info" , ( "checkpoint 3" ) ) ;
 char * ptr = X509_NAME_oneline ( X509_get_issuer_name ( cert ) , 0 , 0 ) ;
 DBUG_PRINT ( "info" , ( "comparing issuers: '%s' and '%s'" , acl_user -> x509_issuer , ptr ) ) ;
 if ( strcmp ( acl_user -> x509_issuer , ptr ) ) {
 if ( global_system_variables . log_warnings ) sql_print_information ( "X509 issuer mismatch: should be '%s' " "but is '%s'" , acl_user -> x509_issuer , ptr ) ;
 free ( ptr ) ;
 X509_free ( cert ) ;
 user_access = NO_ACCESS ;
 break ;
 }
 user_access = acl_user -> access ;
 free ( ptr ) ;
 }
 DBUG_PRINT ( "info" , ( "checkpoint 4" ) ) ;
 if ( acl_user -> x509_subject ) {
 char * ptr = X509_NAME_oneline ( X509_get_subject_name ( cert ) , 0 , 0 ) ;
 DBUG_PRINT ( "info" , ( "comparing subjects: '%s' and '%s'" , acl_user -> x509_subject , ptr ) ) ;
 if ( strcmp ( acl_user -> x509_subject , ptr ) ) {
 if ( global_system_variables . log_warnings ) sql_print_information ( "X509 subject mismatch: should be '%s' but is '%s'" , acl_user -> x509_subject , ptr ) ;
 free ( ptr ) ;
 X509_free ( cert ) ;
 user_access = NO_ACCESS ;
 break ;
 }
 user_access = acl_user -> access ;
 free ( ptr ) ;
 }
 X509_free ( cert ) ;
 break ;


 sctx -> master_access = user_access ;
 sctx -> priv_user = acl_user -> user ? sctx -> user : ( char * ) "" ;
 * mqh = acl_user -> user_resource ;
 if ( acl_user -> host . hostname ) strmake ( sctx -> priv_host , acl_user -> host . hostname , MAX_HOSTNAME - 1 ) ;
 else * sctx -> priv_host = 0 ;
 }
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 DBUG_RETURN ( res ) ;
 }