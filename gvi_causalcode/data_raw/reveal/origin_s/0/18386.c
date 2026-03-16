Datum regexeqjoinsel ( PG_FUNCTION_ARGS ) {
 PG_RETURN_FLOAT8 ( patternjoinsel ( fcinfo , Pattern_Type_Regex , false ) ) ;
 }