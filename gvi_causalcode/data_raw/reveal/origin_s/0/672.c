static int mvsad_err_cost ( const MACROBLOCK * x , const MV * mv , const MV * ref , int error_per_bit ) {
 if ( x -> nmvsadcost ) {
 const MV diff = {
 mv -> row - ref -> row , mv -> col - ref -> col }
 ;
 return ROUND_POWER_OF_TWO ( mv_cost ( & diff , x -> nmvjointsadcost , x -> nmvsadcost ) * error_per_bit , 8 ) ;
 }
 return 0 ;
 }