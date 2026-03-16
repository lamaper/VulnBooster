int vp9_mv_bit_cost ( const MV * mv , const MV * ref , const int * mvjcost , int * mvcost [ 2 ] , int weight ) {
 const MV diff = {
 mv -> row - ref -> row , mv -> col - ref -> col }
 ;
 return ROUND_POWER_OF_TWO ( mv_cost ( & diff , mvjcost , mvcost ) * weight , 7 ) ;
 }