void proto_registrar_dump_fields ( void ) {
 header_field_info * hfinfo , * parent_hfinfo ;
 int i , len ;
 const char * enum_name ;
 const char * base_name ;
 const char * blurb ;
 char width [ 5 ] ;
 len = gpa_hfinfo . len ;
 for ( i = 0 ;
 i < len ;
 i ++ ) {
 if ( gpa_hfinfo . hfi [ i ] == NULL ) continue ;
 PROTO_REGISTRAR_GET_NTH ( i , hfinfo ) ;
 if ( hfinfo -> id == hf_text_only ) continue ;
 if ( proto_registrar_is_protocol ( i ) ) {
 ws_debug_printf ( "P\t%s\t%s\n" , hfinfo -> name , hfinfo -> abbrev ) ;
 }
 else {
 if ( hfinfo -> same_name_prev_id != - 1 ) continue ;
 PROTO_REGISTRAR_GET_NTH ( hfinfo -> parent , parent_hfinfo ) ;
 enum_name = ftype_name ( hfinfo -> type ) ;
 base_name = "" ;
 if ( hfinfo -> type == FT_UINT8 || hfinfo -> type == FT_UINT16 || hfinfo -> type == FT_UINT24 || hfinfo -> type == FT_UINT32 || hfinfo -> type == FT_UINT40 || hfinfo -> type == FT_UINT48 || hfinfo -> type == FT_UINT56 || hfinfo -> type == FT_UINT64 || hfinfo -> type == FT_INT8 || hfinfo -> type == FT_INT16 || hfinfo -> type == FT_INT24 || hfinfo -> type == FT_INT32 || hfinfo -> type == FT_INT40 || hfinfo -> type == FT_INT48 || hfinfo -> type == FT_INT56 || hfinfo -> type == FT_INT64 ) {
 switch ( FIELD_DISPLAY ( hfinfo -> display ) ) {
 case BASE_NONE : case BASE_DEC : case BASE_HEX : case BASE_OCT : case BASE_DEC_HEX : case BASE_HEX_DEC : case BASE_CUSTOM : case BASE_PT_UDP : case BASE_PT_TCP : case BASE_PT_DCCP : case BASE_PT_SCTP : base_name = val_to_str_const ( FIELD_DISPLAY ( hfinfo -> display ) , hf_display , "????" ) ;
 break ;
 default : base_name = "????" ;
 break ;
 }
 }
 else if ( hfinfo -> type == FT_BOOLEAN ) {
 g_snprintf ( width , sizeof ( width ) , "%d" , hfinfo -> display ) ;
 base_name = width ;
 }
 blurb = hfinfo -> blurb ;
 if ( blurb == NULL ) blurb = "" ;
 else if ( strlen ( blurb ) == 0 ) blurb = "\"\"" ;
 ws_debug_printf ( "F\t%s\t%s\t%s\t%s\t%s\t0x%" G_GINT64_MODIFIER "x\t%s\n" , hfinfo -> name , hfinfo -> abbrev , enum_name , parent_hfinfo -> abbrev , base_name , hfinfo -> bitmask , blurb ) ;
 }
 }
 }