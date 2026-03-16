void btcostestimate ( PlannerInfo * root , IndexPath * path , double loop_count , Cost * indexStartupCost , Cost * indexTotalCost , Selectivity * indexSelectivity , double * indexCorrelation ) {
 IndexOptInfo * index = path -> indexinfo ;
 List * qinfos ;
 GenericCosts costs ;
 Oid relid ;
 AttrNumber colnum ;
 VariableStatData vardata ;
 double numIndexTuples ;
 Cost descentCost ;
 List * indexBoundQuals ;
 int indexcol ;
 bool eqQualHere ;
 bool found_saop ;
 bool found_is_null_op ;
 double num_sa_scans ;
 ListCell * lc ;
 qinfos = deconstruct_indexquals ( path ) ;
 indexBoundQuals = NIL ;
 indexcol = 0 ;
 eqQualHere = false ;
 found_saop = false ;
 found_is_null_op = false ;
 num_sa_scans = 1 ;
 foreach ( lc , qinfos ) {
 IndexQualInfo * qinfo = ( IndexQualInfo * ) lfirst ( lc ) ;
 RestrictInfo * rinfo = qinfo -> rinfo ;
 Expr * clause = rinfo -> clause ;
 Oid clause_op ;
 int op_strategy ;
 if ( indexcol != qinfo -> indexcol ) {
 if ( ! eqQualHere ) break ;
 eqQualHere = false ;
 indexcol ++ ;
 if ( indexcol != qinfo -> indexcol ) break ;
 }
 if ( IsA ( clause , ScalarArrayOpExpr ) ) {
 int alength = estimate_array_length ( qinfo -> other_operand ) ;
 found_saop = true ;
 if ( alength > 1 ) num_sa_scans *= alength ;
 }
 else if ( IsA ( clause , NullTest ) ) {
 NullTest * nt = ( NullTest * ) clause ;
 if ( nt -> nulltesttype == IS_NULL ) {
 found_is_null_op = true ;
 eqQualHere = true ;
 }
 }
 clause_op = qinfo -> clause_op ;
 if ( OidIsValid ( clause_op ) ) {
 op_strategy = get_op_opfamily_strategy ( clause_op , index -> opfamily [ indexcol ] ) ;
 Assert ( op_strategy != 0 ) ;
 if ( op_strategy == BTEqualStrategyNumber ) eqQualHere = true ;
 }
 indexBoundQuals = lappend ( indexBoundQuals , rinfo ) ;
 }
 if ( index -> unique && indexcol == index -> ncolumns - 1 && eqQualHere && ! found_saop && ! found_is_null_op ) numIndexTuples = 1.0 ;
 else {
 List * selectivityQuals ;
 Selectivity btreeSelectivity ;
 selectivityQuals = add_predicate_to_quals ( index , indexBoundQuals ) ;
 btreeSelectivity = clauselist_selectivity ( root , selectivityQuals , index -> rel -> relid , JOIN_INNER , NULL ) ;
 numIndexTuples = btreeSelectivity * index -> rel -> tuples ;
 numIndexTuples = rint ( numIndexTuples / num_sa_scans ) ;
 }
 MemSet ( & costs , 0 , sizeof ( costs ) ) ;
 costs . numIndexTuples = numIndexTuples ;
 genericcostestimate ( root , path , loop_count , qinfos , & costs ) ;
 if ( index -> tuples > 1 ) {
 descentCost = ceil ( log ( index -> tuples ) / log ( 2.0 ) ) * cpu_operator_cost ;
 costs . indexStartupCost += descentCost ;
 costs . indexTotalCost += costs . num_sa_scans * descentCost ;
 }
 descentCost = ( index -> tree_height + 1 ) * 50.0 * cpu_operator_cost ;
 costs . indexStartupCost += descentCost ;
 costs . indexTotalCost += costs . num_sa_scans * descentCost ;
 MemSet ( & vardata , 0 , sizeof ( vardata ) ) ;
 if ( index -> indexkeys [ 0 ] != 0 ) {
 RangeTblEntry * rte = planner_rt_fetch ( index -> rel -> relid , root ) ;
 Assert ( rte -> rtekind == RTE_RELATION ) ;
 relid = rte -> relid ;
 Assert ( relid != InvalidOid ) ;
 colnum = index -> indexkeys [ 0 ] ;
 if ( get_relation_stats_hook && ( * get_relation_stats_hook ) ( root , rte , colnum , & vardata ) ) {
 if ( HeapTupleIsValid ( vardata . statsTuple ) && ! vardata . freefunc ) elog ( ERROR , "no function provided to release variable stats with" ) ;
 }
 else {
 vardata . statsTuple = SearchSysCache3 ( STATRELATTINH , ObjectIdGetDatum ( relid ) , Int16GetDatum ( colnum ) , BoolGetDatum ( rte -> inh ) ) ;
 vardata . freefunc = ReleaseSysCache ;
 }
 }
 else {
 relid = index -> indexoid ;
 colnum = 1 ;
 if ( get_index_stats_hook && ( * get_index_stats_hook ) ( root , relid , colnum , & vardata ) ) {
 if ( HeapTupleIsValid ( vardata . statsTuple ) && ! vardata . freefunc ) elog ( ERROR , "no function provided to release variable stats with" ) ;
 }
 else {
 vardata . statsTuple = SearchSysCache3 ( STATRELATTINH , ObjectIdGetDatum ( relid ) , Int16GetDatum ( colnum ) , BoolGetDatum ( false ) ) ;
 vardata . freefunc = ReleaseSysCache ;
 }
 }
 if ( HeapTupleIsValid ( vardata . statsTuple ) ) {
 Oid sortop ;
 float4 * numbers ;
 int nnumbers ;
 sortop = get_opfamily_member ( index -> opfamily [ 0 ] , index -> opcintype [ 0 ] , index -> opcintype [ 0 ] , BTLessStrategyNumber ) ;
 if ( OidIsValid ( sortop ) && get_attstatsslot ( vardata . statsTuple , InvalidOid , 0 , STATISTIC_KIND_CORRELATION , sortop , NULL , NULL , NULL , & numbers , & nnumbers ) ) {
 double varCorrelation ;
 Assert ( nnumbers == 1 ) ;
 varCorrelation = numbers [ 0 ] ;
 if ( index -> reverse_sort [ 0 ] ) varCorrelation = - varCorrelation ;
 if ( index -> ncolumns > 1 ) costs . indexCorrelation = varCorrelation * 0.75 ;
 else costs . indexCorrelation = varCorrelation ;
 free_attstatsslot ( InvalidOid , NULL , 0 , numbers , nnumbers ) ;
 }
 }
 ReleaseVariableStats ( vardata ) ;
 * indexStartupCost = costs . indexStartupCost ;
 * indexTotalCost = costs . indexTotalCost ;
 * indexSelectivity = costs . indexSelectivity ;
 * indexCorrelation = costs . indexCorrelation ;
 }