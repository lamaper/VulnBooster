static const char * hfinfo_numeric_value_format ( const header_field_info * hfinfo , char buf [ 32 ] , guint32 value ) {
 int display = hfinfo -> display & FIELD_DISPLAY_E_MASK ;
 if ( hfinfo -> type == FT_FRAMENUM ) {
 display = BASE_DEC ;
 }
 if ( IS_BASE_PORT ( display ) ) {
 display = BASE_DEC ;
 }
 switch ( display ) {
 case BASE_NONE : case BASE_DEC_HEX : case BASE_OCT : case BASE_CUSTOM : display = BASE_DEC ;
 break ;
 case BASE_HEX_DEC : display = BASE_HEX ;
 break ;
 }
 return hfinfo_number_value_format_display ( hfinfo , display , buf , value ) ;
 }