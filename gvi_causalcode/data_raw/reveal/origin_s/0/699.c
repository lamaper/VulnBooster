void gistcostestimate ( PlannerInfo * root , IndexPath * path , double loop_count , Cost * indexStartupCost , Cost * indexTotalCost , Selectivity * indexSelectivity , double * indexCorrelation ) {
 IndexOptInfo * index = path -> indexinfo ;
 List * qinfos ;
 GenericCosts costs ;
 Cost descentCost ;
 qinfos = deconstruct_indexquals ( path ) ;
 MemSet ( & costs , 0 , sizeof ( costs ) ) ;
 genericcostestimate ( root , path , loop_count , qinfos , & costs ) ;
 if ( index -> tree_height < 0 ) {
 if ( index -> pages > 1 ) index -> tree_height = ( int ) ( log ( index -> pages ) / log ( 100.0 ) ) ;
 else index -> tree_height = 0 ;
 }
 if ( index -> tuples > 1 ) {
 descentCost = ceil ( log ( index -> tuples ) ) * cpu_operator_cost ;
 costs . indexStartupCost += descentCost ;
 costs . indexTotalCost += costs . num_sa_scans * descentCost ;
 }
 descentCost = ( index -> tree_height + 1 ) * 50.0 * cpu_operator_cost ;
 costs . indexStartupCost += descentCost ;
 costs . indexTotalCost += costs . num_sa_scans * descentCost ;
 * indexStartupCost = costs . indexStartupCost ;
 * indexTotalCost = costs . indexTotalCost ;
 * indexSelectivity = costs . indexSelectivity ;
 * indexCorrelation = costs . indexCorrelation ;
 }