double estimate_num_groups ( PlannerInfo * root , List * groupExprs , double input_rows , List * * pgset ) {
 List * varinfos = NIL ;
 double numdistinct ;
 ListCell * l ;
 int i ;
 input_rows = clamp_row_est ( input_rows ) ;
 if ( groupExprs == NIL || ( pgset && list_length ( * pgset ) < 1 ) ) return 1.0 ;
 numdistinct = 1.0 ;
 i = 0 ;
 foreach ( l , groupExprs ) {
 Node * groupexpr = ( Node * ) lfirst ( l ) ;
 VariableStatData vardata ;
 List * varshere ;
 ListCell * l2 ;
 if ( pgset && ! list_member_int ( * pgset , i ++ ) ) continue ;
 if ( exprType ( groupexpr ) == BOOLOID ) {
 numdistinct *= 2.0 ;
 continue ;
 }
 examine_variable ( root , groupexpr , 0 , & vardata ) ;
 if ( HeapTupleIsValid ( vardata . statsTuple ) || vardata . isunique ) {
 varinfos = add_unique_group_var ( root , varinfos , groupexpr , & vardata ) ;
 ReleaseVariableStats ( vardata ) ;
 continue ;
 }
 ReleaseVariableStats ( vardata ) ;
 varshere = pull_var_clause ( groupexpr , PVC_RECURSE_AGGREGATES | PVC_RECURSE_WINDOWFUNCS | PVC_RECURSE_PLACEHOLDERS ) ;
 if ( varshere == NIL ) {
 if ( contain_volatile_functions ( groupexpr ) ) return input_rows ;
 continue ;
 }
 foreach ( l2 , varshere ) {
 Node * var = ( Node * ) lfirst ( l2 ) ;
 examine_variable ( root , var , 0 , & vardata ) ;
 varinfos = add_unique_group_var ( root , varinfos , var , & vardata ) ;
 ReleaseVariableStats ( vardata ) ;
 }
 }
 if ( varinfos == NIL ) {
 if ( numdistinct > input_rows ) numdistinct = input_rows ;
 return numdistinct ;
 }
 do {
 GroupVarInfo * varinfo1 = ( GroupVarInfo * ) linitial ( varinfos ) ;
 RelOptInfo * rel = varinfo1 -> rel ;
 double reldistinct = varinfo1 -> ndistinct ;
 double relmaxndistinct = reldistinct ;
 int relvarcount = 1 ;
 List * newvarinfos = NIL ;
 for_each_cell ( l , lnext ( list_head ( varinfos ) ) ) {
 GroupVarInfo * varinfo2 = ( GroupVarInfo * ) lfirst ( l ) ;
 if ( varinfo2 -> rel == varinfo1 -> rel ) {
 reldistinct *= varinfo2 -> ndistinct ;
 if ( relmaxndistinct < varinfo2 -> ndistinct ) relmaxndistinct = varinfo2 -> ndistinct ;
 relvarcount ++ ;
 }
 else {
 newvarinfos = lcons ( varinfo2 , newvarinfos ) ;
 }
 }
 Assert ( rel -> reloptkind == RELOPT_BASEREL ) ;
 if ( rel -> tuples > 0 ) {
 double clamp = rel -> tuples ;
 if ( relvarcount > 1 ) {
 clamp *= 0.1 ;
 if ( clamp < relmaxndistinct ) {
 clamp = relmaxndistinct ;
 if ( clamp > rel -> tuples ) clamp = rel -> tuples ;
 }
 }
 if ( reldistinct > clamp ) reldistinct = clamp ;
 if ( reldistinct > 0 && rel -> rows < rel -> tuples ) {
 reldistinct *= ( 1 - pow ( ( rel -> tuples - rel -> rows ) / rel -> tuples , rel -> tuples / reldistinct ) ) ;
 }
 reldistinct = clamp_row_est ( reldistinct ) ;
 numdistinct *= reldistinct ;
 }
 varinfos = newvarinfos ;
 }
 while ( varinfos != NIL ) ;
 numdistinct = ceil ( numdistinct ) ;
 if ( numdistinct > input_rows ) numdistinct = input_rows ;
 if ( numdistinct < 1.0 ) numdistinct = 1.0 ;
 return numdistinct ;
 }