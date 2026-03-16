static int dissect_segment_defn ( tvbuff_t * tvb , int offset , packet_info * pinfo , proto_tree * tree , guint64 channel , int encoding ) {
 proto_item * subtree_item = NULL ;
 proto_tree * subtree = NULL ;
 int seglen = 0 ;
 int ofs = 0 ;
 gboolean string_field_name = FALSE ;
 int remaining_datalen = 0 ;
 guint32 num_fields = 0 ;
 lbmpdm_definition_t * def = NULL ;
 gboolean add_definition = FALSE ;
 guint32 def_id = 0 ;
 guint8 vers_major = 0 ;
 guint8 vers_minor = 0 ;
 lbmpdm_definition_field_t * last_fixed_required_field = NULL ;
 seglen = lbmpdm_get_segment_length ( tvb , offset , encoding , & remaining_datalen ) ;
 if ( pinfo -> fd -> flags . visited == 0 ) {
 add_definition = TRUE ;
 }
 subtree_item = proto_tree_add_none_format ( tree , hf_lbmpdm_segment , tvb , offset , seglen , "Definition Segment" ) ;
 subtree = proto_item_add_subtree ( subtree_item , ett_lbmpdm_segment ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_next_hdr , tvb , offset + O_LBMPDM_SEG_HDR_T_NEXT_HDR , L_LBMPDM_SEG_HDR_T_NEXT_HDR , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_flags , tvb , offset + O_LBMPDM_SEG_HDR_T_FLAGS , L_LBMPDM_SEG_HDR_T_FLAGS , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_res , tvb , offset + O_LBMPDM_SEG_HDR_T_RES , L_LBMPDM_SEG_HDR_T_RES , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_len , tvb , offset + O_LBMPDM_SEG_HDR_T_LEN , L_LBMPDM_SEG_HDR_T_LEN , encoding ) ;
 ofs = offset + L_LBMPDM_SEG_HDR_T ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_def_id , tvb , ofs + O_LBMPDM_DEFN_T_ID , L_LBMPDM_DEFN_T_ID , encoding ) ;
 def_id = lbmpdm_fetch_uint32_encoded ( tvb , ofs + O_LBMPDM_DEFN_T_ID , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_def_num_fields , tvb , ofs + O_LBMPDM_DEFN_T_NUM_FIELDS , L_LBMPDM_DEFN_T_NUM_FIELDS , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_def_field_names_type , tvb , ofs + O_LBMPDM_DEFN_T_FIELD_NAMES_TYPE , L_LBMPDM_DEFN_T_FIELD_NAMES_TYPE , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_def_finalized , tvb , ofs + O_LBMPDM_DEFN_T_FINALIZED , L_LBMPDM_DEFN_T_FINALIZED , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_def_msg_vers_major , tvb , ofs + O_LBMPDM_DEFN_T_MSG_VERS_MAJOR , L_LBMPDM_DEFN_T_MSG_VERS_MAJOR , encoding ) ;
 vers_major = tvb_get_guint8 ( tvb , ofs + O_LBMPDM_DEFN_T_MSG_VERS_MAJOR ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_def_msg_vers_minor , tvb , ofs + O_LBMPDM_DEFN_T_MSG_VERS_MINOR , L_LBMPDM_DEFN_T_MSG_VERS_MINOR , encoding ) ;
 vers_minor = tvb_get_guint8 ( tvb , ofs + O_LBMPDM_DEFN_T_MSG_VERS_MINOR ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_def_fixed_req_section_len , tvb , ofs + O_LBMPDM_DEFN_T_FIXED_REQ_SECTION_LEN , L_LBMPDM_DEFN_T_FIXED_REQ_SECTION_LEN , encoding ) ;
 proto_tree_add_item ( subtree , hf_lbmpdm_segment_def_field_info_len , tvb , ofs + O_LBMPDM_DEFN_T_FIELD_INFO_LEN , L_LBMPDM_DEFN_T_FIELD_INFO_LEN , encoding ) ;
 if ( tvb_get_guint8 ( tvb , ofs + O_LBMPDM_DEFN_T_FIELD_NAMES_TYPE ) == PDM_DEFN_STR_FIELD_NAMES ) {
 string_field_name = TRUE ;
 }
 num_fields = lbmpdm_fetch_uint32_encoded ( tvb , ofs + O_LBMPDM_DEFN_T_NUM_FIELDS , encoding ) ;
 if ( add_definition ) {
 def = lbmpdm_definition_find ( channel , def_id , vers_major , vers_minor ) ;
 if ( def == NULL ) {
 def = lbmpdm_definition_add ( channel , def_id , vers_major , vers_minor ) ;
 def -> num_fields = num_fields ;
 def -> field_names_type = tvb_get_guint8 ( tvb , ofs + O_LBMPDM_DEFN_T_FIELD_NAMES_TYPE ) ;
 def -> fixed_req_section_len = lbmpdm_fetch_uint32_encoded ( tvb , ofs + O_LBMPDM_DEFN_T_FIXED_REQ_SECTION_LEN , encoding ) ;
 def -> first_fixed_required = NULL ;
 def -> fixed_required_count = 0 ;
 }
 }
 ofs += L_LBMPDM_DEFN_T ;
 remaining_datalen = seglen - L_LBMPDM_SEG_HDR_T - L_LBMPDM_DEFN_T ;
 while ( ( remaining_datalen > 0 ) && ( num_fields > 0 ) ) {
 proto_item * field_item = NULL ;
 proto_tree * field_tree = NULL ;
 guint32 def_len = L_LBMPDM_FIELD_INFO_T_INT_NAME ;
 int def_ofs = 0 ;
 int type_ofs = L_LBMPDM_FIELD_INFO_T ;
 guint32 string_name_len = 0 ;
 int string_name_ofs = - 1 ;
 if ( string_field_name ) {
 def_len = lbmpdm_fetch_uint32_encoded ( tvb , ofs , encoding ) + 4 ;
 }
 field_item = proto_tree_add_item ( subtree , hf_lbmpdm_segment_def_field , tvb , ofs , def_len , ENC_NA ) ;
 field_tree = proto_item_add_subtree ( field_item , ett_lbmpdm_segment_def_field ) ;
 if ( string_field_name ) {
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_def_len , tvb , ofs , 4 , encoding ) ;
 def_ofs = 4 ;
 type_ofs += def_ofs ;
 }
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_id , tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_ID , L_LBMPDM_FIELD_INFO_T_ID , encoding ) ;
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_len , tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_LEN , L_LBMPDM_FIELD_INFO_T_LEN , encoding ) ;
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_fixed_str_len , tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_FIXED_STR_LEN , L_LBMPDM_FIELD_INFO_T_FIXED_STR_LEN , encoding ) ;
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_num_arr_elem , tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_NUM_ARR_ELEM , L_LBMPDM_FIELD_INFO_T_NUM_ARR_ELEM , encoding ) ;
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_req , tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_REQ , L_LBMPDM_FIELD_INFO_T_REQ , encoding ) ;
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_fixed , tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_FIXED , L_LBMPDM_FIELD_INFO_T_FIXED , encoding ) ;
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_fld_int_name , tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_FLD_INT_NAME , L_LBMPDM_FIELD_INFO_T_FLD_INT_NAME , encoding ) ;
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_str_name_len , tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_STR_NAME_LEN , L_LBMPDM_FIELD_INFO_T_STR_NAME_LEN , encoding ) ;
 if ( string_field_name ) {
 string_name_len = lbmpdm_fetch_uint32_encoded ( tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_STR_NAME_LEN , encoding ) ;
 if ( string_name_len > 0 ) {
 string_name_ofs = ofs + def_ofs + L_LBMPDM_FIELD_INFO_T ;
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_str_name , tvb , string_name_ofs , ( int ) string_name_len , ENC_ASCII | ENC_NA ) ;
 type_ofs += string_name_len ;
 }
 }
 proto_tree_add_item ( field_tree , hf_lbmpdm_segment_def_field_fld_type , tvb , ofs + type_ofs , 2 , encoding ) ;
 if ( add_definition && ( def != NULL ) ) {
 lbmpdm_definition_field_t * field = NULL ;
 guint32 field_id ;
 field_id = lbmpdm_fetch_uint32_encoded ( tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_ID , encoding ) ;
 field = lbmpdm_definition_field_find ( def , field_id ) ;
 if ( field == NULL ) {
 field = lbmpdm_definition_field_add ( def , field_id ) ;
 if ( field != NULL ) {
 field -> len = lbmpdm_fetch_uint32_encoded ( tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_LEN , encoding ) ;
 field -> fixed_string_len = lbmpdm_fetch_uint32_encoded ( tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_FIXED_STR_LEN , encoding ) ;
 field -> num_array_elem = lbmpdm_fetch_uint32_encoded ( tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_NUM_ARR_ELEM , encoding ) ;
 field -> required = tvb_get_guint8 ( tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_REQ ) ;
 field -> fixed = tvb_get_guint8 ( tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_FIXED ) ;
 field -> field_int_name = lbmpdm_fetch_uint32_encoded ( tvb , ofs + def_ofs + O_LBMPDM_FIELD_INFO_T_FLD_INT_NAME , encoding ) ;
 if ( string_field_name && ( string_name_len > 0 ) ) {
 field -> field_string_name_len = string_name_len ;
 field -> field_string_name = tvb_get_string_enc ( wmem_file_scope ( ) , tvb , string_name_ofs , string_name_len , ENC_ASCII ) ;
 }
 else {
 field -> field_string_name_len = 0 ;
 field -> field_string_name = NULL ;
 }
 field -> field_type = lbmpdm_fetch_uint16_encoded ( tvb , ofs + type_ofs , encoding ) ;
 switch ( field -> field_type ) {
 case PDM_TYPE_BOOLEAN : case PDM_TYPE_BOOLEAN_ARR : field -> base_type = PDM_TYPE_BOOLEAN ;
 break ;
 case PDM_TYPE_INT8 : case PDM_TYPE_INT8_ARR : field -> base_type = PDM_TYPE_INT8 ;
 break ;
 case PDM_TYPE_UINT8 : case PDM_TYPE_UINT8_ARR : field -> base_type = PDM_TYPE_UINT8 ;
 break ;
 case PDM_TYPE_INT16 : case PDM_TYPE_INT16_ARR : field -> base_type = PDM_TYPE_INT16 ;
 break ;
 case PDM_TYPE_UINT16 : case PDM_TYPE_UINT16_ARR : field -> base_type = PDM_TYPE_UINT16 ;
 break ;
 case PDM_TYPE_INT32 : case PDM_TYPE_INT32_ARR : field -> base_type = PDM_TYPE_INT32 ;
 break ;
 case PDM_TYPE_UINT32 : case PDM_TYPE_UINT32_ARR : field -> base_type = PDM_TYPE_UINT32 ;
 break ;
 case PDM_TYPE_INT64 : case PDM_TYPE_INT64_ARR : field -> base_type = PDM_TYPE_INT64 ;
 break ;
 case PDM_TYPE_UINT64 : case PDM_TYPE_UINT64_ARR : field -> base_type = PDM_TYPE_UINT64 ;
 break ;
 case PDM_TYPE_FLOAT : case PDM_TYPE_FLOAT_ARR : field -> base_type = PDM_TYPE_FLOAT ;
 break ;
 case PDM_TYPE_DOUBLE : case PDM_TYPE_DOUBLE_ARR : field -> base_type = PDM_TYPE_DOUBLE ;
 break ;
 case PDM_TYPE_DECIMAL : case PDM_TYPE_DECIMAL_ARR : field -> base_type = PDM_TYPE_DECIMAL ;
 break ;
 case PDM_TYPE_TIMESTAMP : case PDM_TYPE_TIMESTAMP_ARR : field -> base_type = PDM_TYPE_TIMESTAMP ;
 break ;
 case PDM_TYPE_FIX_STRING : case PDM_TYPE_FIX_STRING_ARR : field -> base_type = PDM_TYPE_FIX_STRING ;
 break ;
 case PDM_TYPE_STRING : case PDM_TYPE_STRING_ARR : field -> base_type = PDM_TYPE_STRING ;
 break ;
 case PDM_TYPE_FIX_UNICODE : case PDM_TYPE_FIX_UNICODE_ARR : field -> base_type = PDM_TYPE_FIX_UNICODE ;
 break ;
 case PDM_TYPE_UNICODE : case PDM_TYPE_UNICODE_ARR : field -> base_type = PDM_TYPE_UNICODE ;
 break ;
 case PDM_TYPE_BLOB : case PDM_TYPE_BLOB_ARR : default : field -> base_type = PDM_TYPE_BLOB ;
 break ;
 case PDM_TYPE_MESSAGE : case PDM_TYPE_MESSAGE_ARR : field -> base_type = PDM_TYPE_MESSAGE ;
 break ;
 }
 if ( ( field -> fixed == PDM_DEFN_FIXED_LENGTH_FIELD ) && ( field -> required == PDM_DEFN_REQUIRED_FIELD ) ) {
 if ( last_fixed_required_field == NULL ) {
 def -> first_fixed_required = field ;
 field -> fixed_required_offset = 0 ;
 }
 else {
 last_fixed_required_field -> next_fixed_required = field ;
 field -> fixed_required_offset = last_fixed_required_field -> fixed_required_offset + last_fixed_required_field -> len ;
 }
 last_fixed_required_field = field ;
 def -> fixed_required_count ++ ;
 }
 }
 }
 }
 ofs += def_len ;
 remaining_datalen -= def_len ;
 num_fields -- ;
 }
 return ( seglen ) ;
 }