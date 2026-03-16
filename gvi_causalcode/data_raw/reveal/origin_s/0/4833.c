static void truespeech_place_pulses ( TSContext * dec , int16_t * out , int quart ) {
 int16_t tmp [ 7 ] ;
 int i , j , t ;
 const int16_t * ptr1 ;
 int16_t * ptr2 ;
 int coef ;
 memset ( out , 0 , 60 * sizeof ( * out ) ) ;
 for ( i = 0 ;
 i < 7 ;
 i ++ ) {
 t = dec -> pulseval [ quart ] & 3 ;
 dec -> pulseval [ quart ] >>= 2 ;
 tmp [ 6 - i ] = ts_pulse_scales [ dec -> pulseoff [ quart ] * 4 + t ] ;
 }
 coef = dec -> pulsepos [ quart ] >> 15 ;
 ptr1 = ts_pulse_values + 30 ;
 ptr2 = tmp ;
 for ( i = 0 , j = 3 ;
 ( i < 30 ) && ( j > 0 ) ;
 i ++ ) {
 t = * ptr1 ++ ;
 if ( coef >= t ) coef -= t ;
 else {
 out [ i ] = * ptr2 ++ ;
 ptr1 += 30 ;
 j -- ;
 }
 }
 coef = dec -> pulsepos [ quart ] & 0x7FFF ;
 ptr1 = ts_pulse_values ;
 for ( i = 30 , j = 4 ;
 ( i < 60 ) && ( j > 0 ) ;
 i ++ ) {
 t = * ptr1 ++ ;
 if ( coef >= t ) coef -= t ;
 else {
 out [ i ] = * ptr2 ++ ;
 ptr1 += 30 ;
 j -- ;
 }
 }
 }