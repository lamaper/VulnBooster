static void intra_pred_dc_128 ( uint8_t * d , uint8_t * top , uint8_t * left , int stride ) {
 int y ;
 uint64_t a = 0x8080808080808080ULL ;
 for ( y = 0 ;
 y < 8 ;
 y ++ ) * ( ( uint64_t * ) ( d + y * stride ) ) = a ;
 }