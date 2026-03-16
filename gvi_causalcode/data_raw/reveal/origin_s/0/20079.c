static void intra_pred_vert ( uint8_t * d , uint8_t * top , uint8_t * left , int stride ) {
 int y ;
 uint64_t a = AV_RN64 ( & top [ 1 ] ) ;
 for ( y = 0 ;
 y < 8 ;
 y ++ ) {
 * ( ( uint64_t * ) ( d + y * stride ) ) = a ;
 }
 }