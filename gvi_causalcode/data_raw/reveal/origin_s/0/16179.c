static bool test_if_create_new_users ( THD * thd ) {
 Security_context * sctx = thd -> security_ctx ;
 bool create_new_users = test ( sctx -> master_access & INSERT_ACL ) || ( ! opt_safe_user_create && test ( sctx -> master_access & CREATE_USER_ACL ) ) ;
 if ( ! create_new_users ) {
 TABLE_LIST tl ;
 ulong db_access ;
 bzero ( ( char * ) & tl , sizeof ( tl ) ) ;
 tl . db = ( char * ) "mysql" ;
 tl . table_name = ( char * ) "user" ;
 create_new_users = 1 ;
 db_access = acl_get ( sctx -> host , sctx -> ip , sctx -> priv_user , tl . db , 0 ) ;
 if ( ! ( db_access & INSERT_ACL ) ) {
 if ( check_grant ( thd , INSERT_ACL , & tl , 0 , UINT_MAX , 1 ) ) create_new_users = 0 ;
 }
 }
 return create_new_users ;
 }