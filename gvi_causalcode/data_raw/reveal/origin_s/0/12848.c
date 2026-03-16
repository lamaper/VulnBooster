static void tokenize_init_one ( TOKENVALUE * t , const vp9_extra_bit * const e , int16_t * value_cost , int max_value ) {
 int i = - max_value ;
 int sign = 1 ;
 do {
 if ( ! i ) sign = 0 ;
 {
 const int a = sign ? - i : i ;
 int eb = sign ;
 if ( a > 4 ) {
 int j = 4 ;
 while ( ++ j < 11 && e [ j ] . base_val <= a ) {
 }
 t [ i ] . token = -- j ;
 eb |= ( a - e [ j ] . base_val ) << 1 ;
 }
 else {
 t [ i ] . token = a ;
 }
 t [ i ] . extra = eb ;
 }
 {
 int cost = 0 ;
 const vp9_extra_bit * p = & e [ t [ i ] . token ] ;
 if ( p -> base_val ) {
 const int extra = t [ i ] . extra ;
 const int length = p -> len ;
 if ( length ) cost += treed_cost ( p -> tree , p -> prob , extra >> 1 , length ) ;
 cost += vp9_cost_bit ( vp9_prob_half , extra & 1 ) ;
 value_cost [ i ] = cost ;
 }
 }
 }
 while ( ++ i < max_value ) ;
 }