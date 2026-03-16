Datum icregexnesel ( PG_FUNCTION_ARGS ) {
 PG_RETURN_FLOAT8 ( patternsel ( fcinfo , Pattern_Type_Regex_IC , true ) ) ;
 }