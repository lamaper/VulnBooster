static int proto_register_field_init ( header_field_info * hfinfo , const int parent ) {
 tmp_fld_check_assert ( hfinfo ) ;
 hfinfo -> parent = parent ;
 hfinfo -> same_name_next = NULL ;
 hfinfo -> same_name_prev_id = - 1 ;
 if ( gpa_hfinfo . len >= gpa_hfinfo . allocated_len ) {
 if ( ! gpa_hfinfo . hfi ) {
 gpa_hfinfo . allocated_len = PROTO_PRE_ALLOC_HF_FIELDS_MEM ;
 gpa_hfinfo . hfi = ( header_field_info * * ) g_malloc ( sizeof ( header_field_info * ) * PROTO_PRE_ALLOC_HF_FIELDS_MEM ) ;
 }
 else {
 gpa_hfinfo . allocated_len += 1000 ;
 gpa_hfinfo . hfi = ( header_field_info * * ) g_realloc ( gpa_hfinfo . hfi , sizeof ( header_field_info * ) * gpa_hfinfo . allocated_len ) ;
 }
 }
 gpa_hfinfo . hfi [ gpa_hfinfo . len ] = hfinfo ;
 gpa_hfinfo . len ++ ;
 hfinfo -> id = gpa_hfinfo . len - 1 ;
 if ( ( hfinfo -> name [ 0 ] != 0 ) && ( hfinfo -> abbrev [ 0 ] != 0 ) ) {
 header_field_info * same_name_next_hfinfo ;
 guchar c ;
 c = wrs_check_charset ( fld_abbrev_chars , hfinfo -> abbrev ) ;
 if ( c ) {
 if ( g_ascii_isprint ( c ) ) fprintf ( stderr , "Invalid character '%c' in filter name '%s'\n" , c , hfinfo -> abbrev ) ;
 else fprintf ( stderr , "Invalid byte \\%03o in filter name '%s'\n" , c , hfinfo -> abbrev ) ;
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 same_name_hfinfo = NULL ;
 g_hash_table_insert ( gpa_name_map , ( gpointer ) ( hfinfo -> abbrev ) , hfinfo ) ;
 if ( same_name_hfinfo ) {
 same_name_next_hfinfo = same_name_hfinfo -> same_name_next ;
 hfinfo -> same_name_next = same_name_next_hfinfo ;
 if ( same_name_next_hfinfo ) same_name_next_hfinfo -> same_name_prev_id = hfinfo -> id ;
 same_name_hfinfo -> same_name_next = hfinfo ;
 hfinfo -> same_name_prev_id = same_name_hfinfo -> id ;

 if ( _ftype_common ( hfinfo -> type ) != _ftype_common ( same_name_hfinfo -> type ) ) fprintf ( stderr , "'%s' exists multiple times with NOT compatible types: %s and %s\n" , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , ftype_name ( same_name_hfinfo -> type ) ) ;
 same_name_hfinfo = same_name_hfinfo -> same_name_next ;
 }

 }
 return hfinfo -> id ;
 }