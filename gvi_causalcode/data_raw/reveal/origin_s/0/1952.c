static inline int msmpeg4v1_pred_dc ( MpegEncContext * s , int n , int32_t * * dc_val_ptr ) {
 int i ;
 if ( n < 4 ) {
 i = 0 ;
 }
 else {
 i = n - 3 ;
 }
 * dc_val_ptr = & s -> last_dc [ i ] ;
 return s -> last_dc [ i ] ;
 }