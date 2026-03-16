static int dictionary_load ( void ) {
 ddict_t * d ;
 ddict_application_t * p ;
 ddict_vendor_t * v ;
 ddict_cmd_t * c ;
 ddict_typedefn_t * t ;
 ddict_avp_t * a ;
 gboolean do_debug_parser = getenv ( "WIRESHARK_DEBUG_DIAM_DICT_PARSER" ) ? TRUE : FALSE ;
 gboolean do_dump_dict = getenv ( "WIRESHARK_DUMP_DIAM_DICT" ) ? TRUE : FALSE ;
 char * dir ;
 const avp_type_t * type ;
 const avp_type_t * octetstring = & basic_types [ 0 ] ;
 diam_avp_t * avp ;
 GHashTable * vendors = g_hash_table_new ( strcase_hash , strcase_equal ) ;
 diam_vnd_t * vnd ;
 GArray * vnd_shrt_arr = g_array_new ( TRUE , TRUE , sizeof ( value_string ) ) ;
 build_dict . hf = wmem_array_new ( wmem_epan_scope ( ) , sizeof ( hf_register_info ) ) ;
 build_dict . ett = g_ptr_array_new ( ) ;
 build_dict . types = g_hash_table_new ( strcase_hash , strcase_equal ) ;
 build_dict . avps = g_hash_table_new ( strcase_hash , strcase_equal ) ;
 dictionary . vnds = wmem_tree_new ( wmem_epan_scope ( ) ) ;
 dictionary . avps = wmem_tree_new ( wmem_epan_scope ( ) ) ;
 unknown_vendor . vs_cmds = g_array_new ( TRUE , TRUE , sizeof ( value_string ) ) ;
 unknown_vendor . vs_avps = g_array_new ( TRUE , TRUE , sizeof ( value_string ) ) ;
 no_vnd . vs_cmds = g_array_new ( TRUE , TRUE , sizeof ( value_string ) ) ;
 no_vnd . vs_avps = g_array_new ( TRUE , TRUE , sizeof ( value_string ) ) ;
 all_cmds = g_array_new ( TRUE , TRUE , sizeof ( value_string ) ) ;
 wmem_tree_insert32 ( dictionary . vnds , 0 , & no_vnd ) ;
 g_hash_table_insert ( vendors , ( gchar * ) "None" , & no_vnd ) ;
 for ( type = basic_types ;
 type -> name ;
 type ++ ) {
 g_hash_table_insert ( build_dict . types , ( gchar * ) type -> name , ( void * ) type ) ;
 }
 dir = g_strdup_printf ( "%s" G_DIR_SEPARATOR_S "diameter" G_DIR_SEPARATOR_S , get_datafile_dir ( ) ) ;
 d = ddict_scan ( dir , "dictionary.xml" , do_debug_parser ) ;
 g_free ( dir ) ;
 if ( d == NULL ) {
 g_hash_table_destroy ( vendors ) ;
 g_array_free ( vnd_shrt_arr , TRUE ) ;
 return 0 ;
 }
 if ( do_dump_dict ) ddict_print ( stdout , d ) ;
 for ( t = d -> typedefns ;
 t ;
 t = t -> next ) {
 const avp_type_t * parent = NULL ;
 if ( t -> name == NULL ) {
 report_failure ( "Diameter Dictionary: Invalid Type (empty name): parent==%s\n" , t -> parent ? t -> parent : "(null)" ) ;
 continue ;
 }
 if ( g_hash_table_lookup ( build_dict . types , t -> name ) ) continue ;
 if ( t -> parent ) {
 parent = ( avp_type_t * ) g_hash_table_lookup ( build_dict . types , t -> parent ) ;
 }
 if ( ! parent ) parent = octetstring ;
 g_hash_table_insert ( build_dict . types , t -> name , ( void * ) parent ) ;
 }
 if ( ( p = d -> applications ) ) {
 wmem_array_t * arr = wmem_array_new ( wmem_epan_scope ( ) , sizeof ( value_string ) ) ;
 value_string term [ 1 ] ;
 term [ 0 ] . value = 0 ;
 term [ 0 ] . strptr = NULL ;
 for ( ;
 p ;
 p = p -> next ) {
 value_string item [ 1 ] ;
 item [ 0 ] . value = p -> code ;
 item [ 0 ] . strptr = p -> name ;
 if ( ! p -> name ) {
 report_failure ( "Diameter Dictionary: Invalid Application (empty name): id=%d\n" , p -> code ) ;
 continue ;
 }
 wmem_array_append_one ( arr , item ) ;
 }
 wmem_array_sort ( arr , compare_avps ) ;
 wmem_array_append_one ( arr , term ) ;
 dictionary . applications = value_string_ext_new ( ( value_string * ) wmem_array_get_raw ( arr ) , wmem_array_get_count ( arr ) , wmem_strdup_printf ( wmem_epan_scope ( ) , "applications_vals_ext" ) ) ;
 }
 if ( ( v = d -> vendors ) ) {
 for ( ;
 v ;
 v = v -> next ) {
 value_string item [ 1 ] ;
 item [ 0 ] . value = v -> code ;
 item [ 0 ] . strptr = v -> name ;
 if ( v -> name == NULL ) {
 report_failure ( "Diameter Dictionary: Invalid Vendor (empty name): code==%d\n" , v -> code ) ;
 continue ;
 }
 if ( g_hash_table_lookup ( vendors , v -> name ) ) continue ;
 g_array_append_val ( vnd_shrt_arr , item ) ;
 vnd = wmem_new ( wmem_epan_scope ( ) , diam_vnd_t ) ;
 vnd -> code = v -> code ;
 vnd -> vs_cmds = g_array_new ( TRUE , TRUE , sizeof ( value_string ) ) ;
 vnd -> vs_avps = g_array_new ( TRUE , TRUE , sizeof ( value_string ) ) ;
 vnd -> vs_avps_ext = NULL ;
 wmem_tree_insert32 ( dictionary . vnds , vnd -> code , vnd ) ;
 g_hash_table_insert ( vendors , v -> name , vnd ) ;
 }
 }
 vnd_short_vs = ( value_string * ) vnd_shrt_arr -> data ;
 g_array_free ( vnd_shrt_arr , FALSE ) ;
 if ( ( c = d -> cmds ) ) {
 for ( ;
 c ;
 c = c -> next ) {
 if ( c -> vendor == NULL ) {
 report_failure ( "Diameter Dictionary: Invalid Vendor (empty name) for command %s\n" , c -> name ? c -> name : "(null)" ) ;
 continue ;
 }
 if ( ( vnd = ( diam_vnd_t * ) g_hash_table_lookup ( vendors , c -> vendor ) ) ) {
 value_string item [ 1 ] ;
 item [ 0 ] . value = c -> code ;
 item [ 0 ] . strptr = c -> name ;
 g_array_append_val ( vnd -> vs_cmds , item ) ;
 g_array_append_val ( all_cmds , item ) ;
 }
 else {
 report_failure ( "Diameter Dictionary: No Vendor: %s\n" , c -> vendor ) ;
 }
 }
 }
 for ( a = d -> avps ;
 a ;
 a = a -> next ) {
 ddict_enum_t * e ;
 value_string * vs = NULL ;
 const char * vend = a -> vendor ? a -> vendor : "None" ;
 ddict_xmlpi_t * x ;
 void * avp_data = NULL ;
 if ( a -> name == NULL ) {
 report_failure ( "Diameter Dictionary: Invalid AVP (empty name)\n" ) ;
 continue ;
 }
 if ( ( vnd = ( diam_vnd_t * ) g_hash_table_lookup ( vendors , vend ) ) ) {
 value_string vndvs [ 1 ] ;
 vndvs [ 0 ] . value = a -> code ;
 vndvs [ 0 ] . strptr = a -> name ;
 g_array_append_val ( vnd -> vs_avps , vndvs ) ;
 }
 else {
 report_failure ( "Diameter Dictionary: No Vendor: %s\n" , vend ) ;
 vnd = & unknown_vendor ;
 }
 if ( ( e = a -> enums ) ) {
 wmem_array_t * arr = wmem_array_new ( wmem_epan_scope ( ) , sizeof ( value_string ) ) ;
 value_string term [ 1 ] ;
 term [ 0 ] . value = 0 ;
 term [ 0 ] . strptr = NULL ;
 for ( ;
 e ;
 e = e -> next ) {
 value_string item [ 1 ] ;
 item [ 0 ] . value = e -> code ;
 item [ 0 ] . strptr = e -> name ;
 wmem_array_append_one ( arr , item ) ;
 }
 wmem_array_sort ( arr , compare_avps ) ;
 wmem_array_append_one ( arr , term ) ;
 vs = ( value_string * ) wmem_array_get_raw ( arr ) ;
 }
 type = NULL ;
 for ( x = d -> xmlpis ;
 x ;
 x = x -> next ) {
 if ( ( strcase_equal ( x -> name , "avp-proto" ) && strcase_equal ( x -> key , a -> name ) ) || ( a -> type && strcase_equal ( x -> name , "type-proto" ) && strcase_equal ( x -> key , a -> type ) ) ) {
 static avp_type_t proto_type = {
 "proto" , proto_avp , proto_avp , FT_UINT32 , BASE_HEX , build_proto_avp }
 ;
 type = & proto_type ;
 avp_data = x -> value ;
 break ;
 }
 }
 if ( ( ! type ) && a -> type ) type = ( avp_type_t * ) g_hash_table_lookup ( build_dict . types , a -> type ) ;
 if ( ! type ) type = octetstring ;
 avp = type -> build ( type , a -> code , vnd , a -> name , vs , avp_data ) ;
 if ( avp != NULL ) {
 g_hash_table_insert ( build_dict . avps , a -> name , avp ) ;
 {
 wmem_tree_key_t k [ 3 ] ;
 k [ 0 ] . length = 1 ;
 k [ 0 ] . key = & ( a -> code ) ;
 k [ 1 ] . length = 1 ;
 k [ 1 ] . key = & ( vnd -> code ) ;
 k [ 2 ] . length = 0 ;
 k [ 2 ] . key = NULL ;
 wmem_tree_insert32_array ( dictionary . avps , k , avp ) ;
 }
 }
 }
 g_hash_table_destroy ( build_dict . types ) ;
 g_hash_table_destroy ( build_dict . avps ) ;
 g_hash_table_destroy ( vendors ) ;
 return 1 ;
 }