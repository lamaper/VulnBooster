static bool expression_returns_set_rows_walker ( Node * node , double * count ) {
 if ( node == NULL ) return false ;
 if ( IsA ( node , FuncExpr ) ) {
 FuncExpr * expr = ( FuncExpr * ) node ;
 if ( expr -> funcretset ) * count *= get_func_rows ( expr -> funcid ) ;
 }
 if ( IsA ( node , OpExpr ) ) {
 OpExpr * expr = ( OpExpr * ) node ;
 if ( expr -> opretset ) {
 set_opfuncid ( expr ) ;
 * count *= get_func_rows ( expr -> opfuncid ) ;
 }
 }
 if ( IsA ( node , Aggref ) ) return false ;
 if ( IsA ( node , WindowFunc ) ) return false ;
 if ( IsA ( node , DistinctExpr ) ) return false ;
 if ( IsA ( node , NullIfExpr ) ) return false ;
 if ( IsA ( node , ScalarArrayOpExpr ) ) return false ;
 if ( IsA ( node , BoolExpr ) ) return false ;
 if ( IsA ( node , SubLink ) ) return false ;
 if ( IsA ( node , SubPlan ) ) return false ;
 if ( IsA ( node , AlternativeSubPlan ) ) return false ;
 if ( IsA ( node , ArrayExpr ) ) return false ;
 if ( IsA ( node , RowExpr ) ) return false ;
 if ( IsA ( node , RowCompareExpr ) ) return false ;
 if ( IsA ( node , CoalesceExpr ) ) return false ;
 if ( IsA ( node , MinMaxExpr ) ) return false ;
 if ( IsA ( node , XmlExpr ) ) return false ;
 return expression_tree_walker ( node , expression_returns_set_rows_walker , ( void * ) count ) ;
 }