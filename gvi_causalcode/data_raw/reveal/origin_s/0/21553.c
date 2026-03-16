static Expr * simplify_function ( Oid funcid , Oid result_type , int32 result_typmod , Oid result_collid , Oid input_collid , List * * args_p , bool funcvariadic , bool process_args , bool allow_non_const , eval_const_expressions_context * context ) {
 List * args = * args_p ;
 HeapTuple func_tuple ;
 Form_pg_proc func_form ;
 Expr * newexpr ;
 func_tuple = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( ! HeapTupleIsValid ( func_tuple ) ) elog ( ERROR , "cache lookup failed for function %u" , funcid ) ;
 func_form = ( Form_pg_proc ) GETSTRUCT ( func_tuple ) ;
 if ( process_args ) {
 args = expand_function_arguments ( args , result_type , func_tuple ) ;
 args = ( List * ) expression_tree_mutator ( ( Node * ) args , eval_const_expressions_mutator , ( void * ) context ) ;
 * args_p = args ;
 }
 newexpr = evaluate_function ( funcid , result_type , result_typmod , result_collid , input_collid , args , funcvariadic , func_tuple , context ) ;
 if ( ! newexpr && allow_non_const && OidIsValid ( func_form -> protransform ) ) {
 FuncExpr fexpr ;
 fexpr . xpr . type = T_FuncExpr ;
 fexpr . funcid = funcid ;
 fexpr . funcresulttype = result_type ;
 fexpr . funcretset = func_form -> proretset ;
 fexpr . funcvariadic = funcvariadic ;
 fexpr . funcformat = COERCE_EXPLICIT_CALL ;
 fexpr . funccollid = result_collid ;
 fexpr . inputcollid = input_collid ;
 fexpr . args = args ;
 fexpr . location = - 1 ;
 newexpr = ( Expr * ) DatumGetPointer ( OidFunctionCall1 ( func_form -> protransform , PointerGetDatum ( & fexpr ) ) ) ;
 }
 if ( ! newexpr && allow_non_const ) newexpr = inline_function ( funcid , result_type , result_collid , input_collid , args , funcvariadic , func_tuple , context ) ;
 ReleaseSysCache ( func_tuple ) ;
 return newexpr ;
 }