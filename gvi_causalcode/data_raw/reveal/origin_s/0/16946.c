static int arith_get_number ( ArithCoder * c , int mod_val ) {
 int range = c -> high - c -> low + 1 ;
 int val = ( ( c -> value - c -> low + 1 ) * mod_val - 1 ) / range ;
 int prob = range * val ;
 c -> high = ( prob + range ) / mod_val + c -> low - 1 ;
 c -> low += prob / mod_val ;
 arith_normalise ( c ) ;
 return val ;
 }