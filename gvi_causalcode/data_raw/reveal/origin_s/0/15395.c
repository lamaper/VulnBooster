static double patternjoinsel ( PG_FUNCTION_ARGS , Pattern_Type ptype , bool negate ) {
 return negate ? ( 1.0 - DEFAULT_MATCH_SEL ) : DEFAULT_MATCH_SEL ;
 }