gboolean proto_deregister_protocol ( const char * short_name ) {
 protocol_t * protocol ;
 header_field_info * hfinfo ;
 int proto_id ;
 gint key ;
 guint i ;
 proto_id = proto_get_id_by_short_name ( short_name ) ;
 protocol = find_protocol_by_id ( proto_id ) ;
 if ( protocol == NULL ) return FALSE ;
 key = wrs_str_hash ( protocol -> name ) ;
 g_hash_table_remove ( proto_names , & key ) ;
 g_hash_table_remove ( proto_short_names , ( gpointer ) short_name ) ;
 g_hash_table_remove ( proto_filter_names , ( gpointer ) protocol -> filter_name ) ;
 for ( i = 0 ;
 i < protocol -> fields -> len ;
 i ++ ) {
 hfinfo = ( header_field_info * ) g_ptr_array_index ( protocol -> fields , i ) ;
 hfinfo_remove_from_gpa_name_map ( hfinfo ) ;
 expert_deregister_expertinfo ( hfinfo -> abbrev ) ;
 g_ptr_array_add ( deregistered_fields , gpa_hfinfo . hfi [ hfinfo -> id ] ) ;
 }
 g_ptr_array_free ( protocol -> fields , TRUE ) ;
 protocol -> fields = NULL ;
 protocols = g_list_remove ( protocols , protocol ) ;
 g_ptr_array_add ( deregistered_fields , gpa_hfinfo . hfi [ proto_id ] ) ;
 g_hash_table_steal ( gpa_name_map , protocol -> filter_name ) ;
 g_free ( last_field_name ) ;
 last_field_name = NULL ;
 return TRUE ;
 }