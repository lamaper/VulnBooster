void proto_cleanup ( void ) {
 if ( gpa_name_map ) {
 g_hash_table_destroy ( gpa_name_map ) ;
 gpa_name_map = NULL ;
 }
 g_free ( last_field_name ) ;
 last_field_name = NULL ;
 while ( protocols ) {
 protocol_t * protocol = ( protocol_t * ) protocols -> data ;
 header_field_info * hfinfo ;
 PROTO_REGISTRAR_GET_NTH ( protocol -> proto_id , hfinfo ) ;
 DISSECTOR_ASSERT ( protocol -> proto_id == hfinfo -> id ) ;
 g_slice_free ( header_field_info , hfinfo ) ;
 g_ptr_array_free ( protocol -> fields , TRUE ) ;
 g_list_free ( protocol -> heur_list ) ;
 protocols = g_list_remove ( protocols , protocol ) ;
 g_free ( protocol ) ;
 }
 if ( proto_names ) {
 g_hash_table_destroy ( proto_names ) ;
 proto_names = NULL ;
 }
 if ( proto_short_names ) {
 g_hash_table_destroy ( proto_short_names ) ;
 proto_short_names = NULL ;
 }
 if ( proto_filter_names ) {
 g_hash_table_destroy ( proto_filter_names ) ;
 proto_filter_names = NULL ;
 }
 if ( gpa_hfinfo . allocated_len ) {
 gpa_hfinfo . len = 0 ;
 gpa_hfinfo . allocated_len = 0 ;
 g_free ( gpa_hfinfo . hfi ) ;
 gpa_hfinfo . hfi = NULL ;
 }
 if ( deregistered_fields ) {
 g_ptr_array_free ( deregistered_fields , FALSE ) ;
 deregistered_fields = NULL ;
 }
 if ( deregistered_data ) {
 g_ptr_array_free ( deregistered_data , FALSE ) ;
 deregistered_data = NULL ;
 }
 g_free ( tree_is_expanded ) ;
 tree_is_expanded = NULL ;
 }