bool check_grant ( THD * thd , ulong want_access , TABLE_LIST * tables , uint show_table , uint number , bool no_errors ) {
 TABLE_LIST * table , * first_not_own_table = thd -> lex -> first_not_own_table ( ) ;
 Security_context * sctx = thd -> security_ctx ;
 uint i ;
 ulong orig_want_access = want_access ;
 DBUG_ENTER ( "check_grant" ) ;
 DBUG_ASSERT ( number > 0 ) ;
 for ( i = 0 , table = tables ;
 i < number && table != first_not_own_table ;
 table = table -> next_global , i ++ ) {
 table -> grant . orig_want_privilege = ( want_access & ~ SHOW_VIEW_ACL ) ;
 }
 rw_rdlock ( & LOCK_grant ) ;
 for ( table = tables ;
 table && number -- && table != first_not_own_table ;
 table = table -> next_global ) {
 GRANT_TABLE * grant_table ;
 sctx = test ( table -> security_ctx ) ? table -> security_ctx : thd -> security_ctx ;
 want_access = orig_want_access ;
 want_access &= ~ sctx -> master_access ;
 if ( ! want_access ) continue ;
 if ( ! ( ~ table -> grant . privilege & want_access ) || table -> is_anonymous_derived_table ( ) || table -> schema_table ) {
 if ( ! table -> referencing_view ) {
 table -> grant . want_privilege = 0 ;
 }
 continue ;
 }
 if ( ! ( grant_table = table_hash_search ( sctx -> host , sctx -> ip , table -> get_db_name ( ) , sctx -> priv_user , table -> get_table_name ( ) , FALSE ) ) ) {
 want_access &= ~ table -> grant . privilege ;
 goto err ;
 }
 if ( show_table ) continue ;
 table -> grant . grant_table = grant_table ;
 table -> grant . version = grant_version ;
 table -> grant . privilege |= grant_table -> privs ;
 table -> grant . want_privilege = ( ( want_access & COL_ACLS ) & ~ table -> grant . privilege ) ;
 if ( ! ( ~ table -> grant . privilege & want_access ) ) continue ;
 if ( want_access & ~ ( grant_table -> cols | table -> grant . privilege ) ) {
 want_access &= ~ ( grant_table -> cols | table -> grant . privilege ) ;
 goto err ;
 }
 }
 rw_unlock ( & LOCK_grant ) ;
 DBUG_RETURN ( 0 ) ;
 err : rw_unlock ( & LOCK_grant ) ;
 if ( ! no_errors ) {
 char command [ 128 ] ;
 get_privilege_desc ( command , sizeof ( command ) , want_access ) ;
 my_error ( ER_TABLEACCESS_DENIED_ERROR , MYF ( 0 ) , command , sctx -> priv_user , sctx -> host_or_ip , table ? table -> get_table_name ( ) : "unknown" ) ;
 }
 DBUG_RETURN ( 1 ) ;
 }