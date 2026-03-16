guint16 elem_v ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , gint pdu_type , int idx , guint32 offset , const gchar * name_add ) {
 guint16 consumed ;
 guint32 curr_offset ;
 proto_tree * subtree ;
 proto_item * item ;
 value_string_ext elem_names_ext ;
 gint * elem_ett ;
 const gchar * elem_name ;
 guint16 ( * * elem_funcs ) ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string , int string_len ) ;
 curr_offset = offset ;
 consumed = 0 ;
 SET_ELEM_VARS ( pdu_type , elem_names_ext , elem_ett , elem_funcs , & ei_gsm_a_unknown_pdu_type ) ;
 elem_name = try_val_to_str_ext ( idx , & elem_names_ext ) ;
 if ( elem_name == NULL || elem_funcs [ idx ] == NULL ) {
 proto_tree_add_expert ( tree , pinfo , & ei_gsm_a_no_element_dissector , tvb , curr_offset , 1 ) ;
 consumed = 1 ;
 }
 else {
 gchar * a_add_string ;
 subtree = proto_tree_add_subtree_format ( tree , tvb , curr_offset , 0 , elem_ett [ idx ] , & item , "%s%s" , elem_name , ( name_add == NULL ) || ( name_add [ 0 ] == '\0' ) ? "" : name_add ) ;
 a_add_string = ( gchar * ) wmem_alloc ( wmem_packet_scope ( ) , 1024 ) ;
 a_add_string [ 0 ] = '\0' ;
 consumed = ( * elem_funcs [ idx ] ) ( tvb , subtree , pinfo , curr_offset , - 1 , a_add_string , 1024 ) ;
 if ( a_add_string [ 0 ] != '\0' ) {
 proto_item_append_text ( item , "%s" , a_add_string ) ;
 }
 proto_item_set_len ( item , consumed ) ;
 }
 return ( consumed ) ;
 }