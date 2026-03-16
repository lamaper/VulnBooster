void proto_register_lbmpdm ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_lbmpdm_magic , {
 "Magic" , "lbmpdm.magic" , FT_UINT32 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_encoding , {
 "Encoding" , "lbmpdm.encoding" , FT_STRING , BASE_NONE , NULL , 0x0 , "encoding as determined by magic number" , HFILL }
 }
 , {
 & hf_lbmpdm_ver , {
 "Version" , "lbmpdm.ver" , FT_UINT8 , BASE_DEC , NULL , PDM_HDR_VER_TYPE_VER_MASK , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_type , {
 "Type" , "lbmpdm.type" , FT_UINT8 , BASE_DEC , NULL , PDM_HDR_VER_TYPE_TYPE_MASK , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_next_hdr , {
 "Next Header" , "lbmpdm.next_hdr" , FT_UINT8 , BASE_DEC_HEX , VALS ( lbmpdm_next_header ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_def_major_ver , {
 "Definition Major Version" , "lbmpdm.def_major_ver" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_def_minor_ver , {
 "Definition Minor Version" , "lbmpdm.def_minor_ver" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_def_id , {
 "Definition ID" , "lbmpdm.def_id" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_len , {
 "Length" , "lbmpdm.len" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segments , {
 "Segments" , "lbmpdm.segments" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment , {
 "Segment" , "lbmpdm.segment" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_next_hdr , {
 "Next Header" , "lbmpdm.segment.next_hdr" , FT_UINT8 , BASE_DEC_HEX , VALS ( lbmpdm_next_header ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_flags , {
 "Flags" , "lbmpdm.segment.flags" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_res , {
 "Reserved" , "lbmpdm.segment.res" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_len , {
 "Length" , "lbmpdm.segment.len" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_id , {
 "Definition ID" , "lbmpdm.segment_def.id" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_num_fields , {
 "Number Of Fields" , "lbmpdm.segment_def.num_fields" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_names_type , {
 "Field Names Type" , "lbmpdm.segment_def.field_names_type" , FT_UINT8 , BASE_HEX , VALS ( lbmpdm_field_name_type ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_finalized , {
 "Finalized" , "lbmpdm.segment_def.finalized" , FT_UINT8 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_msg_vers_major , {
 "Definition Major Version" , "lbmpdm.segment_def.msg_vers_major" , FT_UINT8 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_msg_vers_minor , {
 "Definition Minor Version" , "lbmpdm.segment_def.msg_vers_minor" , FT_UINT8 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_fixed_req_section_len , {
 "Fixed Required Section Length" , "lbmpdm.segment_def.fixed_req_section_len" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_info_len , {
 "Field Information Length" , "lbmpdm.segment_def.field_info_len" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field , {
 "Field Definition" , "lbmpdm.segment_def.field" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_def_len , {
 "Definition Length" , "lbmpdm.segment_def.field.def_len" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_id , {
 "ID" , "lbmpdm.segment_def.field.id" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_len , {
 "Length" , "lbmpdm.segment_def.field.len" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_fixed_str_len , {
 "Fixed String Length" , "lbmpdm.segment_def.field.fixed_str_len" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_num_arr_elem , {
 "Number Of Array Elements" , "lbmpdm.segment_def.field.num_arr_elem" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_req , {
 "Required" , "lbmpdm.segment_def.field.req" , FT_UINT8 , BASE_HEX , VALS ( lbmpdm_field_required ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_fixed , {
 "Fixed Length Field" , "lbmpdm.segment_def.field.fixed" , FT_UINT8 , BASE_HEX , VALS ( lbmpdm_field_fixed_length ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_fld_int_name , {
 "Field Integer Name" , "lbmpdm.segment_def.field.fld_int_name" , FT_INT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_str_name_len , {
 "String Name Length" , "lbmpdm.segment_def.field.str_name_len" , FT_INT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_str_name , {
 "String Name" , "lbmpdm.segment_def.field.str_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_def_field_fld_type , {
 "Field Type" , "lbmpdm.segment_def.field.fld_type" , FT_UINT16 , BASE_DEC_HEX , VALS ( lbmpdm_field_type ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_offset_entry , {
 "Offset Entry" , "lbmpdm.segment_ofs.entry" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_offset_entry_id , {
 "ID" , "lbmpdm.segment_ofs.entry.id" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_offset_entry_offset , {
 "Offset" , "lbmpdm.segment_ofs.entry.offset" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_segment_data , {
 "Data" , "lbmpdm.segment.data" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field , {
 "Field" , "lbmpdm.field" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_id , {
 "ID" , "lbmpdm.field.id" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_string_name , {
 "String Name" , "lbmpdm.field.string_name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_int_name , {
 "Integer Name" , "lbmpdm.field.int_name" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_type , {
 "Type" , "lbmpdm.field.type" , FT_UINT16 , BASE_DEC_HEX , VALS ( lbmpdm_field_type ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_total_length , {
 "Total Length" , "lbmpdm.field.total_length" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_length , {
 "Length" , "lbmpdm.field.length" , FT_UINT32 , BASE_DEC_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_boolean , {
 "Boolean Value" , "lbmpdm.field.value_boolean" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_int8 , {
 "INT8 Value" , "lbmpdm.field.value_int8" , FT_INT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_uint8 , {
 "UINT8 Value" , "lbmpdm.field.value_uint8" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_int16 , {
 "INT16 Value" , "lbmpdm.field.value_int16" , FT_INT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_uint16 , {
 "UINT16 Value" , "lbmpdm.field.value_uint16" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_int32 , {
 "INT32 Value" , "lbmpdm.field.value_int32" , FT_INT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_uint32 , {
 "UINT32 Value" , "lbmpdm.field.value_uint32" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_int64 , {
 "INT64 Value" , "lbmpdm.field.value_int64" , FT_INT64 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_uint64 , {
 "UINT64 Value" , "lbmpdm.field.value_uint64" , FT_UINT64 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_float , {
 "FLOAT Value" , "lbmpdm.field.value_float" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_double , {
 "DOUBLE Value" , "lbmpdm.field.value_double" , FT_DOUBLE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_decimal , {
 "DECIMAL Value" , "lbmpdm.field.value_decimal" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_timestamp , {
 "TIMESTAMP Value" , "lbmpdm.field.value_timestamp" , FT_ABSOLUTE_TIME , ABSOLUTE_TIME_LOCAL , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_fixed_string , {
 "FIXED STRING Value" , "lbmpdm.field.value_fixed_string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_string , {
 "STRING Value" , "lbmpdm.field.value_string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_fixed_unicode , {
 "FIXED UNICODE Value" , "lbmpdm.field.value_fixed_unicode" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_unicode , {
 "UNICODE Value" , "lbmpdm.field.value_unicode" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_blob , {
 "BLOB Value" , "lbmpdm.field.value_blob" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_lbmpdm_field_value_message , {
 "MESSAGE Value" , "lbmpdm.field.value_message" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 }
 ;
 static gint * ett [ ] = {
 & ett_lbmpdm , & ett_lbmpdm_segments , & ett_lbmpdm_segment , & ett_lbmpdm_offset_entry , & ett_lbmpdm_segment_def_field , & ett_lbmpdm_field }
 ;
 proto_lbmpdm = proto_register_protocol ( "LBMPDM Protocol" , "LBMPDM" , "lbmpdm" ) ;
 proto_register_field_array ( proto_lbmpdm , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 lbmpdm_definition_table = wmem_tree_new_autoreset ( wmem_epan_scope ( ) , wmem_file_scope ( ) ) ;
 }