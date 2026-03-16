static void proto_tree_set_int64 ( field_info * fi , gint64 value ) {
 header_field_info * hfinfo ;
 guint64 integer ;
 gint no_of_bits ;
 hfinfo = fi -> hfinfo ;
 integer = value ;
 if ( hfinfo -> bitmask ) {
 integer &= hfinfo -> bitmask ;
 integer >>= hfinfo_bitshift ( hfinfo ) ;
 no_of_bits = ws_count_ones ( hfinfo -> bitmask ) ;
 integer = ws_sign_ext64 ( integer , no_of_bits ) ;
 }
 fvalue_set_sinteger64 ( & fi -> value , integer ) ;
 }