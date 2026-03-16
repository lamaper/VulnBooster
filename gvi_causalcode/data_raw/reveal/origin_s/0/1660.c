static Datum ExecEvalArrayCoerceExpr ( ArrayCoerceExprState * astate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 ArrayCoerceExpr * acoerce = ( ArrayCoerceExpr * ) astate -> xprstate . expr ;
 Datum result ;
 FunctionCallInfoData locfcinfo ;
 result = ExecEvalExpr ( astate -> arg , econtext , isNull , isDone ) ;
 if ( isDone && * isDone == ExprEndResult ) return result ;
 if ( * isNull ) return result ;
 if ( ! OidIsValid ( acoerce -> elemfuncid ) ) {
 ArrayType * array = DatumGetArrayTypePCopy ( result ) ;
 ARR_ELEMTYPE ( array ) = astate -> resultelemtype ;
 PG_RETURN_ARRAYTYPE_P ( array ) ;
 }
 if ( astate -> elemfunc . fn_oid == InvalidOid ) {
 AclResult aclresult ;
 aclresult = pg_proc_aclcheck ( acoerce -> elemfuncid , GetUserId ( ) , ACL_EXECUTE ) ;
 if ( aclresult != ACLCHECK_OK ) aclcheck_error ( aclresult , ACL_KIND_PROC , get_func_name ( acoerce -> elemfuncid ) ) ;
 InvokeFunctionExecuteHook ( acoerce -> elemfuncid ) ;
 fmgr_info_cxt ( acoerce -> elemfuncid , & ( astate -> elemfunc ) , econtext -> ecxt_per_query_memory ) ;
 fmgr_info_set_expr ( ( Node * ) acoerce , & ( astate -> elemfunc ) ) ;
 }
 InitFunctionCallInfoData ( locfcinfo , & ( astate -> elemfunc ) , 3 , InvalidOid , NULL , NULL ) ;
 locfcinfo . arg [ 0 ] = result ;
 locfcinfo . arg [ 1 ] = Int32GetDatum ( acoerce -> resulttypmod ) ;
 locfcinfo . arg [ 2 ] = BoolGetDatum ( acoerce -> isExplicit ) ;
 locfcinfo . argnull [ 0 ] = false ;
 locfcinfo . argnull [ 1 ] = false ;
 locfcinfo . argnull [ 2 ] = false ;
 return array_map ( & locfcinfo , astate -> resultelemtype , astate -> amstate ) ;
 }