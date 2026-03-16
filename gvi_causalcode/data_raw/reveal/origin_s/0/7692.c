static const char * hfinfo_number_vals_format64 ( const header_field_info * hfinfo , char buf [ 64 ] , guint64 value ) {
 int display = hfinfo -> display & FIELD_DISPLAY_E_MASK ;
 if ( display == BASE_NONE ) return NULL ;
 if ( display == BASE_DEC_HEX ) display = BASE_DEC ;
 if ( display == BASE_HEX_DEC ) display = BASE_HEX ;
 return hfinfo_number_value_format_display64 ( hfinfo , display , buf , value ) ;
 }