static Datum ExecEvalBooleanTest ( GenericExprState * bstate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 BooleanTest * btest = ( BooleanTest * ) bstate -> xprstate . expr ;
 Datum result ;
 result = ExecEvalExpr ( bstate -> arg , econtext , isNull , isDone ) ;
 if ( isDone && * isDone == ExprEndResult ) return result ;
 switch ( btest -> booltesttype ) {
 case IS_TRUE : if ( * isNull ) {
 * isNull = false ;
 return BoolGetDatum ( false ) ;
 }
 else if ( DatumGetBool ( result ) ) return BoolGetDatum ( true ) ;
 else return BoolGetDatum ( false ) ;
 case IS_NOT_TRUE : if ( * isNull ) {
 * isNull = false ;
 return BoolGetDatum ( true ) ;
 }
 else if ( DatumGetBool ( result ) ) return BoolGetDatum ( false ) ;
 else return BoolGetDatum ( true ) ;
 case IS_FALSE : if ( * isNull ) {
 * isNull = false ;
 return BoolGetDatum ( false ) ;
 }
 else if ( DatumGetBool ( result ) ) return BoolGetDatum ( false ) ;
 else return BoolGetDatum ( true ) ;
 case IS_NOT_FALSE : if ( * isNull ) {
 * isNull = false ;
 return BoolGetDatum ( true ) ;
 }
 else if ( DatumGetBool ( result ) ) return BoolGetDatum ( true ) ;
 else return BoolGetDatum ( false ) ;
 case IS_UNKNOWN : if ( * isNull ) {
 * isNull = false ;
 return BoolGetDatum ( true ) ;
 }
 else return BoolGetDatum ( false ) ;
 case IS_NOT_UNKNOWN : if ( * isNull ) {
 * isNull = false ;
 return BoolGetDatum ( false ) ;
 }
 else return BoolGetDatum ( true ) ;
 default : elog ( ERROR , "unrecognized booltesttype: %d" , ( int ) btest -> booltesttype ) ;
 return ( Datum ) 0 ;
 }
 }