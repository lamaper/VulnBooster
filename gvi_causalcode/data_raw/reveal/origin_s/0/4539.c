static void encode_parse_params ( VC2EncContext * s ) {
 put_vc2_ue_uint ( & s -> pb , s -> ver . major ) ;
 put_vc2_ue_uint ( & s -> pb , s -> ver . minor ) ;
 put_vc2_ue_uint ( & s -> pb , s -> profile ) ;
 put_vc2_ue_uint ( & s -> pb , s -> level ) ;
 }