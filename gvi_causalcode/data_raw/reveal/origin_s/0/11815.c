Datum neqsel ( PG_FUNCTION_ARGS ) {
 PlannerInfo * root = ( PlannerInfo * ) PG_GETARG_POINTER ( 0 ) ;
 Oid operator = PG_GETARG_OID ( 1 ) ;
 List * args = ( List * ) PG_GETARG_POINTER ( 2 ) ;
 int varRelid = PG_GETARG_INT32 ( 3 ) ;
 Oid eqop ;
 float8 result ;
 eqop = get_negator ( operator ) ;
 if ( eqop ) {
 result = DatumGetFloat8 ( DirectFunctionCall4 ( eqsel , PointerGetDatum ( root ) , ObjectIdGetDatum ( eqop ) , PointerGetDatum ( args ) , Int32GetDatum ( varRelid ) ) ) ;
 }
 else {
 result = DEFAULT_EQ_SEL ;
 }
 result = 1.0 - result ;
 PG_RETURN_FLOAT8 ( result ) ;
 }