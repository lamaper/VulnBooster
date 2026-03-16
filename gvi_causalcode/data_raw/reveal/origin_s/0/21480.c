static void get_residual ( int16_t * residual , int16_t * prev_excitation , int lag ) {
 int offset = PITCH_MAX - PITCH_ORDER / 2 - lag ;
 int i ;
 residual [ 0 ] = prev_excitation [ offset ] ;
 residual [ 1 ] = prev_excitation [ offset + 1 ] ;
 offset += 2 ;
 for ( i = 2 ;
 i < SUBFRAME_LEN + PITCH_ORDER - 1 ;
 i ++ ) residual [ i ] = prev_excitation [ offset + ( i - 2 ) % lag ] ;
 }