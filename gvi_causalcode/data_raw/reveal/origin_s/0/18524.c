static void intra_pred_lp ( uint8_t * d , uint8_t * top , uint8_t * left , int stride ) {
 int x , y ;
 for ( y = 0 ;
 y < 8 ;
 y ++ ) for ( x = 0 ;
 x < 8 ;
 x ++ ) d [ y * stride + x ] = ( LOWPASS ( top , x + 1 ) + LOWPASS ( left , y + 1 ) ) >> 1 ;
 }