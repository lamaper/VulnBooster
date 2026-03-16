bool check_grant_routine ( THD * thd , ulong want_access , TABLE_LIST * procs , bool is_proc , bool no_errors ) {
 TABLE_LIST * table ;
 Security_context * sctx = thd -> security_ctx ;
 char * user = sctx -> priv_user ;
 char * host = sctx -> priv_host ;
 DBUG_ENTER ( "check_grant_routine" ) ;
 want_access &= ~ sctx -> master_access ;
 if ( ! want_access ) DBUG_RETURN ( 0 ) ;
 rw_rdlock ( & LOCK_grant ) ;
 for ( table = procs ;
 table ;
 table = table -> next_global ) {
 GRANT_NAME * grant_proc ;
 if ( ( grant_proc = routine_hash_search ( host , sctx -> ip , table -> db , user , table -> table_name , is_proc , 0 ) ) ) table -> grant . privilege |= grant_proc -> privs ;
 if ( want_access & ~ table -> grant . privilege ) {
 want_access &= ~ table -> grant . privilege ;
 goto err ;
 }
 }
 rw_unlock ( & LOCK_grant ) ;
 DBUG_RETURN ( 0 ) ;
 err : rw_unlock ( & LOCK_grant ) ;
 if ( ! no_errors ) {
 char buff [ 1024 ] ;
 const char * command = "" ;
 if ( table ) strxmov ( buff , table -> db , "." , table -> table_name , NullS ) ;
 if ( want_access & EXECUTE_ACL ) command = "execute" ;
 else if ( want_access & ALTER_PROC_ACL ) command = "alter routine" ;
 else if ( want_access & GRANT_ACL ) command = "grant" ;
 my_error ( ER_PROCACCESS_DENIED_ERROR , MYF ( 0 ) , command , user , host , table ? buff : "unknown" ) ;
 }
 DBUG_RETURN ( 1 ) ;
 }