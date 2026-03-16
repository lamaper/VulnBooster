static void gen_acb_excitation ( int16_t * vector , int16_t * prev_excitation , int pitch_lag , G723_1_Subframe * subfrm , enum Rate cur_rate ) {
 int16_t residual [ SUBFRAME_LEN + PITCH_ORDER - 1 ] ;
 const int16_t * cb_ptr ;
 int lag = pitch_lag + subfrm -> ad_cb_lag - 1 ;
 int i ;
 int sum ;
 get_residual ( residual , prev_excitation , lag ) ;
 if ( cur_rate == RATE_6300 && pitch_lag < SUBFRAME_LEN - 2 ) cb_ptr = adaptive_cb_gain85 ;
 else cb_ptr = adaptive_cb_gain170 ;
 cb_ptr += subfrm -> ad_cb_gain * 20 ;
 for ( i = 0 ;
 i < SUBFRAME_LEN ;
 i ++ ) {
 sum = dot_product ( residual + i , cb_ptr , PITCH_ORDER ) ;
 vector [ i ] = av_sat_dadd32 ( 1 << 15 , sum ) >> 16 ;
 }
 }