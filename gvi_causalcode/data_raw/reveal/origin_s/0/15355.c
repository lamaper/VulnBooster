Datum arraycontjoinsel ( PG_FUNCTION_ARGS ) {
 Oid operator = PG_GETARG_OID ( 1 ) ;
 PG_RETURN_FLOAT8 ( DEFAULT_SEL ( operator ) ) ;
 }