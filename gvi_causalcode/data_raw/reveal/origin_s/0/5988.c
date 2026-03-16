void gincostestimate ( PlannerInfo * root , IndexPath * path , double loop_count , Cost * indexStartupCost , Cost * indexTotalCost , Selectivity * indexSelectivity , double * indexCorrelation ) {
 IndexOptInfo * index = path -> indexinfo ;
 List * indexQuals = path -> indexquals ;
 List * indexOrderBys = path -> indexorderbys ;
 List * qinfos ;
 ListCell * l ;
 List * selectivityQuals ;
 double numPages = index -> pages , numTuples = index -> tuples ;
 double numEntryPages , numDataPages , numPendingPages , numEntries ;
 GinQualCounts counts ;
 bool matchPossible ;
 double partialScale ;
 double entryPagesFetched , dataPagesFetched , dataPagesFetchedBySel ;
 double qual_op_cost , qual_arg_cost , spc_random_page_cost , outer_scans ;
 Relation indexRel ;
 GinStatsData ginStats ;
 qinfos = deconstruct_indexquals ( path ) ;
 if ( ! index -> hypothetical ) {
 indexRel = index_open ( index -> indexoid , AccessShareLock ) ;
 ginGetStats ( indexRel , & ginStats ) ;
 index_close ( indexRel , AccessShareLock ) ;
 }
 else {
 memset ( & ginStats , 0 , sizeof ( ginStats ) ) ;
 }
 if ( ginStats . nPendingPages < numPages ) numPendingPages = ginStats . nPendingPages ;
 else numPendingPages = 0 ;
 if ( numPages > 0 && ginStats . nTotalPages <= numPages && ginStats . nTotalPages > numPages / 4 && ginStats . nEntryPages > 0 && ginStats . nEntries > 0 ) {
 double scale = numPages / ginStats . nTotalPages ;
 numEntryPages = ceil ( ginStats . nEntryPages * scale ) ;
 numDataPages = ceil ( ginStats . nDataPages * scale ) ;
 numEntries = ceil ( ginStats . nEntries * scale ) ;
 numEntryPages = Min ( numEntryPages , numPages - numPendingPages ) ;
 numDataPages = Min ( numDataPages , numPages - numPendingPages - numEntryPages ) ;
 }
 else {
 numPages = Max ( numPages , 10 ) ;
 numEntryPages = floor ( ( numPages - numPendingPages ) * 0.90 ) ;
 numDataPages = numPages - numPendingPages - numEntryPages ;
 numEntries = floor ( numEntryPages * 100 ) ;
 }
 if ( numEntries < 1 ) numEntries = 1 ;
 if ( index -> indpred != NIL ) {
 List * predExtraQuals = NIL ;
 foreach ( l , index -> indpred ) {
 Node * predQual = ( Node * ) lfirst ( l ) ;
 List * oneQual = list_make1 ( predQual ) ;
 if ( ! predicate_implied_by ( oneQual , indexQuals ) ) predExtraQuals = list_concat ( predExtraQuals , oneQual ) ;
 }
 selectivityQuals = list_concat ( predExtraQuals , indexQuals ) ;
 }
 else selectivityQuals = indexQuals ;
 * indexSelectivity = clauselist_selectivity ( root , selectivityQuals , index -> rel -> relid , JOIN_INNER , NULL ) ;
 get_tablespace_page_costs ( index -> reltablespace , & spc_random_page_cost , NULL ) ;
 * indexCorrelation = 0.0 ;
 memset ( & counts , 0 , sizeof ( counts ) ) ;
 counts . arrayScans = 1 ;
 matchPossible = true ;
 foreach ( l , qinfos ) {
 IndexQualInfo * qinfo = ( IndexQualInfo * ) lfirst ( l ) ;
 Expr * clause = qinfo -> rinfo -> clause ;
 if ( IsA ( clause , OpExpr ) ) {
 matchPossible = gincost_opexpr ( root , index , qinfo , & counts ) ;
 if ( ! matchPossible ) break ;
 }
 else if ( IsA ( clause , ScalarArrayOpExpr ) ) {
 matchPossible = gincost_scalararrayopexpr ( root , index , qinfo , numEntries , & counts ) ;
 if ( ! matchPossible ) break ;
 }
 else {
 elog ( ERROR , "unsupported GIN indexqual type: %d" , ( int ) nodeTag ( clause ) ) ;
 }
 }
 if ( ! matchPossible ) {
 * indexStartupCost = 0 ;
 * indexTotalCost = 0 ;
 * indexSelectivity = 0 ;
 return ;
 }
 if ( counts . haveFullScan || indexQuals == NIL ) {
 counts . partialEntries = 0 ;
 counts . exactEntries = numEntries ;
 counts . searchEntries = numEntries ;
 }
 outer_scans = loop_count ;
 entryPagesFetched = numPendingPages ;
 entryPagesFetched += ceil ( counts . searchEntries * rint ( pow ( numEntryPages , 0.15 ) ) ) ;
 partialScale = counts . partialEntries / numEntries ;
 partialScale = Min ( partialScale , 1.0 ) ;
 entryPagesFetched += ceil ( numEntryPages * partialScale ) ;
 dataPagesFetched = ceil ( numDataPages * partialScale ) ;
 if ( outer_scans > 1 || counts . arrayScans > 1 ) {
 entryPagesFetched *= outer_scans * counts . arrayScans ;
 entryPagesFetched = index_pages_fetched ( entryPagesFetched , ( BlockNumber ) numEntryPages , numEntryPages , root ) ;
 entryPagesFetched /= outer_scans ;
 dataPagesFetched *= outer_scans * counts . arrayScans ;
 dataPagesFetched = index_pages_fetched ( dataPagesFetched , ( BlockNumber ) numDataPages , numDataPages , root ) ;
 dataPagesFetched /= outer_scans ;
 }
 * indexStartupCost = ( entryPagesFetched + dataPagesFetched ) * spc_random_page_cost ;
 dataPagesFetched = ceil ( numDataPages * counts . exactEntries / numEntries ) ;
 dataPagesFetchedBySel = ceil ( * indexSelectivity * ( numTuples / ( BLCKSZ / 3 ) ) ) ;
 if ( dataPagesFetchedBySel > dataPagesFetched ) dataPagesFetched = dataPagesFetchedBySel ;
 if ( outer_scans > 1 || counts . arrayScans > 1 ) {
 dataPagesFetched *= outer_scans * counts . arrayScans ;
 dataPagesFetched = index_pages_fetched ( dataPagesFetched , ( BlockNumber ) numDataPages , numDataPages , root ) ;
 dataPagesFetched /= outer_scans ;
 }
 * indexTotalCost = * indexStartupCost + dataPagesFetched * spc_random_page_cost ;
 qual_arg_cost = other_operands_eval_cost ( root , qinfos ) + orderby_operands_eval_cost ( root , path ) ;
 qual_op_cost = cpu_operator_cost * ( list_length ( indexQuals ) + list_length ( indexOrderBys ) ) ;
 * indexStartupCost += qual_arg_cost ;
 * indexTotalCost += qual_arg_cost ;
 * indexTotalCost += ( numTuples * * indexSelectivity ) * ( cpu_index_tuple_cost + qual_op_cost ) ;
 }