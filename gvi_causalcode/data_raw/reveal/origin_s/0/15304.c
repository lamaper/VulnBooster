ExprState * ExecInitExpr ( Expr * node , PlanState * parent ) {
 ExprState * state ;
 if ( node == NULL ) return NULL ;
 check_stack_depth ( ) ;
 switch ( nodeTag ( node ) ) {
 case T_Var : if ( ( ( Var * ) node ) -> varattno == InvalidAttrNumber ) {
 WholeRowVarExprState * wstate = makeNode ( WholeRowVarExprState ) ;
 wstate -> parent = parent ;
 wstate -> wrv_tupdesc = NULL ;
 wstate -> wrv_junkFilter = NULL ;
 state = ( ExprState * ) wstate ;
 state -> evalfunc = ( ExprStateEvalFunc ) ExecEvalWholeRowVar ;
 }
 else {
 state = ( ExprState * ) makeNode ( ExprState ) ;
 state -> evalfunc = ExecEvalScalarVar ;
 }
 break ;
 case T_Const : state = ( ExprState * ) makeNode ( ExprState ) ;
 state -> evalfunc = ExecEvalConst ;
 break ;
 case T_Param : state = ( ExprState * ) makeNode ( ExprState ) ;
 switch ( ( ( Param * ) node ) -> paramkind ) {
 case PARAM_EXEC : state -> evalfunc = ExecEvalParamExec ;
 break ;
 case PARAM_EXTERN : state -> evalfunc = ExecEvalParamExtern ;
 break ;
 default : elog ( ERROR , "unrecognized paramkind: %d" , ( int ) ( ( Param * ) node ) -> paramkind ) ;
 break ;
 }
 break ;
 case T_CoerceToDomainValue : state = ( ExprState * ) makeNode ( ExprState ) ;
 state -> evalfunc = ExecEvalCoerceToDomainValue ;
 break ;
 case T_CaseTestExpr : state = ( ExprState * ) makeNode ( ExprState ) ;
 state -> evalfunc = ExecEvalCaseTestExpr ;
 break ;
 case T_Aggref : {
 AggrefExprState * astate = makeNode ( AggrefExprState ) ;
 astate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalAggref ;
 if ( parent && IsA ( parent , AggState ) ) {
 AggState * aggstate = ( AggState * ) parent ;
 aggstate -> aggs = lcons ( astate , aggstate -> aggs ) ;
 aggstate -> numaggs ++ ;
 }
 else {
 elog ( ERROR , "Aggref found in non-Agg plan node" ) ;
 }
 state = ( ExprState * ) astate ;
 }
 break ;
 case T_GroupingFunc : {
 GroupingFunc * grp_node = ( GroupingFunc * ) node ;
 GroupingFuncExprState * grp_state = makeNode ( GroupingFuncExprState ) ;
 Agg * agg = NULL ;
 if ( ! parent || ! IsA ( parent , AggState ) || ! IsA ( parent -> plan , Agg ) ) elog ( ERROR , "parent of GROUPING is not Agg node" ) ;
 grp_state -> aggstate = ( AggState * ) parent ;
 agg = ( Agg * ) ( parent -> plan ) ;
 if ( agg -> groupingSets ) grp_state -> clauses = grp_node -> cols ;
 else grp_state -> clauses = NIL ;
 state = ( ExprState * ) grp_state ;
 state -> evalfunc = ( ExprStateEvalFunc ) ExecEvalGroupingFuncExpr ;
 }
 break ;
 case T_WindowFunc : {
 WindowFunc * wfunc = ( WindowFunc * ) node ;
 WindowFuncExprState * wfstate = makeNode ( WindowFuncExprState ) ;
 wfstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalWindowFunc ;
 if ( parent && IsA ( parent , WindowAggState ) ) {
 WindowAggState * winstate = ( WindowAggState * ) parent ;
 int nfuncs ;
 winstate -> funcs = lcons ( wfstate , winstate -> funcs ) ;
 nfuncs = ++ winstate -> numfuncs ;
 if ( wfunc -> winagg ) winstate -> numaggs ++ ;
 wfstate -> args = ( List * ) ExecInitExpr ( ( Expr * ) wfunc -> args , parent ) ;
 wfstate -> aggfilter = ExecInitExpr ( wfunc -> aggfilter , parent ) ;
 if ( nfuncs != winstate -> numfuncs ) ereport ( ERROR , ( errcode ( ERRCODE_WINDOWING_ERROR ) , errmsg ( "window function calls cannot be nested" ) ) ) ;
 }
 else {
 elog ( ERROR , "WindowFunc found in non-WindowAgg plan node" ) ;
 }
 state = ( ExprState * ) wfstate ;
 }
 break ;
 case T_ArrayRef : {
 ArrayRef * aref = ( ArrayRef * ) node ;
 ArrayRefExprState * astate = makeNode ( ArrayRefExprState ) ;
 astate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalArrayRef ;
 astate -> refupperindexpr = ( List * ) ExecInitExpr ( ( Expr * ) aref -> refupperindexpr , parent ) ;
 astate -> reflowerindexpr = ( List * ) ExecInitExpr ( ( Expr * ) aref -> reflowerindexpr , parent ) ;
 astate -> refexpr = ExecInitExpr ( aref -> refexpr , parent ) ;
 astate -> refassgnexpr = ExecInitExpr ( aref -> refassgnexpr , parent ) ;
 astate -> refattrlength = get_typlen ( aref -> refarraytype ) ;
 get_typlenbyvalalign ( aref -> refelemtype , & astate -> refelemlength , & astate -> refelembyval , & astate -> refelemalign ) ;
 state = ( ExprState * ) astate ;
 }
 break ;
 case T_FuncExpr : {
 FuncExpr * funcexpr = ( FuncExpr * ) node ;
 FuncExprState * fstate = makeNode ( FuncExprState ) ;
 fstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalFunc ;
 fstate -> args = ( List * ) ExecInitExpr ( ( Expr * ) funcexpr -> args , parent ) ;
 fstate -> func . fn_oid = InvalidOid ;
 state = ( ExprState * ) fstate ;
 }
 break ;
 case T_OpExpr : {
 OpExpr * opexpr = ( OpExpr * ) node ;
 FuncExprState * fstate = makeNode ( FuncExprState ) ;
 fstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalOper ;
 fstate -> args = ( List * ) ExecInitExpr ( ( Expr * ) opexpr -> args , parent ) ;
 fstate -> func . fn_oid = InvalidOid ;
 state = ( ExprState * ) fstate ;
 }
 break ;
 case T_DistinctExpr : {
 DistinctExpr * distinctexpr = ( DistinctExpr * ) node ;
 FuncExprState * fstate = makeNode ( FuncExprState ) ;
 fstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalDistinct ;
 fstate -> args = ( List * ) ExecInitExpr ( ( Expr * ) distinctexpr -> args , parent ) ;
 fstate -> func . fn_oid = InvalidOid ;
 state = ( ExprState * ) fstate ;
 }
 break ;
 case T_NullIfExpr : {
 NullIfExpr * nullifexpr = ( NullIfExpr * ) node ;
 FuncExprState * fstate = makeNode ( FuncExprState ) ;
 fstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalNullIf ;
 fstate -> args = ( List * ) ExecInitExpr ( ( Expr * ) nullifexpr -> args , parent ) ;
 fstate -> func . fn_oid = InvalidOid ;
 state = ( ExprState * ) fstate ;
 }
 break ;
 case T_ScalarArrayOpExpr : {
 ScalarArrayOpExpr * opexpr = ( ScalarArrayOpExpr * ) node ;
 ScalarArrayOpExprState * sstate = makeNode ( ScalarArrayOpExprState ) ;
 sstate -> fxprstate . xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalScalarArrayOp ;
 sstate -> fxprstate . args = ( List * ) ExecInitExpr ( ( Expr * ) opexpr -> args , parent ) ;
 sstate -> fxprstate . func . fn_oid = InvalidOid ;
 sstate -> element_type = InvalidOid ;
 state = ( ExprState * ) sstate ;
 }
 break ;
 case T_BoolExpr : {
 BoolExpr * boolexpr = ( BoolExpr * ) node ;
 BoolExprState * bstate = makeNode ( BoolExprState ) ;
 switch ( boolexpr -> boolop ) {
 case AND_EXPR : bstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalAnd ;
 break ;
 case OR_EXPR : bstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalOr ;
 break ;
 case NOT_EXPR : bstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalNot ;
 break ;
 default : elog ( ERROR , "unrecognized boolop: %d" , ( int ) boolexpr -> boolop ) ;
 break ;
 }
 bstate -> args = ( List * ) ExecInitExpr ( ( Expr * ) boolexpr -> args , parent ) ;
 state = ( ExprState * ) bstate ;
 }
 break ;
 case T_SubPlan : {
 SubPlan * subplan = ( SubPlan * ) node ;
 SubPlanState * sstate ;
 if ( ! parent ) elog ( ERROR , "SubPlan found with no parent plan" ) ;
 sstate = ExecInitSubPlan ( subplan , parent ) ;
 parent -> subPlan = lappend ( parent -> subPlan , sstate ) ;
 state = ( ExprState * ) sstate ;
 }
 break ;
 case T_AlternativeSubPlan : {
 AlternativeSubPlan * asplan = ( AlternativeSubPlan * ) node ;
 AlternativeSubPlanState * asstate ;
 if ( ! parent ) elog ( ERROR , "AlternativeSubPlan found with no parent plan" ) ;
 asstate = ExecInitAlternativeSubPlan ( asplan , parent ) ;
 state = ( ExprState * ) asstate ;
 }
 break ;
 case T_FieldSelect : {
 FieldSelect * fselect = ( FieldSelect * ) node ;
 FieldSelectState * fstate = makeNode ( FieldSelectState ) ;
 fstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalFieldSelect ;
 fstate -> arg = ExecInitExpr ( fselect -> arg , parent ) ;
 fstate -> argdesc = NULL ;
 state = ( ExprState * ) fstate ;
 }
 break ;
 case T_FieldStore : {
 FieldStore * fstore = ( FieldStore * ) node ;
 FieldStoreState * fstate = makeNode ( FieldStoreState ) ;
 fstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalFieldStore ;
 fstate -> arg = ExecInitExpr ( fstore -> arg , parent ) ;
 fstate -> newvals = ( List * ) ExecInitExpr ( ( Expr * ) fstore -> newvals , parent ) ;
 fstate -> argdesc = NULL ;
 state = ( ExprState * ) fstate ;
 }
 break ;
 case T_RelabelType : {
 RelabelType * relabel = ( RelabelType * ) node ;
 GenericExprState * gstate = makeNode ( GenericExprState ) ;
 gstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalRelabelType ;
 gstate -> arg = ExecInitExpr ( relabel -> arg , parent ) ;
 state = ( ExprState * ) gstate ;
 }
 break ;
 case T_CoerceViaIO : {
 CoerceViaIO * iocoerce = ( CoerceViaIO * ) node ;
 CoerceViaIOState * iostate = makeNode ( CoerceViaIOState ) ;
 Oid iofunc ;
 bool typisvarlena ;
 iostate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalCoerceViaIO ;
 iostate -> arg = ExecInitExpr ( iocoerce -> arg , parent ) ;
 getTypeInputInfo ( iocoerce -> resulttype , & iofunc , & iostate -> intypioparam ) ;
 fmgr_info ( iofunc , & iostate -> infunc ) ;
 getTypeOutputInfo ( exprType ( ( Node * ) iocoerce -> arg ) , & iofunc , & typisvarlena ) ;
 fmgr_info ( iofunc , & iostate -> outfunc ) ;
 state = ( ExprState * ) iostate ;
 }
 break ;
 case T_ArrayCoerceExpr : {
 ArrayCoerceExpr * acoerce = ( ArrayCoerceExpr * ) node ;
 ArrayCoerceExprState * astate = makeNode ( ArrayCoerceExprState ) ;
 astate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalArrayCoerceExpr ;
 astate -> arg = ExecInitExpr ( acoerce -> arg , parent ) ;
 astate -> resultelemtype = get_element_type ( acoerce -> resulttype ) ;
 if ( astate -> resultelemtype == InvalidOid ) ereport ( ERROR , ( errcode ( ERRCODE_INVALID_PARAMETER_VALUE ) , errmsg ( "target type is not an array" ) ) ) ;
 Assert ( getBaseType ( astate -> resultelemtype ) == astate -> resultelemtype ) ;
 astate -> elemfunc . fn_oid = InvalidOid ;
 astate -> amstate = ( ArrayMapState * ) palloc0 ( sizeof ( ArrayMapState ) ) ;
 state = ( ExprState * ) astate ;
 }
 break ;
 case T_ConvertRowtypeExpr : {
 ConvertRowtypeExpr * convert = ( ConvertRowtypeExpr * ) node ;
 ConvertRowtypeExprState * cstate = makeNode ( ConvertRowtypeExprState ) ;
 cstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalConvertRowtype ;
 cstate -> arg = ExecInitExpr ( convert -> arg , parent ) ;
 state = ( ExprState * ) cstate ;
 }
 break ;
 case T_CaseExpr : {
 CaseExpr * caseexpr = ( CaseExpr * ) node ;
 CaseExprState * cstate = makeNode ( CaseExprState ) ;
 List * outlist = NIL ;
 ListCell * l ;
 cstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalCase ;
 cstate -> arg = ExecInitExpr ( caseexpr -> arg , parent ) ;
 foreach ( l , caseexpr -> args ) {
 CaseWhen * when = ( CaseWhen * ) lfirst ( l ) ;
 CaseWhenState * wstate = makeNode ( CaseWhenState ) ;
 Assert ( IsA ( when , CaseWhen ) ) ;
 wstate -> xprstate . evalfunc = NULL ;
 wstate -> xprstate . expr = ( Expr * ) when ;
 wstate -> expr = ExecInitExpr ( when -> expr , parent ) ;
 wstate -> result = ExecInitExpr ( when -> result , parent ) ;
 outlist = lappend ( outlist , wstate ) ;
 }
 cstate -> args = outlist ;
 cstate -> defresult = ExecInitExpr ( caseexpr -> defresult , parent ) ;
 state = ( ExprState * ) cstate ;
 }
 break ;
 case T_ArrayExpr : {
 ArrayExpr * arrayexpr = ( ArrayExpr * ) node ;
 ArrayExprState * astate = makeNode ( ArrayExprState ) ;
 List * outlist = NIL ;
 ListCell * l ;
 astate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalArray ;
 foreach ( l , arrayexpr -> elements ) {
 Expr * e = ( Expr * ) lfirst ( l ) ;
 ExprState * estate ;
 estate = ExecInitExpr ( e , parent ) ;
 outlist = lappend ( outlist , estate ) ;
 }
 astate -> elements = outlist ;
 get_typlenbyvalalign ( arrayexpr -> element_typeid , & astate -> elemlength , & astate -> elembyval , & astate -> elemalign ) ;
 state = ( ExprState * ) astate ;
 }
 break ;
 case T_RowExpr : {
 RowExpr * rowexpr = ( RowExpr * ) node ;
 RowExprState * rstate = makeNode ( RowExprState ) ;
 Form_pg_attribute * attrs ;
 List * outlist = NIL ;
 ListCell * l ;
 int i ;
 rstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalRow ;
 if ( rowexpr -> row_typeid == RECORDOID ) {
 rstate -> tupdesc = ExecTypeFromExprList ( rowexpr -> args ) ;
 }
 else {
 rstate -> tupdesc = lookup_rowtype_tupdesc_copy ( rowexpr -> row_typeid , - 1 ) ;
 }
 ExecTypeSetColNames ( rstate -> tupdesc , rowexpr -> colnames ) ;
 BlessTupleDesc ( rstate -> tupdesc ) ;
 Assert ( list_length ( rowexpr -> args ) <= rstate -> tupdesc -> natts ) ;
 attrs = rstate -> tupdesc -> attrs ;
 i = 0 ;
 foreach ( l , rowexpr -> args ) {
 Expr * e = ( Expr * ) lfirst ( l ) ;
 ExprState * estate ;
 if ( ! attrs [ i ] -> attisdropped ) {
 if ( exprType ( ( Node * ) e ) != attrs [ i ] -> atttypid ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "ROW() column has type %s instead of type %s" , format_type_be ( exprType ( ( Node * ) e ) ) , format_type_be ( attrs [ i ] -> atttypid ) ) ) ) ;
 }
 else {
 e = ( Expr * ) makeNullConst ( INT4OID , - 1 , InvalidOid ) ;
 }
 estate = ExecInitExpr ( e , parent ) ;
 outlist = lappend ( outlist , estate ) ;
 i ++ ;
 }
 rstate -> args = outlist ;
 state = ( ExprState * ) rstate ;
 }
 break ;
 case T_RowCompareExpr : {
 RowCompareExpr * rcexpr = ( RowCompareExpr * ) node ;
 RowCompareExprState * rstate = makeNode ( RowCompareExprState ) ;
 int nopers = list_length ( rcexpr -> opnos ) ;
 List * outlist ;
 ListCell * l ;
 ListCell * l2 ;
 ListCell * l3 ;
 int i ;
 rstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalRowCompare ;
 Assert ( list_length ( rcexpr -> largs ) == nopers ) ;
 outlist = NIL ;
 foreach ( l , rcexpr -> largs ) {
 Expr * e = ( Expr * ) lfirst ( l ) ;
 ExprState * estate ;
 estate = ExecInitExpr ( e , parent ) ;
 outlist = lappend ( outlist , estate ) ;
 }
 rstate -> largs = outlist ;
 Assert ( list_length ( rcexpr -> rargs ) == nopers ) ;
 outlist = NIL ;
 foreach ( l , rcexpr -> rargs ) {
 Expr * e = ( Expr * ) lfirst ( l ) ;
 ExprState * estate ;
 estate = ExecInitExpr ( e , parent ) ;
 outlist = lappend ( outlist , estate ) ;
 }
 rstate -> rargs = outlist ;
 Assert ( list_length ( rcexpr -> opfamilies ) == nopers ) ;
 rstate -> funcs = ( FmgrInfo * ) palloc ( nopers * sizeof ( FmgrInfo ) ) ;
 rstate -> collations = ( Oid * ) palloc ( nopers * sizeof ( Oid ) ) ;
 i = 0 ;
 forthree ( l , rcexpr -> opnos , l2 , rcexpr -> opfamilies , l3 , rcexpr -> inputcollids ) {
 Oid opno = lfirst_oid ( l ) ;
 Oid opfamily = lfirst_oid ( l2 ) ;
 Oid inputcollid = lfirst_oid ( l3 ) ;
 int strategy ;
 Oid lefttype ;
 Oid righttype ;
 Oid proc ;
 get_op_opfamily_properties ( opno , opfamily , false , & strategy , & lefttype , & righttype ) ;
 proc = get_opfamily_proc ( opfamily , lefttype , righttype , BTORDER_PROC ) ;
 fmgr_info ( proc , & ( rstate -> funcs [ i ] ) ) ;
 rstate -> collations [ i ] = inputcollid ;
 i ++ ;
 }
 state = ( ExprState * ) rstate ;
 }
 break ;
 case T_CoalesceExpr : {
 CoalesceExpr * coalesceexpr = ( CoalesceExpr * ) node ;
 CoalesceExprState * cstate = makeNode ( CoalesceExprState ) ;
 List * outlist = NIL ;
 ListCell * l ;
 cstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalCoalesce ;
 foreach ( l , coalesceexpr -> args ) {
 Expr * e = ( Expr * ) lfirst ( l ) ;
 ExprState * estate ;
 estate = ExecInitExpr ( e , parent ) ;
 outlist = lappend ( outlist , estate ) ;
 }
 cstate -> args = outlist ;
 state = ( ExprState * ) cstate ;
 }
 break ;
 case T_MinMaxExpr : {
 MinMaxExpr * minmaxexpr = ( MinMaxExpr * ) node ;
 MinMaxExprState * mstate = makeNode ( MinMaxExprState ) ;
 List * outlist = NIL ;
 ListCell * l ;
 TypeCacheEntry * typentry ;
 mstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalMinMax ;
 foreach ( l , minmaxexpr -> args ) {
 Expr * e = ( Expr * ) lfirst ( l ) ;
 ExprState * estate ;
 estate = ExecInitExpr ( e , parent ) ;
 outlist = lappend ( outlist , estate ) ;
 }
 mstate -> args = outlist ;
 typentry = lookup_type_cache ( minmaxexpr -> minmaxtype , TYPECACHE_CMP_PROC ) ;
 if ( ! OidIsValid ( typentry -> cmp_proc ) ) ereport ( ERROR , ( errcode ( ERRCODE_UNDEFINED_FUNCTION ) , errmsg ( "could not identify a comparison function for type %s" , format_type_be ( minmaxexpr -> minmaxtype ) ) ) ) ;
 fmgr_info ( typentry -> cmp_proc , & ( mstate -> cfunc ) ) ;
 state = ( ExprState * ) mstate ;
 }
 break ;
 case T_XmlExpr : {
 XmlExpr * xexpr = ( XmlExpr * ) node ;
 XmlExprState * xstate = makeNode ( XmlExprState ) ;
 List * outlist ;
 ListCell * arg ;
 xstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalXml ;
 outlist = NIL ;
 foreach ( arg , xexpr -> named_args ) {
 Expr * e = ( Expr * ) lfirst ( arg ) ;
 ExprState * estate ;
 estate = ExecInitExpr ( e , parent ) ;
 outlist = lappend ( outlist , estate ) ;
 }
 xstate -> named_args = outlist ;
 outlist = NIL ;
 foreach ( arg , xexpr -> args ) {
 Expr * e = ( Expr * ) lfirst ( arg ) ;
 ExprState * estate ;
 estate = ExecInitExpr ( e , parent ) ;
 outlist = lappend ( outlist , estate ) ;
 }
 xstate -> args = outlist ;
 state = ( ExprState * ) xstate ;
 }
 break ;
 case T_NullTest : {
 NullTest * ntest = ( NullTest * ) node ;
 NullTestState * nstate = makeNode ( NullTestState ) ;
 nstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalNullTest ;
 nstate -> arg = ExecInitExpr ( ntest -> arg , parent ) ;
 nstate -> argdesc = NULL ;
 state = ( ExprState * ) nstate ;
 }
 break ;
 case T_BooleanTest : {
 BooleanTest * btest = ( BooleanTest * ) node ;
 GenericExprState * gstate = makeNode ( GenericExprState ) ;
 gstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalBooleanTest ;
 gstate -> arg = ExecInitExpr ( btest -> arg , parent ) ;
 state = ( ExprState * ) gstate ;
 }
 break ;
 case T_CoerceToDomain : {
 CoerceToDomain * ctest = ( CoerceToDomain * ) node ;
 CoerceToDomainState * cstate = makeNode ( CoerceToDomainState ) ;
 cstate -> xprstate . evalfunc = ( ExprStateEvalFunc ) ExecEvalCoerceToDomain ;
 cstate -> arg = ExecInitExpr ( ctest -> arg , parent ) ;
 cstate -> constraint_ref = ( DomainConstraintRef * ) palloc ( sizeof ( DomainConstraintRef ) ) ;
 InitDomainConstraintRef ( ctest -> resulttype , cstate -> constraint_ref , CurrentMemoryContext ) ;
 state = ( ExprState * ) cstate ;
 }
 break ;
 case T_CurrentOfExpr : state = ( ExprState * ) makeNode ( ExprState ) ;
 state -> evalfunc = ExecEvalCurrentOfExpr ;
 break ;
 case T_TargetEntry : {
 TargetEntry * tle = ( TargetEntry * ) node ;
 GenericExprState * gstate = makeNode ( GenericExprState ) ;
 gstate -> xprstate . evalfunc = NULL ;
 gstate -> arg = ExecInitExpr ( tle -> expr , parent ) ;
 state = ( ExprState * ) gstate ;
 }
 break ;
 case T_List : {
 List * outlist = NIL ;
 ListCell * l ;
 foreach ( l , ( List * ) node ) {
 outlist = lappend ( outlist , ExecInitExpr ( ( Expr * ) lfirst ( l ) , parent ) ) ;
 }
 return ( ExprState * ) outlist ;
 }
 default : elog ( ERROR , "unrecognized node type: %d" , ( int ) nodeTag ( node ) ) ;
 state = NULL ;
 break ;
 }
 state -> expr = node ;
 return state ;
 }