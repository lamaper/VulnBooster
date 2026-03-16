static Datum ExecEvalScalarArrayOp ( ScalarArrayOpExprState * sstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 ScalarArrayOpExpr * opexpr = ( ScalarArrayOpExpr * ) sstate -> fxprstate . xprstate . expr ;
 bool useOr = opexpr -> useOr ;
 ArrayType * arr ;
 int nitems ;
 Datum result ;
 bool resultnull ;
 FunctionCallInfo fcinfo ;
 ExprDoneCond argDone ;
 int i ;
 int16 typlen ;
 bool typbyval ;
 char typalign ;
 char * s ;
 bits8 * bitmap ;
 int bitmask ;
 * isNull = false ;
 if ( isDone ) * isDone = ExprSingleResult ;
 if ( sstate -> fxprstate . func . fn_oid == InvalidOid ) {
 init_fcache ( opexpr -> opfuncid , opexpr -> inputcollid , & sstate -> fxprstate , econtext -> ecxt_per_query_memory , true ) ;
 Assert ( ! sstate -> fxprstate . func . fn_retset ) ;
 }
 fcinfo = & sstate -> fxprstate . fcinfo_data ;
 argDone = ExecEvalFuncArgs ( fcinfo , sstate -> fxprstate . args , econtext ) ;
 if ( argDone != ExprSingleResult ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "op ANY/ALL (array) does not support set arguments" ) ) ) ;
 Assert ( fcinfo -> nargs == 2 ) ;
 if ( fcinfo -> argnull [ 1 ] ) {
 * isNull = true ;
 return ( Datum ) 0 ;
 }
 arr = DatumGetArrayTypeP ( fcinfo -> arg [ 1 ] ) ;
 nitems = ArrayGetNItems ( ARR_NDIM ( arr ) , ARR_DIMS ( arr ) ) ;
 if ( nitems <= 0 ) return BoolGetDatum ( ! useOr ) ;
 if ( fcinfo -> argnull [ 0 ] && sstate -> fxprstate . func . fn_strict ) {
 * isNull = true ;
 return ( Datum ) 0 ;
 }
 if ( sstate -> element_type != ARR_ELEMTYPE ( arr ) ) {
 get_typlenbyvalalign ( ARR_ELEMTYPE ( arr ) , & sstate -> typlen , & sstate -> typbyval , & sstate -> typalign ) ;
 sstate -> element_type = ARR_ELEMTYPE ( arr ) ;
 }
 typlen = sstate -> typlen ;
 typbyval = sstate -> typbyval ;
 typalign = sstate -> typalign ;
 result = BoolGetDatum ( ! useOr ) ;
 resultnull = false ;
 s = ( char * ) ARR_DATA_PTR ( arr ) ;
 bitmap = ARR_NULLBITMAP ( arr ) ;
 bitmask = 1 ;
 for ( i = 0 ;
 i < nitems ;
 i ++ ) {
 Datum elt ;
 Datum thisresult ;
 if ( bitmap && ( * bitmap & bitmask ) == 0 ) {
 fcinfo -> arg [ 1 ] = ( Datum ) 0 ;
 fcinfo -> argnull [ 1 ] = true ;
 }
 else {
 elt = fetch_att ( s , typbyval , typlen ) ;
 s = att_addlength_pointer ( s , typlen , s ) ;
 s = ( char * ) att_align_nominal ( s , typalign ) ;
 fcinfo -> arg [ 1 ] = elt ;
 fcinfo -> argnull [ 1 ] = false ;
 }
 if ( fcinfo -> argnull [ 1 ] && sstate -> fxprstate . func . fn_strict ) {
 fcinfo -> isnull = true ;
 thisresult = ( Datum ) 0 ;
 }
 else {
 fcinfo -> isnull = false ;
 thisresult = FunctionCallInvoke ( fcinfo ) ;
 }
 if ( fcinfo -> isnull ) resultnull = true ;
 else if ( useOr ) {
 if ( DatumGetBool ( thisresult ) ) {
 result = BoolGetDatum ( true ) ;
 resultnull = false ;
 break ;
 }
 }
 else {
 if ( ! DatumGetBool ( thisresult ) ) {
 result = BoolGetDatum ( false ) ;
 resultnull = false ;
 break ;
 }
 }
 if ( bitmap ) {
 bitmask <<= 1 ;
 if ( bitmask == 0x100 ) {
 bitmap ++ ;
 bitmask = 1 ;
 }
 }
 }
 * isNull = resultnull ;
 return result ;
 }