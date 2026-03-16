void brincostestimate ( PlannerInfo * root , IndexPath * path , double loop_count , Cost * indexStartupCost , Cost * indexTotalCost , Selectivity * indexSelectivity , double * indexCorrelation ) {
 IndexOptInfo * index = path -> indexinfo ;
 List * indexQuals = path -> indexquals ;
 List * indexOrderBys = path -> indexorderbys ;
 double numPages = index -> pages ;
 double numTuples = index -> tuples ;
 List * qinfos ;
 Cost spc_seq_page_cost ;
 Cost spc_random_page_cost ;
 double qual_op_cost ;
 double qual_arg_cost ;
 qinfos = deconstruct_indexquals ( path ) ;
 get_tablespace_page_costs ( index -> reltablespace , & spc_random_page_cost , & spc_seq_page_cost ) ;
 * indexStartupCost = spc_seq_page_cost * numPages * loop_count ;
 * indexTotalCost = spc_random_page_cost * numPages * loop_count ;
 * indexSelectivity = clauselist_selectivity ( root , indexQuals , path -> indexinfo -> rel -> relid , JOIN_INNER , NULL ) ;
 * indexCorrelation = 1 ;
 qual_arg_cost = other_operands_eval_cost ( root , qinfos ) + orderby_operands_eval_cost ( root , path ) ;
 qual_op_cost = cpu_operator_cost * ( list_length ( indexQuals ) + list_length ( indexOrderBys ) ) ;
 * indexStartupCost += qual_arg_cost ;
 * indexTotalCost += qual_arg_cost ;
 * indexTotalCost += ( numTuples * * indexSelectivity ) * ( cpu_index_tuple_cost + qual_op_cost ) ;
 }