static bool get_agg_clause_costs_walker ( Node * node , get_agg_clause_costs_context * context ) {
 if ( node == NULL ) return false ;
 if ( IsA ( node , Aggref ) ) {
 Aggref * aggref = ( Aggref * ) node ;
 AggClauseCosts * costs = context -> costs ;
 HeapTuple aggTuple ;
 Form_pg_aggregate aggform ;
 Oid aggtransfn ;
 Oid aggfinalfn ;
 Oid aggcombinefn ;
 Oid aggserialfn ;
 Oid aggdeserialfn ;
 Oid aggtranstype ;
 int32 aggtransspace ;
 QualCost argcosts ;
 Assert ( aggref -> agglevelsup == 0 ) ;
 aggTuple = SearchSysCache1 ( AGGFNOID , ObjectIdGetDatum ( aggref -> aggfnoid ) ) ;
 if ( ! HeapTupleIsValid ( aggTuple ) ) elog ( ERROR , "cache lookup failed for aggregate %u" , aggref -> aggfnoid ) ;
 aggform = ( Form_pg_aggregate ) GETSTRUCT ( aggTuple ) ;
 aggtransfn = aggform -> aggtransfn ;
 aggfinalfn = aggform -> aggfinalfn ;
 aggcombinefn = aggform -> aggcombinefn ;
 aggserialfn = aggform -> aggserialfn ;
 aggdeserialfn = aggform -> aggdeserialfn ;
 aggtranstype = aggform -> aggtranstype ;
 aggtransspace = aggform -> aggtransspace ;
 ReleaseSysCache ( aggTuple ) ;
 if ( OidIsValid ( aggref -> aggtranstype ) ) aggtranstype = aggref -> aggtranstype ;
 else {
 Oid inputTypes [ FUNC_MAX_ARGS ] ;
 int numArguments ;
 numArguments = get_aggregate_argtypes ( aggref , inputTypes ) ;
 aggtranstype = resolve_aggregate_transtype ( aggref -> aggfnoid , aggtranstype , inputTypes , numArguments ) ;
 aggref -> aggtranstype = aggtranstype ;
 }
 costs -> numAggs ++ ;
 if ( aggref -> aggorder != NIL || aggref -> aggdistinct != NIL ) {
 costs -> numOrderedAggs ++ ;
 costs -> hasNonPartial = true ;
 }
 if ( ! costs -> hasNonPartial ) {
 if ( ! OidIsValid ( aggcombinefn ) ) costs -> hasNonPartial = true ;
 else if ( aggtranstype == INTERNALOID && ( ! OidIsValid ( aggserialfn ) || ! OidIsValid ( aggdeserialfn ) ) ) costs -> hasNonSerial = true ;
 }
 if ( DO_AGGSPLIT_COMBINE ( context -> aggsplit ) ) {
 costs -> transCost . per_tuple += get_func_cost ( aggcombinefn ) * cpu_operator_cost ;
 }
 else costs -> transCost . per_tuple += get_func_cost ( aggtransfn ) * cpu_operator_cost ;
 if ( DO_AGGSPLIT_DESERIALIZE ( context -> aggsplit ) && OidIsValid ( aggdeserialfn ) ) costs -> transCost . per_tuple += get_func_cost ( aggdeserialfn ) * cpu_operator_cost ;
 if ( DO_AGGSPLIT_SERIALIZE ( context -> aggsplit ) && OidIsValid ( aggserialfn ) ) costs -> finalCost += get_func_cost ( aggserialfn ) * cpu_operator_cost ;
 if ( ! DO_AGGSPLIT_SKIPFINAL ( context -> aggsplit ) && OidIsValid ( aggfinalfn ) ) costs -> finalCost += get_func_cost ( aggfinalfn ) * cpu_operator_cost ;
 if ( ! DO_AGGSPLIT_COMBINE ( context -> aggsplit ) ) {
 cost_qual_eval_node ( & argcosts , ( Node * ) aggref -> args , context -> root ) ;
 costs -> transCost . startup += argcosts . startup ;
 costs -> transCost . per_tuple += argcosts . per_tuple ;
 if ( aggref -> aggfilter ) {
 cost_qual_eval_node ( & argcosts , ( Node * ) aggref -> aggfilter , context -> root ) ;
 costs -> transCost . startup += argcosts . startup ;
 costs -> transCost . per_tuple += argcosts . per_tuple ;
 }
 }
 if ( aggref -> aggdirectargs ) {
 cost_qual_eval_node ( & argcosts , ( Node * ) aggref -> aggdirectargs , context -> root ) ;
 costs -> transCost . startup += argcosts . startup ;
 costs -> finalCost += argcosts . per_tuple ;
 }
 if ( ! get_typbyval ( aggtranstype ) ) {
 int32 avgwidth ;
 if ( aggtransspace > 0 ) avgwidth = aggtransspace ;
 else {
 int32 aggtranstypmod = - 1 ;
 if ( aggref -> args ) {
 TargetEntry * tle = ( TargetEntry * ) linitial ( aggref -> args ) ;
 if ( aggtranstype == exprType ( ( Node * ) tle -> expr ) ) aggtranstypmod = exprTypmod ( ( Node * ) tle -> expr ) ;
 }
 avgwidth = get_typavgwidth ( aggtranstype , aggtranstypmod ) ;
 }
 avgwidth = MAXALIGN ( avgwidth ) ;
 costs -> transitionSpace += avgwidth + 2 * sizeof ( void * ) ;
 }
 else if ( aggtranstype == INTERNALOID ) {
 if ( aggtransspace > 0 ) costs -> transitionSpace += aggtransspace ;
 else costs -> transitionSpace += ALLOCSET_DEFAULT_INITSIZE ;
 }
 return false ;
 }
 Assert ( ! IsA ( node , SubLink ) ) ;
 return expression_tree_walker ( node , get_agg_clause_costs_walker , ( void * ) context ) ;
 }