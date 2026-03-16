void hashcostestimate ( PlannerInfo * root , IndexPath * path , double loop_count , Cost * indexStartupCost , Cost * indexTotalCost , Selectivity * indexSelectivity , double * indexCorrelation ) {
 List * qinfos ;
 GenericCosts costs ;
 qinfos = deconstruct_indexquals ( path ) ;
 MemSet ( & costs , 0 , sizeof ( costs ) ) ;
 genericcostestimate ( root , path , loop_count , qinfos , & costs ) ;
 * indexStartupCost = costs . indexStartupCost ;
 * indexTotalCost = costs . indexTotalCost ;
 * indexSelectivity = costs . indexSelectivity ;
 * indexCorrelation = costs . indexCorrelation ;
 }