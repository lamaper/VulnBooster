void genericcostestimate ( PlannerInfo * root , IndexPath * path , double loop_count , List * qinfos , GenericCosts * costs ) {
 IndexOptInfo * index = path -> indexinfo ;
 List * indexQuals = path -> indexquals ;
 List * indexOrderBys = path -> indexorderbys ;
 Cost indexStartupCost ;
 Cost indexTotalCost ;
 Selectivity indexSelectivity ;
 double indexCorrelation ;
 double numIndexPages ;
 double numIndexTuples ;
 double spc_random_page_cost ;
 double num_sa_scans ;
 double num_outer_scans ;
 double num_scans ;
 double qual_op_cost ;
 double qual_arg_cost ;
 List * selectivityQuals ;
 ListCell * l ;
 selectivityQuals = add_predicate_to_quals ( index , indexQuals ) ;
 num_sa_scans = 1 ;
 foreach ( l , indexQuals ) {
 RestrictInfo * rinfo = ( RestrictInfo * ) lfirst ( l ) ;
 if ( IsA ( rinfo -> clause , ScalarArrayOpExpr ) ) {
 ScalarArrayOpExpr * saop = ( ScalarArrayOpExpr * ) rinfo -> clause ;
 int alength = estimate_array_length ( lsecond ( saop -> args ) ) ;
 if ( alength > 1 ) num_sa_scans *= alength ;
 }
 }
 indexSelectivity = clauselist_selectivity ( root , selectivityQuals , index -> rel -> relid , JOIN_INNER , NULL ) ;
 numIndexTuples = costs -> numIndexTuples ;
 if ( numIndexTuples <= 0.0 ) {
 numIndexTuples = indexSelectivity * index -> rel -> tuples ;
 numIndexTuples = rint ( numIndexTuples / num_sa_scans ) ;
 }
 if ( numIndexTuples > index -> tuples ) numIndexTuples = index -> tuples ;
 if ( numIndexTuples < 1.0 ) numIndexTuples = 1.0 ;
 if ( index -> pages > 1 && index -> tuples > 1 ) numIndexPages = ceil ( numIndexTuples * index -> pages / index -> tuples ) ;
 else numIndexPages = 1.0 ;
 get_tablespace_page_costs ( index -> reltablespace , & spc_random_page_cost , NULL ) ;
 num_outer_scans = loop_count ;
 num_scans = num_sa_scans * num_outer_scans ;
 if ( num_scans > 1 ) {
 double pages_fetched ;
 pages_fetched = numIndexPages * num_scans ;
 pages_fetched = index_pages_fetched ( pages_fetched , index -> pages , ( double ) index -> pages , root ) ;
 indexTotalCost = ( pages_fetched * spc_random_page_cost ) / num_outer_scans ;
 }
 else {
 indexTotalCost = numIndexPages * spc_random_page_cost ;
 }
 qual_arg_cost = other_operands_eval_cost ( root , qinfos ) + orderby_operands_eval_cost ( root , path ) ;
 qual_op_cost = cpu_operator_cost * ( list_length ( indexQuals ) + list_length ( indexOrderBys ) ) ;
 indexStartupCost = qual_arg_cost ;
 indexTotalCost += qual_arg_cost ;
 indexTotalCost += numIndexTuples * num_sa_scans * ( cpu_index_tuple_cost + qual_op_cost ) ;
 indexCorrelation = 0.0 ;
 costs -> indexStartupCost = indexStartupCost ;
 costs -> indexTotalCost = indexTotalCost ;
 costs -> indexSelectivity = indexSelectivity ;
 costs -> indexCorrelation = indexCorrelation ;
 costs -> numIndexPages = numIndexPages ;
 costs -> numIndexTuples = numIndexTuples ;
 costs -> spc_random_page_cost = spc_random_page_cost ;
 costs -> num_sa_scans = num_sa_scans ;
 }