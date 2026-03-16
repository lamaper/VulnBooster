static void deloco_rgb24 ( uint8_t * dst , int size ) {
 int i ;
 for ( i = 0 ;
 i < size ;
 i += 3 ) {
 int g = dst [ i + 1 ] ;
 dst [ i + 0 ] += g ;
 dst [ i + 2 ] += g ;
 }
 }