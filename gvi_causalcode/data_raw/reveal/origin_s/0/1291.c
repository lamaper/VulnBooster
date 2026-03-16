guint16 elem_t ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint8 iei , gint pdu_type , int idx , guint32 offset , const gchar * name_add ) {
 guint8 oct ;
 guint32 curr_offset ;
 guint16 consumed ;
 value_string_ext elem_names_ext ;
 gint * elem_ett ;
 guint16 ( * * elem_funcs ) ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string , int string_len ) ;
 curr_offset = offset ;
 consumed = 0 ;
 SET_ELEM_VARS ( pdu_type , elem_names_ext , elem_ett , elem_funcs , & ei_gsm_a_unknown_pdu_type ) ;
 ( void ) elem_ett ;
 ( void ) elem_funcs ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 if ( oct == iei ) {
 proto_tree_add_uint_format ( tree , get_hf_elem_id ( pdu_type ) , tvb , curr_offset , 1 , oct , "%s%s" , val_to_str_ext ( idx , & elem_names_ext , "Unknown (%u)" ) , ( name_add == NULL ) || ( name_add [ 0 ] == '\0' ) ? "" : name_add ) ;
 consumed = 1 ;
 }
 return consumed ;
 }