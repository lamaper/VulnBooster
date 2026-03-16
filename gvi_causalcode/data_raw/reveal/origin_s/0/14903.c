static void pack_mb_tokens ( vp9_writer * w , TOKENEXTRA * * tp , const TOKENEXTRA * const stop ) {
 TOKENEXTRA * p = * tp ;
 while ( p < stop && p -> token != EOSB_TOKEN ) {
 const int t = p -> token ;
 const struct vp9_token * const a = & vp9_coef_encodings [ t ] ;
 const vp9_extra_bit * const b = & vp9_extra_bits [ t ] ;
 int i = 0 ;
 int v = a -> value ;
 int n = a -> len ;
 if ( p -> skip_eob_node ) {
 n -= p -> skip_eob_node ;
 i = 2 * p -> skip_eob_node ;
 }
 if ( t >= TWO_TOKEN && t < EOB_TOKEN ) {
 int len = UNCONSTRAINED_NODES - p -> skip_eob_node ;
 int bits = v >> ( n - len ) ;
 vp9_write_tree ( w , vp9_coef_tree , p -> context_tree , bits , len , i ) ;
 vp9_write_tree ( w , vp9_coef_con_tree , vp9_pareto8_full [ p -> context_tree [ PIVOT_NODE ] - 1 ] , v , n - len , 0 ) ;
 }
 else {
 vp9_write_tree ( w , vp9_coef_tree , p -> context_tree , v , n , i ) ;
 }
 if ( b -> base_val ) {
 const int e = p -> extra , l = b -> len ;
 if ( l ) {
 const unsigned char * pb = b -> prob ;
 int v = e >> 1 ;
 int n = l ;
 int i = 0 ;
 do {
 const int bb = ( v >> -- n ) & 1 ;
 vp9_write ( w , bb , pb [ i >> 1 ] ) ;
 i = b -> tree [ i + bb ] ;
 }
 while ( n ) ;
 }
 vp9_write_bit ( w , e & 1 ) ;
 }
 ++ p ;
 }
 * tp = p + ( p -> token == EOSB_TOKEN ) ;
 }