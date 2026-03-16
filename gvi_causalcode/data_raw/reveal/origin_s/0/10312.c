static inline void rv34_pred_b_vector ( int A [ 2 ] , int B [ 2 ] , int C [ 2 ] , int A_avail , int B_avail , int C_avail , int * mx , int * my ) {
 if ( A_avail + B_avail + C_avail != 3 ) {
 * mx = A [ 0 ] + B [ 0 ] + C [ 0 ] ;
 * my = A [ 1 ] + B [ 1 ] + C [ 1 ] ;
 if ( A_avail + B_avail + C_avail == 2 ) {
 * mx /= 2 ;
 * my /= 2 ;
 }
 }
 else {
 * mx = mid_pred ( A [ 0 ] , B [ 0 ] , C [ 0 ] ) ;
 * my = mid_pred ( A [ 1 ] , B [ 1 ] , C [ 1 ] ) ;
 }
 }