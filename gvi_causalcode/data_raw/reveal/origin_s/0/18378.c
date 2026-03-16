static void acl_insert_user ( const char * user , const char * host , const char * password , uint password_len , enum SSL_type ssl_type , const char * ssl_cipher , const char * x509_issuer , const char * x509_subject , USER_RESOURCES * mqh , ulong privileges ) {
 ACL_USER acl_user ;
 safe_mutex_assert_owner ( & acl_cache -> lock ) ;
 acl_user . user = * user ? strdup_root ( & mem , user ) : 0 ;
 update_hostname ( & acl_user . host , * host ? strdup_root ( & mem , host ) : 0 ) ;
 acl_user . access = privileges ;
 acl_user . user_resource = * mqh ;
 acl_user . sort = get_sort ( 2 , acl_user . host . hostname , acl_user . user ) ;
 acl_user . hostname_length = ( uint ) strlen ( host ) ;
 acl_user . ssl_type = ( ssl_type != SSL_TYPE_NOT_SPECIFIED ? ssl_type : SSL_TYPE_NONE ) ;
 acl_user . ssl_cipher = ssl_cipher ? strdup_root ( & mem , ssl_cipher ) : 0 ;
 acl_user . x509_issuer = x509_issuer ? strdup_root ( & mem , x509_issuer ) : 0 ;
 acl_user . x509_subject = x509_subject ? strdup_root ( & mem , x509_subject ) : 0 ;
 set_user_salt ( & acl_user , password , password_len ) ;
 VOID ( push_dynamic ( & acl_users , ( uchar * ) & acl_user ) ) ;
 if ( ! acl_user . host . hostname || ( acl_user . host . hostname [ 0 ] == wild_many && ! acl_user . host . hostname [ 1 ] ) ) allow_all_hosts = 1 ;
 my_qsort ( ( uchar * ) dynamic_element ( & acl_users , 0 , ACL_USER * ) , acl_users . elements , sizeof ( ACL_USER ) , ( qsort_cmp ) acl_compare ) ;
 rebuild_check_host ( ) ;
 }