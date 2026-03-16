static void init_fcache ( Oid foid , Oid input_collation , FuncExprState * fcache , MemoryContext fcacheCxt , bool needDescForSets ) {
 AclResult aclresult ;
 aclresult = pg_proc_aclcheck ( foid , GetUserId ( ) , ACL_EXECUTE ) ;
 if ( aclresult != ACLCHECK_OK ) aclcheck_error ( aclresult , ACL_KIND_PROC , get_func_name ( foid ) ) ;
 InvokeFunctionExecuteHook ( foid ) ;
 if ( list_length ( fcache -> args ) > FUNC_MAX_ARGS ) ereport ( ERROR , ( errcode ( ERRCODE_TOO_MANY_ARGUMENTS ) , errmsg_plural ( "cannot pass more than %d argument to a function" , "cannot pass more than %d arguments to a function" , FUNC_MAX_ARGS , FUNC_MAX_ARGS ) ) ) ;
 fmgr_info_cxt ( foid , & ( fcache -> func ) , fcacheCxt ) ;
 fmgr_info_set_expr ( ( Node * ) fcache -> xprstate . expr , & ( fcache -> func ) ) ;
 InitFunctionCallInfoData ( fcache -> fcinfo_data , & ( fcache -> func ) , list_length ( fcache -> args ) , input_collation , NULL , NULL ) ;
 if ( fcache -> func . fn_retset && needDescForSets ) {
 TypeFuncClass functypclass ;
 Oid funcrettype ;
 TupleDesc tupdesc ;
 MemoryContext oldcontext ;
 functypclass = get_expr_result_type ( fcache -> func . fn_expr , & funcrettype , & tupdesc ) ;
 oldcontext = MemoryContextSwitchTo ( fcacheCxt ) ;
 if ( functypclass == TYPEFUNC_COMPOSITE ) {
 Assert ( tupdesc ) ;
 fcache -> funcResultDesc = CreateTupleDescCopy ( tupdesc ) ;
 fcache -> funcReturnsTuple = true ;
 }
 else if ( functypclass == TYPEFUNC_SCALAR ) {
 tupdesc = CreateTemplateTupleDesc ( 1 , false ) ;
 TupleDescInitEntry ( tupdesc , ( AttrNumber ) 1 , NULL , funcrettype , - 1 , 0 ) ;
 fcache -> funcResultDesc = tupdesc ;
 fcache -> funcReturnsTuple = false ;
 }
 else if ( functypclass == TYPEFUNC_RECORD ) {
 fcache -> funcResultDesc = NULL ;
 fcache -> funcReturnsTuple = true ;
 }
 else {
 fcache -> funcResultDesc = NULL ;
 }
 MemoryContextSwitchTo ( oldcontext ) ;
 }
 else fcache -> funcResultDesc = NULL ;
 fcache -> funcResultStore = NULL ;
 fcache -> funcResultSlot = NULL ;
 fcache -> setArgsValid = false ;
 fcache -> shutdown_reg = false ;
 }