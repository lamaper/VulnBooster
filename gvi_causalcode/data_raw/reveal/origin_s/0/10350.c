static void gen_fcb_excitation ( int16_t * vector , G723_1_Subframe * subfrm , enum Rate cur_rate , int pitch_lag , int index ) {
 int temp , i , j ;
 memset ( vector , 0 , SUBFRAME_LEN * sizeof ( * vector ) ) ;
 if ( cur_rate == RATE_6300 ) {
 if ( subfrm -> pulse_pos >= max_pos [ index ] ) return ;
 j = PULSE_MAX - pulses [ index ] ;
 temp = subfrm -> pulse_pos ;
 for ( i = 0 ;
 i < SUBFRAME_LEN / GRID_SIZE ;
 i ++ ) {
 temp -= combinatorial_table [ j ] [ i ] ;
 if ( temp >= 0 ) continue ;
 temp += combinatorial_table [ j ++ ] [ i ] ;
 if ( subfrm -> pulse_sign & ( 1 << ( PULSE_MAX - j ) ) ) {
 vector [ subfrm -> grid_index + GRID_SIZE * i ] = - fixed_cb_gain [ subfrm -> amp_index ] ;
 }
 else {
 vector [ subfrm -> grid_index + GRID_SIZE * i ] = fixed_cb_gain [ subfrm -> amp_index ] ;
 }
 if ( j == PULSE_MAX ) break ;
 }
 if ( subfrm -> dirac_train == 1 ) gen_dirac_train ( vector , pitch_lag ) ;
 }
 else {
 int cb_gain = fixed_cb_gain [ subfrm -> amp_index ] ;
 int cb_shift = subfrm -> grid_index ;
 int cb_sign = subfrm -> pulse_sign ;
 int cb_pos = subfrm -> pulse_pos ;
 int offset , beta , lag ;
 for ( i = 0 ;
 i < 8 ;
 i += 2 ) {
 offset = ( ( cb_pos & 7 ) << 3 ) + cb_shift + i ;
 vector [ offset ] = ( cb_sign & 1 ) ? cb_gain : - cb_gain ;
 cb_pos >>= 3 ;
 cb_sign >>= 1 ;
 }
 lag = pitch_contrib [ subfrm -> ad_cb_gain << 1 ] + pitch_lag + subfrm -> ad_cb_lag - 1 ;
 beta = pitch_contrib [ ( subfrm -> ad_cb_gain << 1 ) + 1 ] ;
 if ( lag < SUBFRAME_LEN - 2 ) {
 for ( i = lag ;
 i < SUBFRAME_LEN ;
 i ++ ) vector [ i ] += beta * vector [ i - lag ] >> 15 ;
 }
 }
 }