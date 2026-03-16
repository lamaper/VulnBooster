static Expr * inline_function ( Oid funcid , Oid result_type , Oid result_collid , Oid input_collid , List * args , bool funcvariadic , HeapTuple func_tuple , eval_const_expressions_context * context ) {
 Form_pg_proc funcform = ( Form_pg_proc ) GETSTRUCT ( func_tuple ) ;
 char * src ;
 Datum tmp ;
 bool isNull ;
 bool modifyTargetList ;
 MemoryContext oldcxt ;
 MemoryContext mycxt ;
 inline_error_callback_arg callback_arg ;
 ErrorContextCallback sqlerrcontext ;
 FuncExpr * fexpr ;
 SQLFunctionParseInfoPtr pinfo ;
 ParseState * pstate ;
 List * raw_parsetree_list ;
 Query * querytree ;
 Node * newexpr ;
 int * usecounts ;
 ListCell * arg ;
 int i ;
 if ( funcform -> prolang != SQLlanguageId || funcform -> prosecdef || funcform -> proretset || funcform -> prorettype == RECORDOID || ! heap_attisnull ( func_tuple , Anum_pg_proc_proconfig ) || funcform -> pronargs != list_length ( args ) ) return NULL ;
 if ( list_member_oid ( context -> active_fns , funcid ) ) return NULL ;
 if ( pg_proc_aclcheck ( funcid , GetUserId ( ) , ACL_EXECUTE ) != ACLCHECK_OK ) return NULL ;
 if ( FmgrHookIsNeeded ( funcid ) ) return NULL ;
 mycxt = AllocSetContextCreate ( CurrentMemoryContext , "inline_function" , ALLOCSET_DEFAULT_MINSIZE , ALLOCSET_DEFAULT_INITSIZE , ALLOCSET_DEFAULT_MAXSIZE ) ;
 oldcxt = MemoryContextSwitchTo ( mycxt ) ;
 tmp = SysCacheGetAttr ( PROCOID , func_tuple , Anum_pg_proc_prosrc , & isNull ) ;
 if ( isNull ) elog ( ERROR , "null prosrc for function %u" , funcid ) ;
 src = TextDatumGetCString ( tmp ) ;
 callback_arg . proname = NameStr ( funcform -> proname ) ;
 callback_arg . prosrc = src ;
 sqlerrcontext . callback = sql_inline_error_callback ;
 sqlerrcontext . arg = ( void * ) & callback_arg ;
 sqlerrcontext . previous = error_context_stack ;
 error_context_stack = & sqlerrcontext ;
 fexpr = makeNode ( FuncExpr ) ;
 fexpr -> funcid = funcid ;
 fexpr -> funcresulttype = result_type ;
 fexpr -> funcretset = false ;
 fexpr -> funcvariadic = funcvariadic ;
 fexpr -> funcformat = COERCE_EXPLICIT_CALL ;
 fexpr -> funccollid = result_collid ;
 fexpr -> inputcollid = input_collid ;
 fexpr -> args = args ;
 fexpr -> location = - 1 ;
 pinfo = prepare_sql_fn_parse_info ( func_tuple , ( Node * ) fexpr , input_collid ) ;
 raw_parsetree_list = pg_parse_query ( src ) ;
 if ( list_length ( raw_parsetree_list ) != 1 ) goto fail ;
 pstate = make_parsestate ( NULL ) ;
 pstate -> p_sourcetext = src ;
 sql_fn_parser_setup ( pstate , pinfo ) ;
 querytree = transformTopLevelStmt ( pstate , linitial ( raw_parsetree_list ) ) ;
 free_parsestate ( pstate ) ;
 if ( ! IsA ( querytree , Query ) || querytree -> commandType != CMD_SELECT || querytree -> utilityStmt || querytree -> hasAggs || querytree -> hasWindowFuncs || querytree -> hasSubLinks || querytree -> cteList || querytree -> rtable || querytree -> jointree -> fromlist || querytree -> jointree -> quals || querytree -> groupClause || querytree -> groupingSets || querytree -> havingQual || querytree -> windowClause || querytree -> distinctClause || querytree -> sortClause || querytree -> limitOffset || querytree -> limitCount || querytree -> setOperations || list_length ( querytree -> targetList ) != 1 ) goto fail ;
 if ( check_sql_fn_retval ( funcid , result_type , list_make1 ( querytree ) , & modifyTargetList , NULL ) ) goto fail ;
 newexpr = ( Node * ) ( ( TargetEntry * ) linitial ( querytree -> targetList ) ) -> expr ;
 Assert ( exprType ( newexpr ) == result_type ) ;
 Assert ( ! modifyTargetList ) ;
 if ( expression_returns_set ( newexpr ) ) goto fail ;
 if ( funcform -> provolatile == PROVOLATILE_IMMUTABLE && contain_mutable_functions ( newexpr ) ) goto fail ;
 else if ( funcform -> provolatile == PROVOLATILE_STABLE && contain_volatile_functions ( newexpr ) ) goto fail ;
 if ( funcform -> proisstrict && contain_nonstrict_functions ( newexpr ) ) goto fail ;
 if ( contain_context_dependent_node ( ( Node * ) args ) ) goto fail ;
 usecounts = ( int * ) palloc0 ( funcform -> pronargs * sizeof ( int ) ) ;
 newexpr = substitute_actual_parameters ( newexpr , funcform -> pronargs , args , usecounts ) ;
 i = 0 ;
 foreach ( arg , args ) {
 Node * param = lfirst ( arg ) ;
 if ( usecounts [ i ] == 0 ) {
 if ( funcform -> proisstrict ) goto fail ;
 }
 else if ( usecounts [ i ] != 1 ) {
 QualCost eval_cost ;
 if ( contain_subplans ( param ) ) goto fail ;
 cost_qual_eval ( & eval_cost , list_make1 ( param ) , NULL ) ;
 if ( eval_cost . startup + eval_cost . per_tuple > 10 * cpu_operator_cost ) goto fail ;
 if ( contain_volatile_functions ( param ) ) goto fail ;
 }
 i ++ ;
 }
 MemoryContextSwitchTo ( oldcxt ) ;
 newexpr = copyObject ( newexpr ) ;
 MemoryContextDelete ( mycxt ) ;
 if ( OidIsValid ( result_collid ) ) {
 Oid exprcoll = exprCollation ( newexpr ) ;
 if ( OidIsValid ( exprcoll ) && exprcoll != result_collid ) {
 CollateExpr * newnode = makeNode ( CollateExpr ) ;
 newnode -> arg = ( Expr * ) newexpr ;
 newnode -> collOid = result_collid ;
 newnode -> location = - 1 ;
 newexpr = ( Node * ) newnode ;
 }
 }
 if ( context -> root ) record_plan_function_dependency ( context -> root , funcid ) ;
 context -> active_fns = lcons_oid ( funcid , context -> active_fns ) ;
 newexpr = eval_const_expressions_mutator ( newexpr , context ) ;
 context -> active_fns = list_delete_first ( context -> active_fns ) ;
 error_context_stack = sqlerrcontext . previous ;
 return ( Expr * ) newexpr ;
 fail : MemoryContextSwitchTo ( oldcxt ) ;
 MemoryContextDelete ( mycxt ) ;
 error_context_stack = sqlerrcontext . previous ;
 return NULL ;
 }