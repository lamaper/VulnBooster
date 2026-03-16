static bool get_actual_variable_range ( PlannerInfo * root , VariableStatData * vardata , Oid sortop , Datum * min , Datum * max ) {
 bool have_data = false ;
 RelOptInfo * rel = vardata -> rel ;
 RangeTblEntry * rte ;
 ListCell * lc ;
 if ( rel == NULL || rel -> indexlist == NIL ) return false ;
 rte = root -> simple_rte_array [ rel -> relid ] ;
 Assert ( rte -> rtekind == RTE_RELATION ) ;
 foreach ( lc , rel -> indexlist ) {
 IndexOptInfo * index = ( IndexOptInfo * ) lfirst ( lc ) ;
 ScanDirection indexscandir ;
 if ( index -> relam != BTREE_AM_OID ) continue ;
 if ( index -> indpred != NIL ) continue ;
 if ( index -> hypothetical ) continue ;
 if ( ! match_index_to_operand ( vardata -> var , 0 , index ) ) continue ;
 switch ( get_op_opfamily_strategy ( sortop , index -> sortopfamily [ 0 ] ) ) {
 case BTLessStrategyNumber : if ( index -> reverse_sort [ 0 ] ) indexscandir = BackwardScanDirection ;
 else indexscandir = ForwardScanDirection ;
 break ;
 case BTGreaterStrategyNumber : if ( index -> reverse_sort [ 0 ] ) indexscandir = ForwardScanDirection ;
 else indexscandir = BackwardScanDirection ;
 break ;
 default : continue ;
 }
 {
 EState * estate ;
 ExprContext * econtext ;
 MemoryContext tmpcontext ;
 MemoryContext oldcontext ;
 Relation heapRel ;
 Relation indexRel ;
 IndexInfo * indexInfo ;
 TupleTableSlot * slot ;
 int16 typLen ;
 bool typByVal ;
 ScanKeyData scankeys [ 1 ] ;
 IndexScanDesc index_scan ;
 HeapTuple tup ;
 Datum values [ INDEX_MAX_KEYS ] ;
 bool isnull [ INDEX_MAX_KEYS ] ;
 SnapshotData SnapshotDirty ;
 estate = CreateExecutorState ( ) ;
 econtext = GetPerTupleExprContext ( estate ) ;
 tmpcontext = econtext -> ecxt_per_tuple_memory ;
 oldcontext = MemoryContextSwitchTo ( tmpcontext ) ;
 heapRel = heap_open ( rte -> relid , NoLock ) ;
 indexRel = index_open ( index -> indexoid , AccessShareLock ) ;
 indexInfo = BuildIndexInfo ( indexRel ) ;
 slot = MakeSingleTupleTableSlot ( RelationGetDescr ( heapRel ) ) ;
 econtext -> ecxt_scantuple = slot ;
 get_typlenbyval ( vardata -> atttype , & typLen , & typByVal ) ;
 InitDirtySnapshot ( SnapshotDirty ) ;
 ScanKeyEntryInitialize ( & scankeys [ 0 ] , SK_ISNULL | SK_SEARCHNOTNULL , 1 , InvalidStrategy , InvalidOid , InvalidOid , InvalidOid , ( Datum ) 0 ) ;
 have_data = true ;
 if ( min ) {
 index_scan = index_beginscan ( heapRel , indexRel , & SnapshotDirty , 1 , 0 ) ;
 index_rescan ( index_scan , scankeys , 1 , NULL , 0 ) ;
 if ( ( tup = index_getnext ( index_scan , indexscandir ) ) != NULL ) {
 ExecStoreTuple ( tup , slot , InvalidBuffer , false ) ;
 FormIndexDatum ( indexInfo , slot , estate , values , isnull ) ;
 if ( isnull [ 0 ] ) elog ( ERROR , "found unexpected null value in index \"%s\"" , RelationGetRelationName ( indexRel ) ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 * min = datumCopy ( values [ 0 ] , typByVal , typLen ) ;
 MemoryContextSwitchTo ( tmpcontext ) ;
 }
 else have_data = false ;
 index_endscan ( index_scan ) ;
 }
 if ( max && have_data ) {
 index_scan = index_beginscan ( heapRel , indexRel , & SnapshotDirty , 1 , 0 ) ;
 index_rescan ( index_scan , scankeys , 1 , NULL , 0 ) ;
 if ( ( tup = index_getnext ( index_scan , - indexscandir ) ) != NULL ) {
 ExecStoreTuple ( tup , slot , InvalidBuffer , false ) ;
 FormIndexDatum ( indexInfo , slot , estate , values , isnull ) ;
 if ( isnull [ 0 ] ) elog ( ERROR , "found unexpected null value in index \"%s\"" , RelationGetRelationName ( indexRel ) ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 * max = datumCopy ( values [ 0 ] , typByVal , typLen ) ;
 MemoryContextSwitchTo ( tmpcontext ) ;
 }
 else have_data = false ;
 index_endscan ( index_scan ) ;
 }
 ExecDropSingleTupleTableSlot ( slot ) ;
 index_close ( indexRel , AccessShareLock ) ;
 heap_close ( heapRel , NoLock ) ;
 MemoryContextSwitchTo ( oldcontext ) ;
 FreeExecutorState ( estate ) ;
 break ;
 }
 }
 return have_data ;
 }