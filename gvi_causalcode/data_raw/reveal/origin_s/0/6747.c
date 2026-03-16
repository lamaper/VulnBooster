static int dissect_segment_data ( tvbuff_t * tvb , int offset , packet_info * pinfo _U_ , proto_tree * tree , lbmpdm_msg_definition_id_t * id , int encoding ) {
 proto_item * subtree_item = NULL ;
 proto_tree * subtree = NULL ;
 int datalen = 0 ;
 int seglen = 0 ;
 lbmpdm_definition_t * def = NULL ;
 seglen = lbmpdm_get_segment_length ( tvb , offset , encoding , & datalen ) ;
 subtree_item = proto_tree_add_none_format ( tree , hf_lbmpdm_segment , tvb , offset , seglen , "Data Segment" ) ;
 subtree = proto_item_add_subtree ( subtree_item , ett_lbmpdm_segment ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_next_hdr , tvb , offset + O_LBMPDM_SEG_HDR_T_NEXT_HDR , L_LBMPDM_SEG_HDR_T_NEXT_HDR , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_flags , tvb , offset + O_LBMPDM_SEG_HDR_T_FLAGS , L_LBMPDM_SEG_HDR_T_FLAGS , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_res , tvb , offset + O_LBMPDM_SEG_HDR_T_RES , L_LBMPDM_SEG_HDR_T_RES , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_len , tvb , offset + O_LBMPDM_SEG_HDR_T_LEN , L_LBMPDM_SEG_HDR_T_LEN , encoding ) ;
 if ( ( id != NULL ) && ( id -> offset_table != NULL ) ) {
 def = lbmpdm_definition_find ( id -> channel , id -> msg_def_id , id -> ver_major , id -> ver_minor ) ;
 }
 if ( def == NULL ) {
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_data , tvb , offset + L_LBMPDM_SEG_HDR_T , datalen , ENC_NA ) ;
 }
 else {
 int fld_offset = offset + L_LBMPDM_SEG_HDR_T ;
 lbmpdm_definition_field_t * field = NULL ;
 gboolean string_field_names = FALSE ;
 guint32 idx ;
 if ( def -> field_names_type == PDM_DEFN_STR_FIELD_NAMES ) {
 string_field_names = TRUE ;
 }
 else {
 string_field_names = FALSE ;
 }
 for ( field = def -> first_fixed_required ;
 field != NULL ;
 field = field -> next_fixed_required ) {
 fld_offset += dissect_field ( tvb , fld_offset , subtree , field , string_field_names , encoding ) ;
 }
 for ( idx = 0 ;
 idx < id -> offset_table -> num_flds ;
 ++ idx ) {
 gint32 ofs = id -> offset_table -> offset_list [ idx ] ;
 if ( ofs != - 1 ) {
 field = lbmpdm_definition_field_find ( def , idx ) ;
 if ( field != NULL ) {
 ( void ) dissect_field ( tvb , offset + L_LBMPDM_SEG_HDR_T + ofs , subtree , field , string_field_names , encoding ) ;
 }
 }
 }
 }
 return ( seglen ) ;
 }