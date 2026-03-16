static Node * eval_const_expressions_mutator ( Node * node , eval_const_expressions_context * context ) {
 if ( node == NULL ) return NULL ;
 switch ( nodeTag ( node ) ) {
 case T_Param : {
 Param * param = ( Param * ) node ;
 if ( param -> paramkind == PARAM_EXTERN && context -> boundParams != NULL && param -> paramid > 0 && param -> paramid <= context -> boundParams -> numParams ) {
 ParamExternData * prm = & context -> boundParams -> params [ param -> paramid - 1 ] ;
 if ( OidIsValid ( prm -> ptype ) ) {
 if ( context -> estimate || ( prm -> pflags & PARAM_FLAG_CONST ) ) {
 int16 typLen ;
 bool typByVal ;
 Datum pval ;
 Assert ( prm -> ptype == param -> paramtype ) ;
 get_typlenbyval ( param -> paramtype , & typLen , & typByVal ) ;
 if ( prm -> isnull || typByVal ) pval = prm -> value ;
 else pval = datumCopy ( prm -> value , typByVal , typLen ) ;
 return ( Node * ) makeConst ( param -> paramtype , param -> paramtypmod , param -> paramcollid , ( int ) typLen , pval , prm -> isnull , typByVal ) ;
 }
 }
 }
 return ( Node * ) copyObject ( param ) ;
 }
 case T_WindowFunc : {
 WindowFunc * expr = ( WindowFunc * ) node ;
 Oid funcid = expr -> winfnoid ;
 List * args ;
 Expr * aggfilter ;
 HeapTuple func_tuple ;
 WindowFunc * newexpr ;
 func_tuple = SearchSysCache1 ( PROCOID , ObjectIdGetDatum ( funcid ) ) ;
 if ( ! HeapTupleIsValid ( func_tuple ) ) elog ( ERROR , "cache lookup failed for function %u" , funcid ) ;
 args = expand_function_arguments ( expr -> args , expr -> wintype , func_tuple ) ;
 ReleaseSysCache ( func_tuple ) ;
 args = ( List * ) expression_tree_mutator ( ( Node * ) args , eval_const_expressions_mutator , ( void * ) context ) ;
 aggfilter = ( Expr * ) eval_const_expressions_mutator ( ( Node * ) expr -> aggfilter , context ) ;
 newexpr = makeNode ( WindowFunc ) ;
 newexpr -> winfnoid = expr -> winfnoid ;
 newexpr -> wintype = expr -> wintype ;
 newexpr -> wincollid = expr -> wincollid ;
 newexpr -> inputcollid = expr -> inputcollid ;
 newexpr -> args = args ;
 newexpr -> aggfilter = aggfilter ;
 newexpr -> winref = expr -> winref ;
 newexpr -> winstar = expr -> winstar ;
 newexpr -> winagg = expr -> winagg ;
 newexpr -> location = expr -> location ;
 return ( Node * ) newexpr ;
 }
 case T_FuncExpr : {
 FuncExpr * expr = ( FuncExpr * ) node ;
 List * args = expr -> args ;
 Expr * simple ;
 FuncExpr * newexpr ;
 simple = simplify_function ( expr -> funcid , expr -> funcresulttype , exprTypmod ( node ) , expr -> funccollid , expr -> inputcollid , & args , expr -> funcvariadic , true , true , context ) ;
 if ( simple ) return ( Node * ) simple ;
 newexpr = makeNode ( FuncExpr ) ;
 newexpr -> funcid = expr -> funcid ;
 newexpr -> funcresulttype = expr -> funcresulttype ;
 newexpr -> funcretset = expr -> funcretset ;
 newexpr -> funcvariadic = expr -> funcvariadic ;
 newexpr -> funcformat = expr -> funcformat ;
 newexpr -> funccollid = expr -> funccollid ;
 newexpr -> inputcollid = expr -> inputcollid ;
 newexpr -> args = args ;
 newexpr -> location = expr -> location ;
 return ( Node * ) newexpr ;
 }
 case T_OpExpr : {
 OpExpr * expr = ( OpExpr * ) node ;
 List * args = expr -> args ;
 Expr * simple ;
 OpExpr * newexpr ;
 set_opfuncid ( expr ) ;
 simple = simplify_function ( expr -> opfuncid , expr -> opresulttype , - 1 , expr -> opcollid , expr -> inputcollid , & args , false , true , true , context ) ;
 if ( simple ) return ( Node * ) simple ;
 if ( expr -> opno == BooleanEqualOperator || expr -> opno == BooleanNotEqualOperator ) {
 simple = ( Expr * ) simplify_boolean_equality ( expr -> opno , args ) ;
 if ( simple ) return ( Node * ) simple ;
 }
 newexpr = makeNode ( OpExpr ) ;
 newexpr -> opno = expr -> opno ;
 newexpr -> opfuncid = expr -> opfuncid ;
 newexpr -> opresulttype = expr -> opresulttype ;
 newexpr -> opretset = expr -> opretset ;
 newexpr -> opcollid = expr -> opcollid ;
 newexpr -> inputcollid = expr -> inputcollid ;
 newexpr -> args = args ;
 newexpr -> location = expr -> location ;
 return ( Node * ) newexpr ;
 }
 case T_DistinctExpr : {
 DistinctExpr * expr = ( DistinctExpr * ) node ;
 List * args ;
 ListCell * arg ;
 bool has_null_input = false ;
 bool all_null_input = true ;
 bool has_nonconst_input = false ;
 Expr * simple ;
 DistinctExpr * newexpr ;
 args = ( List * ) expression_tree_mutator ( ( Node * ) expr -> args , eval_const_expressions_mutator , ( void * ) context ) ;
 foreach ( arg , args ) {
 if ( IsA ( lfirst ( arg ) , Const ) ) {
 has_null_input |= ( ( Const * ) lfirst ( arg ) ) -> constisnull ;
 all_null_input &= ( ( Const * ) lfirst ( arg ) ) -> constisnull ;
 }
 else has_nonconst_input = true ;
 }
 if ( ! has_nonconst_input ) {
 if ( all_null_input ) return makeBoolConst ( false , false ) ;
 if ( has_null_input ) return makeBoolConst ( true , false ) ;
 set_opfuncid ( ( OpExpr * ) expr ) ;
 simple = simplify_function ( expr -> opfuncid , expr -> opresulttype , - 1 , expr -> opcollid , expr -> inputcollid , & args , false , false , false , context ) ;
 if ( simple ) {
 Const * csimple = ( Const * ) simple ;
 Assert ( IsA ( csimple , Const ) ) ;
 csimple -> constvalue = BoolGetDatum ( ! DatumGetBool ( csimple -> constvalue ) ) ;
 return ( Node * ) csimple ;
 }
 }
 newexpr = makeNode ( DistinctExpr ) ;
 newexpr -> opno = expr -> opno ;
 newexpr -> opfuncid = expr -> opfuncid ;
 newexpr -> opresulttype = expr -> opresulttype ;
 newexpr -> opretset = expr -> opretset ;
 newexpr -> opcollid = expr -> opcollid ;
 newexpr -> inputcollid = expr -> inputcollid ;
 newexpr -> args = args ;
 newexpr -> location = expr -> location ;
 return ( Node * ) newexpr ;
 }
 case T_BoolExpr : {
 BoolExpr * expr = ( BoolExpr * ) node ;
 switch ( expr -> boolop ) {
 case OR_EXPR : {
 List * newargs ;
 bool haveNull = false ;
 bool forceTrue = false ;
 newargs = simplify_or_arguments ( expr -> args , context , & haveNull , & forceTrue ) ;
 if ( forceTrue ) return makeBoolConst ( true , false ) ;
 if ( haveNull ) newargs = lappend ( newargs , makeBoolConst ( false , true ) ) ;
 if ( newargs == NIL ) return makeBoolConst ( false , false ) ;
 if ( list_length ( newargs ) == 1 ) return ( Node * ) linitial ( newargs ) ;
 return ( Node * ) make_orclause ( newargs ) ;
 }
 case AND_EXPR : {
 List * newargs ;
 bool haveNull = false ;
 bool forceFalse = false ;
 newargs = simplify_and_arguments ( expr -> args , context , & haveNull , & forceFalse ) ;
 if ( forceFalse ) return makeBoolConst ( false , false ) ;
 if ( haveNull ) newargs = lappend ( newargs , makeBoolConst ( false , true ) ) ;
 if ( newargs == NIL ) return makeBoolConst ( true , false ) ;
 if ( list_length ( newargs ) == 1 ) return ( Node * ) linitial ( newargs ) ;
 return ( Node * ) make_andclause ( newargs ) ;
 }
 case NOT_EXPR : {
 Node * arg ;
 Assert ( list_length ( expr -> args ) == 1 ) ;
 arg = eval_const_expressions_mutator ( linitial ( expr -> args ) , context ) ;
 return negate_clause ( arg ) ;
 }
 default : elog ( ERROR , "unrecognized boolop: %d" , ( int ) expr -> boolop ) ;
 break ;
 }
 break ;
 }
 case T_SubPlan : case T_AlternativeSubPlan : return node ;
 case T_RelabelType : {
 RelabelType * relabel = ( RelabelType * ) node ;
 Node * arg ;
 arg = eval_const_expressions_mutator ( ( Node * ) relabel -> arg , context ) ;
 while ( arg && IsA ( arg , RelabelType ) ) arg = ( Node * ) ( ( RelabelType * ) arg ) -> arg ;
 if ( arg && IsA ( arg , Const ) ) {
 Const * con = ( Const * ) arg ;
 con -> consttype = relabel -> resulttype ;
 con -> consttypmod = relabel -> resulttypmod ;
 con -> constcollid = relabel -> resultcollid ;
 return ( Node * ) con ;
 }
 else {
 RelabelType * newrelabel = makeNode ( RelabelType ) ;
 newrelabel -> arg = ( Expr * ) arg ;
 newrelabel -> resulttype = relabel -> resulttype ;
 newrelabel -> resulttypmod = relabel -> resulttypmod ;
 newrelabel -> resultcollid = relabel -> resultcollid ;
 newrelabel -> relabelformat = relabel -> relabelformat ;
 newrelabel -> location = relabel -> location ;
 return ( Node * ) newrelabel ;
 }
 }
 case T_CoerceViaIO : {
 CoerceViaIO * expr = ( CoerceViaIO * ) node ;
 List * args ;
 Oid outfunc ;
 bool outtypisvarlena ;
 Oid infunc ;
 Oid intypioparam ;
 Expr * simple ;
 CoerceViaIO * newexpr ;
 args = list_make1 ( expr -> arg ) ;
 getTypeOutputInfo ( exprType ( ( Node * ) expr -> arg ) , & outfunc , & outtypisvarlena ) ;
 getTypeInputInfo ( expr -> resulttype , & infunc , & intypioparam ) ;
 simple = simplify_function ( outfunc , CSTRINGOID , - 1 , InvalidOid , InvalidOid , & args , false , true , true , context ) ;
 if ( simple ) {
 args = list_make3 ( simple , makeConst ( OIDOID , - 1 , InvalidOid , sizeof ( Oid ) , ObjectIdGetDatum ( intypioparam ) , false , true ) , makeConst ( INT4OID , - 1 , InvalidOid , sizeof ( int32 ) , Int32GetDatum ( - 1 ) , false , true ) ) ;
 simple = simplify_function ( infunc , expr -> resulttype , - 1 , expr -> resultcollid , InvalidOid , & args , false , false , true , context ) ;
 if ( simple ) return ( Node * ) simple ;
 }
 newexpr = makeNode ( CoerceViaIO ) ;
 newexpr -> arg = ( Expr * ) linitial ( args ) ;
 newexpr -> resulttype = expr -> resulttype ;
 newexpr -> resultcollid = expr -> resultcollid ;
 newexpr -> coerceformat = expr -> coerceformat ;
 newexpr -> location = expr -> location ;
 return ( Node * ) newexpr ;
 }
 case T_ArrayCoerceExpr : {
 ArrayCoerceExpr * expr = ( ArrayCoerceExpr * ) node ;
 Expr * arg ;
 ArrayCoerceExpr * newexpr ;
 arg = ( Expr * ) eval_const_expressions_mutator ( ( Node * ) expr -> arg , context ) ;
 newexpr = makeNode ( ArrayCoerceExpr ) ;
 newexpr -> arg = arg ;
 newexpr -> elemfuncid = expr -> elemfuncid ;
 newexpr -> resulttype = expr -> resulttype ;
 newexpr -> resulttypmod = expr -> resulttypmod ;
 newexpr -> resultcollid = expr -> resultcollid ;
 newexpr -> isExplicit = expr -> isExplicit ;
 newexpr -> coerceformat = expr -> coerceformat ;
 newexpr -> location = expr -> location ;
 if ( arg && IsA ( arg , Const ) && ( ! OidIsValid ( newexpr -> elemfuncid ) || func_volatile ( newexpr -> elemfuncid ) == PROVOLATILE_IMMUTABLE ) ) return ( Node * ) evaluate_expr ( ( Expr * ) newexpr , newexpr -> resulttype , newexpr -> resulttypmod , newexpr -> resultcollid ) ;
 return ( Node * ) newexpr ;
 }
 case T_CollateExpr : {
 CollateExpr * collate = ( CollateExpr * ) node ;
 Node * arg ;
 arg = eval_const_expressions_mutator ( ( Node * ) collate -> arg , context ) ;
 if ( arg && IsA ( arg , Const ) ) {
 Const * con = ( Const * ) arg ;
 con -> constcollid = collate -> collOid ;
 return ( Node * ) con ;
 }
 else if ( collate -> collOid == exprCollation ( arg ) ) {
 return arg ;
 }
 else {
 RelabelType * relabel = makeNode ( RelabelType ) ;
 relabel -> resulttype = exprType ( arg ) ;
 relabel -> resulttypmod = exprTypmod ( arg ) ;
 relabel -> resultcollid = collate -> collOid ;
 relabel -> relabelformat = COERCE_IMPLICIT_CAST ;
 relabel -> location = collate -> location ;
 while ( arg && IsA ( arg , RelabelType ) ) arg = ( Node * ) ( ( RelabelType * ) arg ) -> arg ;
 relabel -> arg = ( Expr * ) arg ;
 return ( Node * ) relabel ;
 }
 }
 case T_CaseExpr : {
 CaseExpr * caseexpr = ( CaseExpr * ) node ;
 CaseExpr * newcase ;
 Node * save_case_val ;
 Node * newarg ;
 List * newargs ;
 bool const_true_cond ;
 Node * defresult = NULL ;
 ListCell * arg ;
 newarg = eval_const_expressions_mutator ( ( Node * ) caseexpr -> arg , context ) ;
 save_case_val = context -> case_val ;
 if ( newarg && IsA ( newarg , Const ) ) {
 context -> case_val = newarg ;
 newarg = NULL ;
 }
 else context -> case_val = NULL ;
 newargs = NIL ;
 const_true_cond = false ;
 foreach ( arg , caseexpr -> args ) {
 CaseWhen * oldcasewhen = ( CaseWhen * ) lfirst ( arg ) ;
 Node * casecond ;
 Node * caseresult ;
 Assert ( IsA ( oldcasewhen , CaseWhen ) ) ;
 casecond = eval_const_expressions_mutator ( ( Node * ) oldcasewhen -> expr , context ) ;
 if ( casecond && IsA ( casecond , Const ) ) {
 Const * const_input = ( Const * ) casecond ;
 if ( const_input -> constisnull || ! DatumGetBool ( const_input -> constvalue ) ) continue ;
 const_true_cond = true ;
 }
 caseresult = eval_const_expressions_mutator ( ( Node * ) oldcasewhen -> result , context ) ;
 if ( ! const_true_cond ) {
 CaseWhen * newcasewhen = makeNode ( CaseWhen ) ;
 newcasewhen -> expr = ( Expr * ) casecond ;
 newcasewhen -> result = ( Expr * ) caseresult ;
 newcasewhen -> location = oldcasewhen -> location ;
 newargs = lappend ( newargs , newcasewhen ) ;
 continue ;
 }
 defresult = caseresult ;
 break ;
 }
 if ( ! const_true_cond ) defresult = eval_const_expressions_mutator ( ( Node * ) caseexpr -> defresult , context ) ;
 context -> case_val = save_case_val ;
 if ( newargs == NIL ) return defresult ;
 newcase = makeNode ( CaseExpr ) ;
 newcase -> casetype = caseexpr -> casetype ;
 newcase -> casecollid = caseexpr -> casecollid ;
 newcase -> arg = ( Expr * ) newarg ;
 newcase -> args = newargs ;
 newcase -> defresult = ( Expr * ) defresult ;
 newcase -> location = caseexpr -> location ;
 return ( Node * ) newcase ;
 }
 case T_CaseTestExpr : {
 if ( context -> case_val ) return copyObject ( context -> case_val ) ;
 else return copyObject ( node ) ;
 }
 case T_ArrayExpr : {
 ArrayExpr * arrayexpr = ( ArrayExpr * ) node ;
 ArrayExpr * newarray ;
 bool all_const = true ;
 List * newelems ;
 ListCell * element ;
 newelems = NIL ;
 foreach ( element , arrayexpr -> elements ) {
 Node * e ;
 e = eval_const_expressions_mutator ( ( Node * ) lfirst ( element ) , context ) ;
 if ( ! IsA ( e , Const ) ) all_const = false ;
 newelems = lappend ( newelems , e ) ;
 }
 newarray = makeNode ( ArrayExpr ) ;
 newarray -> array_typeid = arrayexpr -> array_typeid ;
 newarray -> array_collid = arrayexpr -> array_collid ;
 newarray -> element_typeid = arrayexpr -> element_typeid ;
 newarray -> elements = newelems ;
 newarray -> multidims = arrayexpr -> multidims ;
 newarray -> location = arrayexpr -> location ;
 if ( all_const ) return ( Node * ) evaluate_expr ( ( Expr * ) newarray , newarray -> array_typeid , exprTypmod ( node ) , newarray -> array_collid ) ;
 return ( Node * ) newarray ;
 }
 case T_CoalesceExpr : {
 CoalesceExpr * coalesceexpr = ( CoalesceExpr * ) node ;
 CoalesceExpr * newcoalesce ;
 List * newargs ;
 ListCell * arg ;
 newargs = NIL ;
 foreach ( arg , coalesceexpr -> args ) {
 Node * e ;
 e = eval_const_expressions_mutator ( ( Node * ) lfirst ( arg ) , context ) ;
 if ( IsA ( e , Const ) ) {
 if ( ( ( Const * ) e ) -> constisnull ) continue ;
 if ( newargs == NIL ) return e ;
 newargs = lappend ( newargs , e ) ;
 break ;
 }
 newargs = lappend ( newargs , e ) ;
 }
 if ( newargs == NIL ) return ( Node * ) makeNullConst ( coalesceexpr -> coalescetype , - 1 , coalesceexpr -> coalescecollid ) ;
 newcoalesce = makeNode ( CoalesceExpr ) ;
 newcoalesce -> coalescetype = coalesceexpr -> coalescetype ;
 newcoalesce -> coalescecollid = coalesceexpr -> coalescecollid ;
 newcoalesce -> args = newargs ;
 newcoalesce -> location = coalesceexpr -> location ;
 return ( Node * ) newcoalesce ;
 }
 case T_FieldSelect : {
 FieldSelect * fselect = ( FieldSelect * ) node ;
 FieldSelect * newfselect ;
 Node * arg ;
 arg = eval_const_expressions_mutator ( ( Node * ) fselect -> arg , context ) ;
 if ( arg && IsA ( arg , Var ) && ( ( Var * ) arg ) -> varattno == InvalidAttrNumber && ( ( Var * ) arg ) -> varlevelsup == 0 ) {
 if ( rowtype_field_matches ( ( ( Var * ) arg ) -> vartype , fselect -> fieldnum , fselect -> resulttype , fselect -> resulttypmod , fselect -> resultcollid ) ) return ( Node * ) makeVar ( ( ( Var * ) arg ) -> varno , fselect -> fieldnum , fselect -> resulttype , fselect -> resulttypmod , fselect -> resultcollid , ( ( Var * ) arg ) -> varlevelsup ) ;
 }
 if ( arg && IsA ( arg , RowExpr ) ) {
 RowExpr * rowexpr = ( RowExpr * ) arg ;
 if ( fselect -> fieldnum > 0 && fselect -> fieldnum <= list_length ( rowexpr -> args ) ) {
 Node * fld = ( Node * ) list_nth ( rowexpr -> args , fselect -> fieldnum - 1 ) ;
 if ( rowtype_field_matches ( rowexpr -> row_typeid , fselect -> fieldnum , fselect -> resulttype , fselect -> resulttypmod , fselect -> resultcollid ) && fselect -> resulttype == exprType ( fld ) && fselect -> resulttypmod == exprTypmod ( fld ) && fselect -> resultcollid == exprCollation ( fld ) ) return fld ;
 }
 }
 newfselect = makeNode ( FieldSelect ) ;
 newfselect -> arg = ( Expr * ) arg ;
 newfselect -> fieldnum = fselect -> fieldnum ;
 newfselect -> resulttype = fselect -> resulttype ;
 newfselect -> resulttypmod = fselect -> resulttypmod ;
 newfselect -> resultcollid = fselect -> resultcollid ;
 return ( Node * ) newfselect ;
 }
 case T_NullTest : {
 NullTest * ntest = ( NullTest * ) node ;
 NullTest * newntest ;
 Node * arg ;
 arg = eval_const_expressions_mutator ( ( Node * ) ntest -> arg , context ) ;
 if ( ntest -> argisrow && arg && IsA ( arg , RowExpr ) ) {
 RowExpr * rarg = ( RowExpr * ) arg ;
 List * newargs = NIL ;
 ListCell * l ;
 foreach ( l , rarg -> args ) {
 Node * relem = ( Node * ) lfirst ( l ) ;
 if ( relem && IsA ( relem , Const ) ) {
 Const * carg = ( Const * ) relem ;
 if ( carg -> constisnull ? ( ntest -> nulltesttype == IS_NOT_NULL ) : ( ntest -> nulltesttype == IS_NULL ) ) return makeBoolConst ( false , false ) ;
 continue ;
 }
 newntest = makeNode ( NullTest ) ;
 newntest -> arg = ( Expr * ) relem ;
 newntest -> nulltesttype = ntest -> nulltesttype ;
 newntest -> argisrow = false ;
 newntest -> location = ntest -> location ;
 newargs = lappend ( newargs , newntest ) ;
 }
 if ( newargs == NIL ) return makeBoolConst ( true , false ) ;
 if ( list_length ( newargs ) == 1 ) return ( Node * ) linitial ( newargs ) ;
 return ( Node * ) make_andclause ( newargs ) ;
 }
 if ( ! ntest -> argisrow && arg && IsA ( arg , Const ) ) {
 Const * carg = ( Const * ) arg ;
 bool result ;
 switch ( ntest -> nulltesttype ) {
 case IS_NULL : result = carg -> constisnull ;
 break ;
 case IS_NOT_NULL : result = ! carg -> constisnull ;
 break ;
 default : elog ( ERROR , "unrecognized nulltesttype: %d" , ( int ) ntest -> nulltesttype ) ;
 result = false ;
 break ;
 }
 return makeBoolConst ( result , false ) ;
 }
 newntest = makeNode ( NullTest ) ;
 newntest -> arg = ( Expr * ) arg ;
 newntest -> nulltesttype = ntest -> nulltesttype ;
 newntest -> argisrow = ntest -> argisrow ;
 newntest -> location = ntest -> location ;
 return ( Node * ) newntest ;
 }
 case T_BooleanTest : {
 BooleanTest * btest = ( BooleanTest * ) node ;
 BooleanTest * newbtest ;
 Node * arg ;
 arg = eval_const_expressions_mutator ( ( Node * ) btest -> arg , context ) ;
 if ( arg && IsA ( arg , Const ) ) {
 Const * carg = ( Const * ) arg ;
 bool result ;
 switch ( btest -> booltesttype ) {
 case IS_TRUE : result = ( ! carg -> constisnull && DatumGetBool ( carg -> constvalue ) ) ;
 break ;
 case IS_NOT_TRUE : result = ( carg -> constisnull || ! DatumGetBool ( carg -> constvalue ) ) ;
 break ;
 case IS_FALSE : result = ( ! carg -> constisnull && ! DatumGetBool ( carg -> constvalue ) ) ;
 break ;
 case IS_NOT_FALSE : result = ( carg -> constisnull || DatumGetBool ( carg -> constvalue ) ) ;
 break ;
 case IS_UNKNOWN : result = carg -> constisnull ;
 break ;
 case IS_NOT_UNKNOWN : result = ! carg -> constisnull ;
 break ;
 default : elog ( ERROR , "unrecognized booltesttype: %d" , ( int ) btest -> booltesttype ) ;
 result = false ;
 break ;
 }
 return makeBoolConst ( result , false ) ;
 }
 newbtest = makeNode ( BooleanTest ) ;
 newbtest -> arg = ( Expr * ) arg ;
 newbtest -> booltesttype = btest -> booltesttype ;
 newbtest -> location = btest -> location ;
 return ( Node * ) newbtest ;
 }
 case T_PlaceHolderVar : if ( context -> estimate ) {
 PlaceHolderVar * phv = ( PlaceHolderVar * ) node ;
 return eval_const_expressions_mutator ( ( Node * ) phv -> phexpr , context ) ;
 }
 break ;
 default : break ;
 }
 return expression_tree_mutator ( node , eval_const_expressions_mutator , ( void * ) context ) ;
 }