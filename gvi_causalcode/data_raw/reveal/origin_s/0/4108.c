static void intra_pred_horiz ( uint8_t * d , uint8_t * top , uint8_t * left , int stride ) {
 int y ;
 uint64_t a ;
 for ( y = 0 ;
 y < 8 ;
 y ++ ) {
 a = left [ y + 1 ] * 0x0101010101010101ULL ;
 * ( ( uint64_t * ) ( d + y * stride ) ) = a ;
 }
 }