static void tmp_fld_check_assert ( header_field_info * hfinfo ) {
 gchar * tmp_str ;
 if ( ! hfinfo -> name || ! hfinfo -> name [ 0 ] ) {
 if ( hfinfo -> abbrev ) g_error ( "Field (abbrev='%s') does not have a name\n" , hfinfo -> abbrev ) ;
 else g_error ( "Field does not have a name (nor an abbreviation)\n" ) ;
 }
 if ( ! hfinfo -> abbrev || ! hfinfo -> abbrev [ 0 ] ) g_error ( "Field '%s' does not have an abbreviation\n" , hfinfo -> name ) ;
 if ( hfinfo -> strings != NULL && ! ( ( hfinfo -> type == FT_UINT8 ) || ( hfinfo -> type == FT_UINT16 ) || ( hfinfo -> type == FT_UINT24 ) || ( hfinfo -> type == FT_UINT32 ) || ( hfinfo -> type == FT_UINT40 ) || ( hfinfo -> type == FT_UINT48 ) || ( hfinfo -> type == FT_UINT56 ) || ( hfinfo -> type == FT_UINT64 ) || ( hfinfo -> type == FT_INT8 ) || ( hfinfo -> type == FT_INT16 ) || ( hfinfo -> type == FT_INT24 ) || ( hfinfo -> type == FT_INT32 ) || ( hfinfo -> type == FT_INT40 ) || ( hfinfo -> type == FT_INT48 ) || ( hfinfo -> type == FT_INT56 ) || ( hfinfo -> type == FT_INT64 ) || ( hfinfo -> type == FT_BOOLEAN ) || ( hfinfo -> type == FT_PROTOCOL ) || ( hfinfo -> type == FT_FRAMENUM ) ) ) g_error ( "Field '%s' (%s) has a 'strings' value but is of type %s" " (which is not allowed to have strings)\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;

 int n , m ;
 const value_string * start_values ;
 const value_string * current ;
 if ( hfinfo -> display & BASE_EXT_STRING ) start_values = VALUE_STRING_EXT_VS_P ( ( ( const value_string_ext * ) hfinfo -> strings ) ) ;
 else start_values = ( const value_string * ) hfinfo -> strings ;
 current = start_values ;
 for ( n = 0 ;
 current ;
 n ++ , current ++ ) {
 if ( ( current -> value == 0 ) && ( current -> strptr == NULL ) ) {
 break ;
 }
 for ( m = 0 ;
 m < n ;
 m ++ ) {
 if ( ( start_values [ m ] . value == current -> value ) && ( strcmp ( start_values [ m ] . strptr , current -> strptr ) != 0 ) ) {
 g_warning ( "Field '%s' (%s) has a conflicting entry in its" " value_string: %u is at indices %u (%s) and %u (%s))\n" , hfinfo -> name , hfinfo -> abbrev , current -> value , m , start_values [ m ] . strptr , n , current -> strptr ) ;
 }
 }
 }
 }

 case FT_INT8 : case FT_INT16 : case FT_INT24 : case FT_INT32 : case FT_INT40 : case FT_INT48 : case FT_INT56 : case FT_INT64 : switch ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) {
 case BASE_HEX : case BASE_OCT : case BASE_DEC_HEX : case BASE_HEX_DEC : tmp_str = val_to_str_wmem ( NULL , hfinfo -> display , hf_display , "(Bit count: %d)" ) ;
 g_error ( "Field '%s' (%s) is signed (%s) but is being displayed unsigned (%s)\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , tmp_str ) ;
 wmem_free ( NULL , tmp_str ) ;
 }
 case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : case FT_UINT40 : case FT_UINT48 : case FT_UINT56 : case FT_UINT64 : if ( IS_BASE_PORT ( hfinfo -> display ) ) {
 tmp_str = val_to_str_wmem ( NULL , hfinfo -> display , hf_display , "(Unknown: 0x%x)" ) ;
 if ( hfinfo -> type != FT_UINT16 ) {
 g_error ( "Field '%s' (%s) has 'display' value %s but it can only be used with FT_UINT16, not %s\n" , hfinfo -> name , hfinfo -> abbrev , tmp_str , ftype_name ( hfinfo -> type ) ) ;
 }
 if ( hfinfo -> strings != NULL ) {
 g_error ( "Field '%s' (%s) is an %s (%s) but has a strings value\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , tmp_str ) ;
 }
 if ( hfinfo -> bitmask != 0 ) {
 g_error ( "Field '%s' (%s) is an %s (%s) but has a bitmask\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , tmp_str ) ;
 }
 wmem_free ( NULL , tmp_str ) ;
 break ;
 }
 switch ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) {
 case BASE_DEC : case BASE_HEX : case BASE_OCT : case BASE_DEC_HEX : case BASE_HEX_DEC : case BASE_CUSTOM : break ;
 case BASE_NONE : if ( hfinfo -> strings == NULL ) g_error ( "Field '%s' (%s) is an integral value (%s)" " but is being displayed as BASE_NONE but" " without a strings conversion" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;
 break ;
 default : tmp_str = val_to_str_wmem ( NULL , hfinfo -> display , hf_display , "(Unknown: 0x%x)" ) ;
 g_error ( "Field '%s' (%s) is an integral value (%s)" " but is being displayed as %s\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , tmp_str ) ;
 wmem_free ( NULL , tmp_str ) ;
 }
 break ;
 case FT_BYTES : switch ( hfinfo -> display & FIELD_DISPLAY_E_MASK ) {
 case BASE_NONE : case SEP_DOT : case SEP_DASH : case SEP_COLON : case SEP_SPACE : break ;
 default : tmp_str = val_to_str_wmem ( NULL , hfinfo -> display , hf_display , "(Bit count: %d)" ) ;
 g_error ( "Field '%s' (%s) is an byte array but is being displayed as %s instead of BASE_NONE, SEP_DOT, SEP_DASH, SEP_COLON, or SEP_SPACE\n" , hfinfo -> name , hfinfo -> abbrev , tmp_str ) ;
 wmem_free ( NULL , tmp_str ) ;
 }
 if ( hfinfo -> bitmask != 0 ) g_error ( "Field '%s' (%s) is an %s but has a bitmask\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;
 if ( hfinfo -> strings != NULL ) g_error ( "Field '%s' (%s) is an %s but has a strings value\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;
 break ;
 case FT_PROTOCOL : case FT_FRAMENUM : if ( hfinfo -> display != BASE_NONE ) {
 tmp_str = val_to_str_wmem ( NULL , hfinfo -> display , hf_display , "(Bit count: %d)" ) ;
 g_error ( "Field '%s' (%s) is an %s but is being displayed as %s instead of BASE_NONE\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , tmp_str ) ;
 wmem_free ( NULL , tmp_str ) ;
 }
 if ( hfinfo -> bitmask != 0 ) g_error ( "Field '%s' (%s) is an %s but has a bitmask\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;
 break ;
 case FT_BOOLEAN : break ;
 case FT_ABSOLUTE_TIME : if ( ! ( hfinfo -> display == ABSOLUTE_TIME_LOCAL || hfinfo -> display == ABSOLUTE_TIME_UTC || hfinfo -> display == ABSOLUTE_TIME_DOY_UTC ) ) {
 tmp_str = val_to_str_wmem ( NULL , hfinfo -> display , hf_display , "(Bit count: %d)" ) ;
 g_error ( "Field '%s' (%s) is a %s but is being displayed as %s instead of as a time\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , tmp_str ) ;
 wmem_free ( NULL , tmp_str ) ;
 }
 if ( hfinfo -> bitmask != 0 ) g_error ( "Field '%s' (%s) is an %s but has a bitmask\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;
 break ;
 case FT_STRING : case FT_STRINGZ : case FT_UINT_STRING : case FT_STRINGZPAD : switch ( hfinfo -> display ) {
 case STR_ASCII : case STR_UNICODE : break ;
 default : tmp_str = val_to_str_wmem ( NULL , hfinfo -> display , hf_display , "(Unknown: 0x%x)" ) ;
 g_error ( "Field '%s' (%s) is an string value (%s)" " but is being displayed as %s\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , tmp_str ) ;
 wmem_free ( NULL , tmp_str ) ;
 }
 if ( hfinfo -> bitmask != 0 ) g_error ( "Field '%s' (%s) is an %s but has a bitmask\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;
 if ( hfinfo -> strings != NULL ) g_error ( "Field '%s' (%s) is an %s but has a strings value\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;
 break ;
 case FT_IPv4 : switch ( hfinfo -> display ) {
 case BASE_NONE : case BASE_NETMASK : break ;
 default : tmp_str = val_to_str_wmem ( NULL , hfinfo -> display , hf_display , "(Unknown: 0x%x)" ) ;
 g_error ( "Field '%s' (%s) is an IPv4 value (%s)" " but is being displayed as %s\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , tmp_str ) ;
 wmem_free ( NULL , tmp_str ) ;
 break ;
 }
 break ;
 default : if ( hfinfo -> display != BASE_NONE ) {
 tmp_str = val_to_str_wmem ( NULL , hfinfo -> display , hf_display , "(Bit count: %d)" ) ;
 g_error ( "Field '%s' (%s) is an %s but is being displayed as %s instead of BASE_NONE\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) , tmp_str ) ;
 wmem_free ( NULL , tmp_str ) ;
 }
 if ( hfinfo -> bitmask != 0 ) g_error ( "Field '%s' (%s) is an %s but has a bitmask\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;
 if ( hfinfo -> strings != NULL ) g_error ( "Field '%s' (%s) is an %s but has a strings value\n" , hfinfo -> name , hfinfo -> abbrev , ftype_name ( hfinfo -> type ) ) ;
 break ;
 }
 }