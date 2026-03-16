proto_item * proto_tree_add_item_ret_uint ( proto_tree * tree , int hfindex , tvbuff_t * tvb , const gint start , gint length , const guint encoding , guint32 * retval ) {
 header_field_info * hfinfo = proto_registrar_get_nth ( hfindex ) ;
 field_info * new_fi ;
 guint32 value ;
 DISSECTOR_ASSERT_HINT ( hfinfo != NULL , "Not passed hfi!" ) ;
 switch ( hfinfo -> type ) {
 case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : break ;
 default : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 if ( length < - 1 || length == 0 ) REPORT_DISSECTOR_BUG ( wmem_strdup_printf ( wmem_packet_scope ( ) , "Invalid length %d passed to proto_tree_add_item_ret_uint" , length ) ) ;
 if ( encoding & ENC_STRING ) {
 REPORT_DISSECTOR_BUG ( "wrong encoding" ) ;
 }
 value = get_uint_value ( tree , tvb , start , length , encoding ) ;
 if ( retval ) * retval = value ;
 CHECK_FOR_NULL_TREE ( tree ) ;
 TRY_TO_FAKE_THIS_ITEM ( tree , hfinfo -> id , hfinfo ) ;
 new_fi = new_field_info ( tree , hfinfo , tvb , start , length ) ;
 proto_tree_set_uint ( new_fi , value ) ;
 new_fi -> flags |= ( encoding & ENC_LITTLE_ENDIAN ) ? FI_LITTLE_ENDIAN : FI_BIG_ENDIAN ;
 return proto_tree_add_node ( tree , new_fi ) ;
 }