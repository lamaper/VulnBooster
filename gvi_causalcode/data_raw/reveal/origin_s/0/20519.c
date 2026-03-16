static void intra_pred_down_left ( uint8_t * d , uint8_t * top , uint8_t * left , int stride ) {
 int x , y ;
 for ( y = 0 ;
 y < 8 ;
 y ++ ) for ( x = 0 ;
 x < 8 ;
 x ++ ) d [ y * stride + x ] = ( LOWPASS ( top , x + y + 2 ) + LOWPASS ( left , x + y + 2 ) ) >> 1 ;
 }