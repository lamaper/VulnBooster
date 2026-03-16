static void decode_pitch_lag_1_6 ( int * lag_int , int * lag_frac , int pitch_index , const int prev_lag_int , const int subframe ) {
 if ( subframe == 0 || subframe == 2 ) {
 if ( pitch_index < 463 ) {
 * lag_int = ( pitch_index + 107 ) * 10923 >> 16 ;
 * lag_frac = pitch_index - * lag_int * 6 + 105 ;
 }
 else {
 * lag_int = pitch_index - 368 ;
 * lag_frac = 0 ;
 }
 }
 else {
 * lag_int = ( ( pitch_index + 5 ) * 10923 >> 16 ) - 1 ;
 * lag_frac = pitch_index - * lag_int * 6 - 3 ;
 * lag_int += av_clip ( prev_lag_int - 5 , PITCH_LAG_MIN_MODE_12k2 , PITCH_DELAY_MAX - 9 ) ;
 }
 }