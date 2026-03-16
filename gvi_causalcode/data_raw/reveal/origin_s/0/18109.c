guint16 elem_v_short ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , gint pdu_type , int idx , guint32 offset , guint32 nibble ) {
 guint16 consumed = 1 ;
 guint32 curr_offset ;
 proto_tree * subtree ;
 proto_item * item ;
 value_string_ext elem_names_ext ;
 gint * elem_ett ;
 elem_fcn * elem_funcs ;
 gchar * a_add_string ;
 const gchar * elem_name ;
 curr_offset = offset ;
 SET_ELEM_VARS ( pdu_type , elem_names_ext , elem_ett , elem_funcs , & ei_gsm_a_unknown_pdu_type ) ;
 elem_name = try_val_to_str_ext ( idx , & elem_names_ext ) ;
 if ( elem_name == NULL ) {
 proto_tree_add_expert ( tree , pinfo , & ei_gsm_a_unknown_element , tvb , curr_offset , 0 ) ;
 return consumed ;
 }
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 0 , elem_ett [ idx ] , & item , elem_name ) ;
 a_add_string = ( gchar * ) wmem_alloc ( wmem_packet_scope ( ) , 1024 ) ;
 a_add_string [ 0 ] = '\0' ;
 if ( elem_funcs [ idx ] == NULL ) {
 ( void ) de_spare_nibble ( tvb , subtree , pinfo , curr_offset , nibble , a_add_string , 1024 ) ;
 }
 else {
 ( void ) ( * elem_funcs [ idx ] ) ( tvb , subtree , pinfo , curr_offset , nibble , a_add_string , 1024 ) ;
 }
 if ( a_add_string [ 0 ] != '\0' ) {
 proto_item_append_text ( item , "%s" , a_add_string ) ;
 }
 proto_item_set_len ( item , consumed ) ;
 return consumed ;
 }