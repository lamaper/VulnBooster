void vp9_comp_avg_pred ( uint8_t * comp_pred , const uint8_t * pred , int width , int height , const uint8_t * ref , int ref_stride ) {
 int i , j ;
 for ( i = 0 ;
 i < height ;
 i ++ ) {
 for ( j = 0 ;
 j < width ;
 j ++ ) {
 const int tmp = pred [ j ] + ref [ j ] ;
 comp_pred [ j ] = ROUND_POWER_OF_TWO ( tmp , 1 ) ;
 }
 comp_pred += width ;
 pred += width ;
 ref += ref_stride ;
 }
 }