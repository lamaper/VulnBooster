static void proto_tree_set_representation_value ( proto_item * pi , const char * format , va_list ap ) {
 g_assert ( pi ) ;
 if ( PTREE_DATA ( pi ) -> visible && ! PROTO_ITEM_IS_HIDDEN ( pi ) ) {
 int ret = 0 ;
 field_info * fi = PITEM_FINFO ( pi ) ;
 header_field_info * hf ;
 DISSECTOR_ASSERT ( fi ) ;
 hf = fi -> hfinfo ;
 ITEM_LABEL_NEW ( PNODE_POOL ( pi ) , fi -> rep ) ;
 if ( hf -> bitmask && ( hf -> type == FT_BOOLEAN || IS_FT_UINT ( hf -> type ) ) ) {
 guint64 val ;
 char * p ;
 if ( IS_FT_UINT ( hf -> type ) ) val = fvalue_get_uinteger ( & fi -> value ) ;
 else val = fvalue_get_uinteger64 ( & fi -> value ) ;
 val <<= hfinfo_bitshift ( hf ) ;
 p = decode_bitfield_value ( fi -> rep -> representation , val , hf -> bitmask , hfinfo_container_bitwidth ( hf ) ) ;
 ret = ( int ) ( p - fi -> rep -> representation ) ;
 }
 ret += g_snprintf ( fi -> rep -> representation + ret , ITEM_LABEL_LENGTH - ret , "%s: " , hf -> name ) ;
 if ( ret < ITEM_LABEL_LENGTH ) {
 ret += g_vsnprintf ( fi -> rep -> representation + ret , ITEM_LABEL_LENGTH - ret , format , ap ) ;
 }
 if ( ret >= ITEM_LABEL_LENGTH ) {
 LABEL_MARK_TRUNCATED_START ( fi -> rep -> representation ) ;
 }
 }
 }