static Datum ExecEvalFieldSelect ( FieldSelectState * fstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 FieldSelect * fselect = ( FieldSelect * ) fstate -> xprstate . expr ;
 AttrNumber fieldnum = fselect -> fieldnum ;
 Datum result ;
 Datum tupDatum ;
 HeapTupleHeader tuple ;
 Oid tupType ;
 int32 tupTypmod ;
 TupleDesc tupDesc ;
 Form_pg_attribute attr ;
 HeapTupleData tmptup ;
 tupDatum = ExecEvalExpr ( fstate -> arg , econtext , isNull , isDone ) ;
 if ( * isNull ) return tupDatum ;
 tuple = DatumGetHeapTupleHeader ( tupDatum ) ;
 tupType = HeapTupleHeaderGetTypeId ( tuple ) ;
 tupTypmod = HeapTupleHeaderGetTypMod ( tuple ) ;
 tupDesc = get_cached_rowtype ( tupType , tupTypmod , & fstate -> argdesc , econtext ) ;
 if ( fieldnum <= 0 ) elog ( ERROR , "unsupported reference to system column %d in FieldSelect" , fieldnum ) ;
 if ( fieldnum > tupDesc -> natts ) elog ( ERROR , "attribute number %d exceeds number of columns %d" , fieldnum , tupDesc -> natts ) ;
 attr = tupDesc -> attrs [ fieldnum - 1 ] ;
 if ( attr -> attisdropped ) {
 * isNull = true ;
 return ( Datum ) 0 ;
 }
 if ( fselect -> resulttype != attr -> atttypid ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "attribute %d has wrong type" , fieldnum ) , errdetail ( "Table has type %s, but query expects %s." , format_type_be ( attr -> atttypid ) , format_type_be ( fselect -> resulttype ) ) ) ) ;
 tmptup . t_len = HeapTupleHeaderGetDatumLength ( tuple ) ;
 tmptup . t_data = tuple ;
 result = heap_getattr ( & tmptup , fieldnum , tupDesc , isNull ) ;
 return result ;
 }