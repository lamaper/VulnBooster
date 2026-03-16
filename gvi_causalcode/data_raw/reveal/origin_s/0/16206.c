static int huff_smallest_node ( hnode * hnodes , int num_hnodes ) {
 int i ;
 int best , best_node ;
 best = 99999999 ;
 best_node = - 1 ;
 for ( i = 0 ;
 i < num_hnodes ;
 i ++ ) {
 if ( hnodes [ i ] . used ) continue ;
 if ( ! hnodes [ i ] . count ) continue ;
 if ( hnodes [ i ] . count < best ) {
 best = hnodes [ i ] . count ;
 best_node = i ;
 }
 }
 if ( best_node == - 1 ) return - 1 ;
 hnodes [ best_node ] . used = 1 ;
 return best_node ;
 }