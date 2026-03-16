static int get_pred_buffer ( PRED_BUFFER * p , int len ) {
 int i ;
 for ( i = 0 ;
 i < len ;
 i ++ ) {
 if ( ! p [ i ] . in_use ) {
 p [ i ] . in_use = 1 ;
 return i ;
 }
 }
 return - 1 ;
 }