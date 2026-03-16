static Datum ExecEvalConvertRowtype ( ConvertRowtypeExprState * cstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 ConvertRowtypeExpr * convert = ( ConvertRowtypeExpr * ) cstate -> xprstate . expr ;
 HeapTuple result ;
 Datum tupDatum ;
 HeapTupleHeader tuple ;
 HeapTupleData tmptup ;
 tupDatum = ExecEvalExpr ( cstate -> arg , econtext , isNull , isDone ) ;
 if ( * isNull ) return tupDatum ;
 tuple = DatumGetHeapTupleHeader ( tupDatum ) ;
 if ( cstate -> indesc == NULL ) {
 get_cached_rowtype ( exprType ( ( Node * ) convert -> arg ) , - 1 , & cstate -> indesc , econtext ) ;
 cstate -> initialized = false ;
 }
 if ( cstate -> outdesc == NULL ) {
 get_cached_rowtype ( convert -> resulttype , - 1 , & cstate -> outdesc , econtext ) ;
 cstate -> initialized = false ;
 }
 Assert ( HeapTupleHeaderGetTypeId ( tuple ) == cstate -> indesc -> tdtypeid || HeapTupleHeaderGetTypeId ( tuple ) == RECORDOID ) ;
 if ( ! cstate -> initialized ) {
 MemoryContext old_cxt ;
 old_cxt = MemoryContextSwitchTo ( econtext -> ecxt_per_query_memory ) ;
 cstate -> map = convert_tuples_by_name ( cstate -> indesc , cstate -> outdesc , gettext_noop ( "could not convert row type" ) ) ;
 cstate -> initialized = true ;
 MemoryContextSwitchTo ( old_cxt ) ;
 }
 if ( cstate -> map == NULL ) return tupDatum ;
 tmptup . t_len = HeapTupleHeaderGetDatumLength ( tuple ) ;
 tmptup . t_data = tuple ;
 result = do_convert_tuple ( & tmptup , cstate -> map ) ;
 return HeapTupleGetDatum ( result ) ;
 }