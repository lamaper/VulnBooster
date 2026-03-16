static void encode_quant_matrix ( VC2EncContext * s ) {
 int level ;
 put_bits ( & s -> pb , 1 , s -> custom_quant_matrix ) ;
 if ( s -> custom_quant_matrix ) {
 put_vc2_ue_uint ( & s -> pb , s -> quant [ 0 ] [ 0 ] ) ;
 for ( level = 0 ;
 level < s -> wavelet_depth ;
 level ++ ) {
 put_vc2_ue_uint ( & s -> pb , s -> quant [ level ] [ 1 ] ) ;
 put_vc2_ue_uint ( & s -> pb , s -> quant [ level ] [ 2 ] ) ;
 put_vc2_ue_uint ( & s -> pb , s -> quant [ level ] [ 3 ] ) ;
 }
 }
 }