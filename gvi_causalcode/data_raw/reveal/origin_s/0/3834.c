static gboolean proto_item_add_bitmask_tree ( proto_item * item , tvbuff_t * tvb , const int offset , const int len , const gint ett , const int * * fields , const int flags , gboolean first , gboolean use_parent_tree , proto_tree * tree , guint64 value ) {
 guint bitshift ;
 guint64 available_bits = 0 ;
 guint64 tmpval ;
 header_field_info * hf ;
 if ( len < 0 || len > 8 ) g_assert_not_reached ( ) ;
 bitshift = ( 8 - ( guint ) len ) * 8 ;
 available_bits = G_GUINT64_CONSTANT ( 0xFFFFFFFFFFFFFFFF ) >> bitshift ;
 if ( use_parent_tree == FALSE ) tree = proto_item_add_subtree ( item , ett ) ;
 while ( * fields ) {
 guint64 present_bits ;
 PROTO_REGISTRAR_GET_NTH ( * * fields , hf ) ;
 DISSECTOR_ASSERT_HINT ( hf -> bitmask != 0 , hf -> abbrev ) ;
 present_bits = available_bits & hf -> bitmask ;
 if ( present_bits != hf -> bitmask ) {
 fields ++ ;
 continue ;
 }
 switch ( hf -> type ) {
 case FT_INT8 : case FT_UINT8 : case FT_INT16 : case FT_UINT16 : case FT_INT24 : case FT_UINT24 : case FT_INT32 : case FT_UINT32 : proto_tree_add_uint ( tree , * * fields , tvb , offset , len , ( guint32 ) value ) ;
 break ;
 case FT_INT40 : case FT_UINT40 : case FT_INT48 : case FT_UINT48 : case FT_INT56 : case FT_UINT56 : case FT_INT64 : case FT_UINT64 : proto_tree_add_uint64 ( tree , * * fields , tvb , offset , len , value ) ;
 break ;
 case FT_BOOLEAN : proto_tree_add_boolean64 ( tree , * * fields , tvb , offset , len , value ) ;
 break ;
 default : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 break ;
 }
 if ( flags & BMT_NO_APPEND ) {
 fields ++ ;
 continue ;
 }
 tmpval = ( value & hf -> bitmask ) >> hfinfo_bitshift ( hf ) ;
 switch ( hf -> type ) {
 case FT_INT8 : case FT_UINT8 : case FT_INT16 : case FT_UINT16 : case FT_INT24 : case FT_UINT24 : case FT_INT32 : case FT_UINT32 : case FT_INT40 : case FT_UINT40 : case FT_INT48 : case FT_UINT48 : case FT_INT56 : case FT_UINT56 : case FT_INT64 : case FT_UINT64 : if ( hf -> display == BASE_CUSTOM ) {
 gchar lbl [ ITEM_LABEL_LENGTH ] ;
 const custom_fmt_func_t fmtfunc = ( const custom_fmt_func_t ) hf -> strings ;
 DISSECTOR_ASSERT ( fmtfunc ) ;
 fmtfunc ( lbl , ( guint32 ) tmpval ) ;
 proto_item_append_text ( item , "%s%s: %s" , first ? "" : ", " , hf -> name , lbl ) ;
 first = FALSE ;
 }
 else if ( hf -> strings ) {
 proto_item_append_text ( item , "%s%s: %s" , first ? "" : ", " , hf -> name , hf_try_val_to_str_const ( ( guint32 ) tmpval , hf , "Unknown" ) ) ;
 first = FALSE ;
 }
 else if ( ! ( flags & BMT_NO_INT ) ) {
 char buf [ 32 ] ;
 const char * out ;
 if ( ! first ) {
 proto_item_append_text ( item , ", " ) ;
 }
 out = hfinfo_number_value_format ( hf , buf , ( guint32 ) tmpval ) ;
 proto_item_append_text ( item , "%s: %s" , hf -> name , out ) ;
 first = FALSE ;
 }
 break ;
 case FT_BOOLEAN : if ( hf -> strings && ! ( flags & BMT_NO_TFS ) ) {
 const struct true_false_string * tfs = ( const struct true_false_string * ) hf -> strings ;
 if ( tmpval ) {
 proto_item_append_text ( item , "%s%s: %s" , first ? "" : ", " , hf -> name , tfs -> true_string ) ;
 first = FALSE ;
 }
 else if ( ! ( flags & BMT_NO_FALSE ) ) {
 proto_item_append_text ( item , "%s%s: %s" , first ? "" : ", " , hf -> name , tfs -> false_string ) ;
 first = FALSE ;
 }
 }
 else if ( hf -> bitmask & value ) {
 proto_item_append_text ( item , "%s%s" , first ? "" : ", " , hf -> name ) ;
 first = FALSE ;
 }
 break ;
 default : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 break ;
 }
 fields ++ ;
 }
 return first ;
 }