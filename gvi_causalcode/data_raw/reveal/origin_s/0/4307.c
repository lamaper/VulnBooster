static void decode_fixed_vector ( float * fixed_vector , const uint16_t * pulse_hi , const uint16_t * pulse_lo , const enum Mode mode ) {
 int sig_pos [ 4 ] [ 6 ] ;
 int spacing = ( mode == MODE_6k60 ) ? 2 : 4 ;
 int i , j ;
 switch ( mode ) {
 case MODE_6k60 : for ( i = 0 ;
 i < 2 ;
 i ++ ) decode_1p_track ( sig_pos [ i ] , pulse_lo [ i ] , 5 , 1 ) ;
 break ;
 case MODE_8k85 : for ( i = 0 ;
 i < 4 ;
 i ++ ) decode_1p_track ( sig_pos [ i ] , pulse_lo [ i ] , 4 , 1 ) ;
 break ;
 case MODE_12k65 : for ( i = 0 ;
 i < 4 ;
 i ++ ) decode_2p_track ( sig_pos [ i ] , pulse_lo [ i ] , 4 , 1 ) ;
 break ;
 case MODE_14k25 : for ( i = 0 ;
 i < 2 ;
 i ++ ) decode_3p_track ( sig_pos [ i ] , pulse_lo [ i ] , 4 , 1 ) ;
 for ( i = 2 ;
 i < 4 ;
 i ++ ) decode_2p_track ( sig_pos [ i ] , pulse_lo [ i ] , 4 , 1 ) ;
 break ;
 case MODE_15k85 : for ( i = 0 ;
 i < 4 ;
 i ++ ) decode_3p_track ( sig_pos [ i ] , pulse_lo [ i ] , 4 , 1 ) ;
 break ;
 case MODE_18k25 : for ( i = 0 ;
 i < 4 ;
 i ++ ) decode_4p_track ( sig_pos [ i ] , ( int ) pulse_lo [ i ] + ( ( int ) pulse_hi [ i ] << 14 ) , 4 , 1 ) ;
 break ;
 case MODE_19k85 : for ( i = 0 ;
 i < 2 ;
 i ++ ) decode_5p_track ( sig_pos [ i ] , ( int ) pulse_lo [ i ] + ( ( int ) pulse_hi [ i ] << 10 ) , 4 , 1 ) ;
 for ( i = 2 ;
 i < 4 ;
 i ++ ) decode_4p_track ( sig_pos [ i ] , ( int ) pulse_lo [ i ] + ( ( int ) pulse_hi [ i ] << 14 ) , 4 , 1 ) ;
 break ;
 case MODE_23k05 : case MODE_23k85 : for ( i = 0 ;
 i < 4 ;
 i ++ ) decode_6p_track ( sig_pos [ i ] , ( int ) pulse_lo [ i ] + ( ( int ) pulse_hi [ i ] << 11 ) , 4 , 1 ) ;
 break ;
 }
 memset ( fixed_vector , 0 , sizeof ( float ) * AMRWB_SFR_SIZE ) ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) for ( j = 0 ;
 j < pulses_nb_per_mode_tr [ mode ] [ i ] ;
 j ++ ) {
 int pos = ( FFABS ( sig_pos [ i ] [ j ] ) - 1 ) * spacing + i ;
 fixed_vector [ pos ] += sig_pos [ i ] [ j ] < 0 ? - 1.0 : 1.0 ;
 }
 }