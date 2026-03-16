Datum neqjoinsel ( PG_FUNCTION_ARGS ) {
 PlannerInfo * root = ( PlannerInfo * ) PG_GETARG_POINTER ( 0 ) ;
 Oid operator = PG_GETARG_OID ( 1 ) ;
 List * args = ( List * ) PG_GETARG_POINTER ( 2 ) ;
 JoinType jointype = ( JoinType ) PG_GETARG_INT16 ( 3 ) ;
 SpecialJoinInfo * sjinfo = ( SpecialJoinInfo * ) PG_GETARG_POINTER ( 4 ) ;
 Oid eqop ;
 float8 result ;
 eqop = get_negator ( operator ) ;
 if ( eqop ) {
 result = DatumGetFloat8 ( DirectFunctionCall5 ( eqjoinsel , PointerGetDatum ( root ) , ObjectIdGetDatum ( eqop ) , PointerGetDatum ( args ) , Int16GetDatum ( jointype ) , PointerGetDatum ( sjinfo ) ) ) ;
 }
 else {
 result = DEFAULT_EQ_SEL ;
 }
 result = 1.0 - result ;
 PG_RETURN_FLOAT8 ( result ) ;
 }