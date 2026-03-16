void proto_registrar_dump_values ( void ) {
 header_field_info * hfinfo ;
 int i , len , vi ;
 const value_string * vals ;
 const val64_string * vals64 ;
 const range_string * range ;
 const true_false_string * tfs ;
 len = gpa_hfinfo . len ;
 for ( i = 0 ;
 i < len ;
 i ++ ) {
 if ( gpa_hfinfo . hfi [ i ] == NULL ) continue ;
 PROTO_REGISTRAR_GET_NTH ( i , hfinfo ) ;
 if ( hfinfo -> id == hf_text_only ) {
 continue ;
 }
 if ( proto_registrar_is_protocol ( i ) ) {
 continue ;
 }


 vals64 = NULL ;
 range = NULL ;
 tfs = NULL ;
 if ( hfinfo -> strings != NULL ) {
 if ( ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) != BASE_CUSTOM && ( hfinfo -> type == FT_UINT8 || hfinfo -> type == FT_UINT16 || hfinfo -> type == FT_UINT24 || hfinfo -> type == FT_UINT32 || hfinfo -> type == FT_UINT40 || hfinfo -> type == FT_UINT48 || hfinfo -> type == FT_UINT56 || hfinfo -> type == FT_UINT64 || hfinfo -> type == FT_INT8 || hfinfo -> type == FT_INT16 || hfinfo -> type == FT_INT24 || hfinfo -> type == FT_INT32 || hfinfo -> type == FT_INT40 || hfinfo -> type == FT_INT48 || hfinfo -> type == FT_INT56 || hfinfo -> type == FT_INT64 ) ) {
 if ( hfinfo -> display & BASE_RANGE_STRING ) {
 range = ( const range_string * ) hfinfo -> strings ;
 }
 else if ( hfinfo -> display & BASE_EXT_STRING ) {
 vals = VALUE_STRING_EXT_VS_P ( ( value_string_ext * ) hfinfo -> strings ) ;
 }
 else if ( hfinfo -> display & BASE_VAL64_STRING ) {
 vals64 = ( const val64_string * ) hfinfo -> strings ;
 }
 else {
 vals = ( const value_string * ) hfinfo -> strings ;
 }
 }
 else if ( hfinfo -> type == FT_BOOLEAN ) {
 tfs = ( const struct true_false_string * ) hfinfo -> strings ;
 }
 }
 if ( vals ) {
 if ( hfinfo -> display & BASE_EXT_STRING ) {
 value_string_ext * vse_p = ( value_string_ext * ) hfinfo -> strings ;
 if ( ! value_string_ext_validate ( vse_p ) ) {
 g_warning ( "Invalid value_string_ext ptr for: %s" , hfinfo -> abbrev ) ;
 continue ;
 }
 try_val_to_str_ext ( 0 , vse_p ) ;
 ws_debug_printf ( "E\t%s\t%u\t%s\t%s\n" , hfinfo -> abbrev , VALUE_STRING_EXT_VS_NUM_ENTRIES ( vse_p ) , VALUE_STRING_EXT_VS_NAME ( vse_p ) , value_string_ext_match_type_str ( vse_p ) ) ;
 }
 vi = 0 ;
 while ( vals [ vi ] . strptr ) {
 if ( hfinfo -> display == BASE_HEX ) {
 ws_debug_printf ( "V\t%s\t0x%x\t%s\n" , hfinfo -> abbrev , vals [ vi ] . value , vals [ vi ] . strptr ) ;
 }
 else {
 ws_debug_printf ( "V\t%s\t%u\t%s\n" , hfinfo -> abbrev , vals [ vi ] . value , vals [ vi ] . strptr ) ;
 }
 vi ++ ;
 }
 }
 else if ( vals64 ) {
 vi = 0 ;
 while ( vals64 [ vi ] . strptr ) {
 ws_debug_printf ( "V64\t%s\t%" G_GINT64_MODIFIER "u\t%s\n" , hfinfo -> abbrev , vals64 [ vi ] . value , vals64 [ vi ] . strptr ) ;
 vi ++ ;
 }
 }
 else if ( range ) {
 vi = 0 ;
 while ( range [ vi ] . strptr ) {
 if ( ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) == BASE_HEX ) {
 ws_debug_printf ( "R\t%s\t0x%x\t0x%x\t%s\n" , hfinfo -> abbrev , range [ vi ] . value_min , range [ vi ] . value_max , range [ vi ] . strptr ) ;
 }
 else {
 ws_debug_printf ( "R\t%s\t%u\t%u\t%s\n" , hfinfo -> abbrev , range [ vi ] . value_min , range [ vi ] . value_max , range [ vi ] . strptr ) ;
 }
 vi ++ ;
 }
 }
 else if ( tfs ) {
 ws_debug_printf ( "T\t%s\t%s\t%s\n" , hfinfo -> abbrev , tfs -> true_string , tfs -> false_string ) ;
 }
 }
 }