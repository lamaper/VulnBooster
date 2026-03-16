static void encode_signal_range ( VC2EncContext * s ) {
 put_bits ( & s -> pb , 1 , ! s -> strict_compliance ) ;
 if ( ! s -> strict_compliance ) put_vc2_ue_uint ( & s -> pb , s -> bpp_idx ) ;
 }