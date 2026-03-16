void vp9_tokenize_initialize ( ) {
 TOKENVALUE * const t = dct_value_tokens + DCT_MAX_VALUE ;
 const vp9_extra_bit * const e = vp9_extra_bits ;
 int i = - DCT_MAX_VALUE ;
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
 const vp9_extra_bit * p = & vp9_extra_bits [ t [ i ] . token ] ;
 if ( p -> base_val ) {
 const int extra = t [ i ] . extra ;
 const int length = p -> len ;
 if ( length ) cost += treed_cost ( p -> tree , p -> prob , extra >> 1 , length ) ;
 cost += vp9_cost_bit ( vp9_prob_half , extra & 1 ) ;
 dct_value_cost [ i + DCT_MAX_VALUE ] = cost ;
 }
 }
 }
 while ( ++ i < DCT_MAX_VALUE ) ;
 vp9_dct_value_tokens_ptr = dct_value_tokens + DCT_MAX_VALUE ;
 vp9_dct_value_cost_ptr = dct_value_cost + DCT_MAX_VALUE ;
 }