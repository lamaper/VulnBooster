static void intra_pred_plane ( uint8_t * d , uint8_t * top , uint8_t * left , int stride ) {
 int x , y , ia ;
 int ih = 0 ;
 int iv = 0 ;
 uint8_t * cm = ff_cropTbl + MAX_NEG_CROP ;
 for ( x = 0 ;
 x < 4 ;
 x ++ ) {
 ih += ( x + 1 ) * ( top [ 5 + x ] - top [ 3 - x ] ) ;
 iv += ( x + 1 ) * ( left [ 5 + x ] - left [ 3 - x ] ) ;
 }
 ia = ( top [ 8 ] + left [ 8 ] ) << 4 ;
 ih = ( 17 * ih + 16 ) >> 5 ;
 iv = ( 17 * iv + 16 ) >> 5 ;
 for ( y = 0 ;
 y < 8 ;
 y ++ ) for ( x = 0 ;
 x < 8 ;
 x ++ ) d [ y * stride + x ] = cm [ ( ia + ( x - 3 ) * ih + ( y - 3 ) * iv + 16 ) >> 5 ] ;
 }