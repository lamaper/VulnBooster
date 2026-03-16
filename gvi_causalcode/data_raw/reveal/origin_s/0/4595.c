gboolean proto_name_already_registered ( const gchar * name ) {
 gint key ;
 DISSECTOR_ASSERT_HINT ( name , "No name present" ) ;
 key = wrs_str_hash ( name ) ;
 if ( g_hash_table_lookup ( proto_names , & key ) != NULL ) return TRUE ;
 return FALSE ;
 }