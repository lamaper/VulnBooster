int proto_register_protocol ( const char * name , const char * short_name , const char * filter_name ) {
 protocol_t * protocol ;
 const protocol_t * existing_protocol = NULL ;
 header_field_info * hfinfo ;
 int proto_id ;
 const char * existing_name ;
 gint * key ;
 guint i ;
 gchar c ;
 gboolean found_invalid ;
 key = ( gint * ) g_malloc ( sizeof ( gint ) ) ;
 * key = wrs_str_hash ( name ) ;
 existing_name = ( const char * ) g_hash_table_lookup ( proto_names , key ) ;
 if ( existing_name != NULL ) {
 g_error ( "Duplicate protocol name \"%s\"!" " This might be caused by an inappropriate plugin or a development error." , name ) ;
 }
 g_hash_table_insert ( proto_names , key , ( gpointer ) name ) ;
 existing_protocol = ( const protocol_t * ) g_hash_table_lookup ( proto_short_names , short_name ) ;
 if ( existing_protocol != NULL ) {
 g_error ( "Duplicate protocol short_name \"%s\"!" " This might be caused by an inappropriate plugin or a development error." , short_name ) ;
 }
 found_invalid = FALSE ;
 for ( i = 0 ;
 filter_name [ i ] ;
 i ++ ) {
 c = filter_name [ i ] ;
 if ( ! ( g_ascii_islower ( c ) || g_ascii_isdigit ( c ) || c == '-' || c == '_' || c == '.' ) ) {
 found_invalid = TRUE ;
 }
 }
 if ( found_invalid ) {
 g_error ( "Protocol filter name \"%s\" has one or more invalid characters." " Allowed are lower characters, digits, '-', '_' and '.'." " This might be caused by an inappropriate plugin or a development error." , filter_name ) ;
 }
 existing_protocol = ( const protocol_t * ) g_hash_table_lookup ( proto_filter_names , filter_name ) ;
 if ( existing_protocol != NULL ) {
 g_error ( "Duplicate protocol filter_name \"%s\"!" " This might be caused by an inappropriate plugin or a development error." , filter_name ) ;
 }
 protocol = g_new ( protocol_t , 1 ) ;
 protocol -> name = name ;
 protocol -> short_name = short_name ;
 protocol -> filter_name = filter_name ;
 protocol -> fields = g_ptr_array_new ( ) ;
 protocol -> is_enabled = TRUE ;
 protocol -> enabled_by_default = TRUE ;
 protocol -> can_toggle = TRUE ;
 protocol -> heur_list = NULL ;
 protocols = g_list_prepend ( protocols , protocol ) ;
 g_hash_table_insert ( proto_filter_names , ( gpointer ) filter_name , protocol ) ;
 g_hash_table_insert ( proto_short_names , ( gpointer ) short_name , protocol ) ;
 hfinfo = g_slice_new ( header_field_info ) ;
 hfinfo -> name = name ;
 hfinfo -> abbrev = filter_name ;
 hfinfo -> type = FT_PROTOCOL ;
 hfinfo -> display = BASE_NONE ;
 hfinfo -> strings = protocol ;
 hfinfo -> bitmask = 0 ;
 hfinfo -> ref_type = HF_REF_TYPE_NONE ;
 hfinfo -> blurb = NULL ;
 hfinfo -> parent = - 1 ;
 proto_id = proto_register_field_init ( hfinfo , hfinfo -> parent ) ;
 protocol -> proto_id = proto_id ;
 return proto_id ;
 }