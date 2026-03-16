static Datum ExecEvalFieldStore ( FieldStoreState * fstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 FieldStore * fstore = ( FieldStore * ) fstate -> xprstate . expr ;
 HeapTuple tuple ;
 Datum tupDatum ;
 TupleDesc tupDesc ;
 Datum * values ;
 bool * isnull ;
 Datum save_datum ;
 bool save_isNull ;
 ListCell * l1 , * l2 ;
 tupDatum = ExecEvalExpr ( fstate -> arg , econtext , isNull , isDone ) ;
 if ( isDone && * isDone == ExprEndResult ) return tupDatum ;
 tupDesc = get_cached_rowtype ( fstore -> resulttype , - 1 , & fstate -> argdesc , econtext ) ;
 values = ( Datum * ) palloc ( tupDesc -> natts * sizeof ( Datum ) ) ;
 isnull = ( bool * ) palloc ( tupDesc -> natts * sizeof ( bool ) ) ;
 if ( ! * isNull ) {
 HeapTupleHeader tuphdr ;
 HeapTupleData tmptup ;
 tuphdr = DatumGetHeapTupleHeader ( tupDatum ) ;
 tmptup . t_len = HeapTupleHeaderGetDatumLength ( tuphdr ) ;
 ItemPointerSetInvalid ( & ( tmptup . t_self ) ) ;
 tmptup . t_tableOid = InvalidOid ;
 tmptup . t_data = tuphdr ;
 heap_deform_tuple ( & tmptup , tupDesc , values , isnull ) ;
 }
 else {
 memset ( isnull , true , tupDesc -> natts * sizeof ( bool ) ) ;
 }
 * isNull = false ;
 save_datum = econtext -> caseValue_datum ;
 save_isNull = econtext -> caseValue_isNull ;
 forboth ( l1 , fstate -> newvals , l2 , fstore -> fieldnums ) {
 ExprState * newval = ( ExprState * ) lfirst ( l1 ) ;
 AttrNumber fieldnum = lfirst_int ( l2 ) ;
 Assert ( fieldnum > 0 && fieldnum <= tupDesc -> natts ) ;
 econtext -> caseValue_datum = values [ fieldnum - 1 ] ;
 econtext -> caseValue_isNull = isnull [ fieldnum - 1 ] ;
 values [ fieldnum - 1 ] = ExecEvalExpr ( newval , econtext , & isnull [ fieldnum - 1 ] , NULL ) ;
 }
 econtext -> caseValue_datum = save_datum ;
 econtext -> caseValue_isNull = save_isNull ;
 tuple = heap_form_tuple ( tupDesc , values , isnull ) ;
 pfree ( values ) ;
 pfree ( isnull ) ;
 return HeapTupleGetDatum ( tuple ) ;
 }