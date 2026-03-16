static void proto_tree_set_int ( field_info * fi , gint32 value ) {
 header_field_info * hfinfo ;
 guint32 integer ;
 gint no_of_bits ;
 hfinfo = fi -> hfinfo ;
 integer = ( guint32 ) value ;
 if ( hfinfo -> bitmask ) {
 integer &= ( guint32 ) ( hfinfo -> bitmask ) ;
 integer >>= hfinfo_bitshift ( hfinfo ) ;
 no_of_bits = ws_count_ones ( hfinfo -> bitmask ) ;
 integer = ws_sign_ext32 ( integer , no_of_bits ) ;
 }
 fvalue_set_sinteger ( & fi -> value , integer ) ;
 }