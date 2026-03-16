bool sp_grant_privileges ( THD * thd , const char * sp_db , const char * sp_name , bool is_proc ) {
 Security_context * sctx = thd -> security_ctx ;
 LEX_USER * combo ;
 TABLE_LIST tables [ 1 ] ;
 List < LEX_USER > user_list ;
 bool result ;
 ACL_USER * au ;
 char passwd_buff [ SCRAMBLED_PASSWORD_CHAR_LENGTH + 1 ] ;
 Dummy_error_handler error_handler ;
 DBUG_ENTER ( "sp_grant_privileges" ) ;
 if ( ! ( combo = ( LEX_USER * ) thd -> alloc ( sizeof ( st_lex_user ) ) ) ) DBUG_RETURN ( TRUE ) ;
 combo -> user . str = sctx -> user ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 if ( ( au = find_acl_user ( combo -> host . str = ( char * ) sctx -> host_or_ip , combo -> user . str , FALSE ) ) ) goto found_acl ;
 if ( ( au = find_acl_user ( combo -> host . str = ( char * ) sctx -> host , combo -> user . str , FALSE ) ) ) goto found_acl ;
 if ( ( au = find_acl_user ( combo -> host . str = ( char * ) sctx -> ip , combo -> user . str , FALSE ) ) ) goto found_acl ;
 if ( ( au = find_acl_user ( combo -> host . str = ( char * ) "%" , combo -> user . str , FALSE ) ) ) goto found_acl ;
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 DBUG_RETURN ( TRUE ) ;
 found_acl : VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 bzero ( ( char * ) tables , sizeof ( TABLE_LIST ) ) ;
 user_list . empty ( ) ;
 tables -> db = ( char * ) sp_db ;
 tables -> table_name = tables -> alias = ( char * ) sp_name ;
 combo -> host . length = strlen ( combo -> host . str ) ;
 combo -> user . length = strlen ( combo -> user . str ) ;
 combo -> host . str = thd -> strmake ( combo -> host . str , combo -> host . length ) ;
 combo -> user . str = thd -> strmake ( combo -> user . str , combo -> user . length ) ;
 if ( au && au -> salt_len ) {
 if ( au -> salt_len == SCRAMBLE_LENGTH ) {
 make_password_from_salt ( passwd_buff , au -> salt ) ;
 combo -> password . length = SCRAMBLED_PASSWORD_CHAR_LENGTH ;
 }
 else if ( au -> salt_len == SCRAMBLE_LENGTH_323 ) {
 make_password_from_salt_323 ( passwd_buff , ( ulong * ) au -> salt ) ;
 combo -> password . length = SCRAMBLED_PASSWORD_CHAR_LENGTH_323 ;
 }
 else {
 push_warning_printf ( thd , MYSQL_ERROR : : WARN_LEVEL_WARN , ER_PASSWD_LENGTH , ER ( ER_PASSWD_LENGTH ) , SCRAMBLED_PASSWORD_CHAR_LENGTH ) ;
 return TRUE ;
 }
 combo -> password . str = passwd_buff ;
 }
 else {
 combo -> password . str = ( char * ) "" ;
 combo -> password . length = 0 ;
 }
 if ( user_list . push_back ( combo ) ) DBUG_RETURN ( TRUE ) ;
 thd -> lex -> ssl_type = SSL_TYPE_NOT_SPECIFIED ;
 thd -> lex -> ssl_cipher = thd -> lex -> x509_subject = thd -> lex -> x509_issuer = 0 ;
 bzero ( ( char * ) & thd -> lex -> mqh , sizeof ( thd -> lex -> mqh ) ) ;
 thd -> push_internal_handler ( & error_handler ) ;
 result = mysql_routine_grant ( thd , tables , is_proc , user_list , DEFAULT_CREATE_PROC_ACLS , FALSE , FALSE ) ;
 thd -> pop_internal_handler ( ) ;
 DBUG_RETURN ( result ) ;
 }