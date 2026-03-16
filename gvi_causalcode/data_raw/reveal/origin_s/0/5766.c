static void intra_pred_down_right ( uint8_t * d , uint8_t * top , uint8_t * left , int stride ) {
 int x , y ;
 for ( y = 0 ;
 y < 8 ;
 y ++ ) for ( x = 0 ;
 x < 8 ;
 x ++ ) if ( x == y ) d [ y * stride + x ] = ( left [ 1 ] + 2 * top [ 0 ] + top [ 1 ] + 2 ) >> 2 ;
 else if ( x > y ) d [ y * stride + x ] = LOWPASS ( top , x - y ) ;
 else d [ y * stride + x ] = LOWPASS ( left , y - x ) ;
 }