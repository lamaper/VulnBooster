static void fill_label_number ( field_info * fi , gchar * label_str , gboolean is_signed ) {
 header_field_info * hfinfo = fi -> hfinfo ;
 guint32 value ;
 char buf [ 32 ] ;
 const char * out ;
 if ( is_signed ) value = fvalue_get_sinteger ( & fi -> value ) ;
 else value = fvalue_get_uinteger ( & fi -> value ) ;
 if ( hfinfo -> display == BASE_CUSTOM ) {
 gchar tmp [ ITEM_LABEL_LENGTH ] ;
 const custom_fmt_func_t fmtfunc = ( const custom_fmt_func_t ) hfinfo -> strings ;
 DISSECTOR_ASSERT ( fmtfunc ) ;
 fmtfunc ( tmp , value ) ;
 label_fill ( label_str , 0 , hfinfo , tmp ) ;
 }
 else if ( hfinfo -> strings && hfinfo -> type != FT_FRAMENUM ) {
 const char * val_str = hf_try_val_to_str_const ( value , hfinfo , "Unknown" ) ;
 out = hfinfo_number_vals_format ( hfinfo , buf , value ) ;
 if ( out == NULL ) label_fill ( label_str , 0 , hfinfo , val_str ) ;
 else label_fill_descr ( label_str , 0 , hfinfo , val_str , out ) ;
 }
 else if ( IS_BASE_PORT ( hfinfo -> display ) ) {
 gchar tmp [ ITEM_LABEL_LENGTH ] ;
 port_with_resolution_to_str_buf ( tmp , sizeof ( tmp ) , display_to_port_type ( ( field_display_e ) hfinfo -> display ) , value ) ;
 label_fill ( label_str , 0 , hfinfo , tmp ) ;
 }
 else {
 out = hfinfo_number_value_format ( hfinfo , buf , value ) ;
 label_fill ( label_str , 0 , hfinfo , out ) ;
 }
 }