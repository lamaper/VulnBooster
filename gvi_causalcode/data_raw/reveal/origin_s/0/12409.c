static Datum ExecEvalNullTest ( NullTestState * nstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 NullTest * ntest = ( NullTest * ) nstate -> xprstate . expr ;
 Datum result ;
 result = ExecEvalExpr ( nstate -> arg , econtext , isNull , isDone ) ;
 if ( isDone && * isDone == ExprEndResult ) return result ;
 if ( ntest -> argisrow && ! ( * isNull ) ) {
 HeapTupleHeader tuple ;
 Oid tupType ;
 int32 tupTypmod ;
 TupleDesc tupDesc ;
 HeapTupleData tmptup ;
 int att ;
 tuple = DatumGetHeapTupleHeader ( result ) ;
 tupType = HeapTupleHeaderGetTypeId ( tuple ) ;
 tupTypmod = HeapTupleHeaderGetTypMod ( tuple ) ;
 tupDesc = get_cached_rowtype ( tupType , tupTypmod , & nstate -> argdesc , econtext ) ;
 tmptup . t_len = HeapTupleHeaderGetDatumLength ( tuple ) ;
 tmptup . t_data = tuple ;
 for ( att = 1 ;
 att <= tupDesc -> natts ;
 att ++ ) {
 if ( tupDesc -> attrs [ att - 1 ] -> attisdropped ) continue ;
 if ( heap_attisnull ( & tmptup , att ) ) {
 if ( ntest -> nulltesttype == IS_NOT_NULL ) return BoolGetDatum ( false ) ;
 }
 else {
 if ( ntest -> nulltesttype == IS_NULL ) return BoolGetDatum ( false ) ;
 }
 }
 return BoolGetDatum ( true ) ;
 }
 else {
 switch ( ntest -> nulltesttype ) {
 case IS_NULL : if ( * isNull ) {
 * isNull = false ;
 return BoolGetDatum ( true ) ;
 }
 else return BoolGetDatum ( false ) ;
 case IS_NOT_NULL : if ( * isNull ) {
 * isNull = false ;
 return BoolGetDatum ( false ) ;
 }
 else return BoolGetDatum ( true ) ;
 default : elog ( ERROR , "unrecognized nulltesttype: %d" , ( int ) ntest -> nulltesttype ) ;
 return ( Datum ) 0 ;
 }
 }
 }