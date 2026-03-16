static int mv_err_cost ( const MV * mv , const MV * ref , const int * mvjcost , int * mvcost [ 2 ] , int error_per_bit ) {
 if ( mvcost ) {
 const MV diff = {
 mv -> row - ref -> row , mv -> col - ref -> col }
 ;
 return ROUND_POWER_OF_TWO ( mv_cost ( & diff , mvjcost , mvcost ) * error_per_bit , 13 ) ;
 }
 return 0 ;
 }