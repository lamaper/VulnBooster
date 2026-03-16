void proto_init ( void ( register_all_protocols_func ) ( register_cb cb , gpointer client_data ) , void ( register_all_handoffs_func ) ( register_cb cb , gpointer client_data ) , register_cb cb , gpointer client_data ) {
 proto_cleanup ( ) ;
 proto_names = g_hash_table_new_full ( g_int_hash , g_int_equal , g_free , NULL ) ;
 proto_short_names = g_hash_table_new ( wrs_str_hash , g_str_equal ) ;
 proto_filter_names = g_hash_table_new ( wrs_str_hash , g_str_equal ) ;
 gpa_hfinfo . len = 0 ;
 gpa_hfinfo . allocated_len = 0 ;
 gpa_hfinfo . hfi = NULL ;
 gpa_name_map = g_hash_table_new_full ( g_str_hash , g_str_equal , NULL , save_same_name_hfinfo ) ;
 deregistered_fields = g_ptr_array_new ( ) ;
 deregistered_data = g_ptr_array_new ( ) ;
 ftypes_initialize ( ) ;
 address_types_initialize ( ) ;
 hf_text_only = proto_register_field_init ( & hfi_text_only , - 1 ) ;
 register_show_exception ( ) ;
 register_type_length_mismatch ( ) ;
 register_number_string_decoding_error ( ) ;
 register_all_protocols_func ( cb , client_data ) ;
 vines_address_type = address_type_get_by_name ( "AT_VINES" ) ;

 g_slist_foreach ( dissector_plugins , register_dissector_plugin , NULL ) ;


 g_slist_foreach ( dissector_plugins , reg_handoff_dissector_plugin , NULL ) ;

 tree_is_expanded = g_new0 ( guint32 , ( num_tree_types / 32 ) + 1 ) ;
 }