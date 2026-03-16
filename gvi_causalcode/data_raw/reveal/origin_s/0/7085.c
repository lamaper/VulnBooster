static void proto_tree_set_uint ( field_info * fi , guint32 value ) {
 header_field_info * hfinfo ;
 guint32 integer ;
 hfinfo = fi -> hfinfo ;
 integer = value ;
 if ( hfinfo -> bitmask ) {
 integer &= ( guint32 ) ( hfinfo -> bitmask ) ;
 integer >>= hfinfo_bitshift ( hfinfo ) ;
 }
 fvalue_set_uinteger ( & fi -> value , integer ) ;
 }