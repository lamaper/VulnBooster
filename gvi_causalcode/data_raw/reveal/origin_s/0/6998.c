static bool gincost_pattern ( IndexOptInfo * index , int indexcol , Oid clause_op , Datum query , GinQualCounts * counts ) {
 Oid extractProcOid ;
 Oid collation ;
 int strategy_op ;
 Oid lefttype , righttype ;
 int32 nentries = 0 ;
 bool * partial_matches = NULL ;
 Pointer * extra_data = NULL ;
 bool * nullFlags = NULL ;
 int32 searchMode = GIN_SEARCH_MODE_DEFAULT ;
 int32 i ;
 get_op_opfamily_properties ( clause_op , index -> opfamily [ indexcol ] , false , & strategy_op , & lefttype , & righttype ) ;
 extractProcOid = get_opfamily_proc ( index -> opfamily [ indexcol ] , index -> opcintype [ indexcol ] , index -> opcintype [ indexcol ] , GIN_EXTRACTQUERY_PROC ) ;
 if ( ! OidIsValid ( extractProcOid ) ) {
 elog ( ERROR , "missing support function %d for attribute %d of index \"%s\"" , GIN_EXTRACTQUERY_PROC , indexcol + 1 , get_rel_name ( index -> indexoid ) ) ;
 }
 if ( OidIsValid ( index -> indexcollations [ indexcol ] ) ) collation = index -> indexcollations [ indexcol ] ;
 else collation = DEFAULT_COLLATION_OID ;
 OidFunctionCall7Coll ( extractProcOid , collation , query , PointerGetDatum ( & nentries ) , UInt16GetDatum ( strategy_op ) , PointerGetDatum ( & partial_matches ) , PointerGetDatum ( & extra_data ) , PointerGetDatum ( & nullFlags ) , PointerGetDatum ( & searchMode ) ) ;
 if ( nentries <= 0 && searchMode == GIN_SEARCH_MODE_DEFAULT ) {
 return false ;
 }
 for ( i = 0 ;
 i < nentries ;
 i ++ ) {
 if ( partial_matches && partial_matches [ i ] ) counts -> partialEntries += 100 ;
 else counts -> exactEntries ++ ;
 counts -> searchEntries ++ ;
 }
 if ( searchMode == GIN_SEARCH_MODE_INCLUDE_EMPTY ) {
 counts -> exactEntries ++ ;
 counts -> searchEntries ++ ;
 }
 else if ( searchMode != GIN_SEARCH_MODE_DEFAULT ) {
 counts -> haveFullScan = true ;
 }
 return true ;
 }