static inline void mv_pred_median ( AVSContext * h , cavs_vector * mvP , cavs_vector * mvA , cavs_vector * mvB , cavs_vector * mvC ) {
 int ax , ay , bx , by , cx , cy ;
 int len_ab , len_bc , len_ca , len_mid ;
 scale_mv ( h , & ax , & ay , mvA , mvP -> dist ) ;
 scale_mv ( h , & bx , & by , mvB , mvP -> dist ) ;
 scale_mv ( h , & cx , & cy , mvC , mvP -> dist ) ;
 len_ab = abs ( ax - bx ) + abs ( ay - by ) ;
 len_bc = abs ( bx - cx ) + abs ( by - cy ) ;
 len_ca = abs ( cx - ax ) + abs ( cy - ay ) ;
 len_mid = mid_pred ( len_ab , len_bc , len_ca ) ;
 if ( len_mid == len_ab ) {
 mvP -> x = cx ;
 mvP -> y = cy ;
 }
 else if ( len_mid == len_bc ) {
 mvP -> x = ax ;
 mvP -> y = ay ;
 }
 else {
 mvP -> x = bx ;
 mvP -> y = by ;
 }
 }