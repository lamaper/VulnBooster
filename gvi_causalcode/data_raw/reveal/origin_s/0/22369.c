static void proto_tree_set_representation ( proto_item * pi , const char * format , va_list ap ) {
 int ret ;
 field_info * fi = PITEM_FINFO ( pi ) ;
 DISSECTOR_ASSERT ( fi ) ;
 if ( ! PROTO_ITEM_IS_HIDDEN ( pi ) ) {
 ITEM_LABEL_NEW ( PNODE_POOL ( pi ) , fi -> rep ) ;
 ret = g_vsnprintf ( fi -> rep -> representation , ITEM_LABEL_LENGTH , format , ap ) ;
 if ( ret >= ITEM_LABEL_LENGTH ) {
 LABEL_MARK_TRUNCATED_START ( fi -> rep -> representation ) ;
 }
 }
 }