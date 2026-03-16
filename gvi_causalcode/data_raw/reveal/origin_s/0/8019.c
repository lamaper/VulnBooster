static const char * hfinfo_number_value_format64 ( const header_field_info * hfinfo , char buf [ 64 ] , guint64 value ) {
 int display = hfinfo -> display ;
 if ( hfinfo -> type == FT_FRAMENUM ) {
 display = BASE_DEC ;
 }
 return hfinfo_number_value_format_display64 ( hfinfo , display , buf , value ) ;
 }