static const char * hfinfo_number_value_format_display ( const header_field_info * hfinfo , int display , char buf [ 32 ] , guint32 value ) {
 char * ptr = & buf [ 31 ] ;
 gboolean isint = IS_FT_INT ( hfinfo -> type ) ;
 * ptr = '\0' ;
 switch ( display & FIELD_DISPLAY_E_MASK ) {
 case BASE_DEC : return isint ? int_to_str_back ( ptr , ( gint32 ) value ) : uint_to_str_back ( ptr , value ) ;
 case BASE_DEC_HEX : * ( -- ptr ) = ')' ;
 ptr = hex_to_str_back ( ptr , hfinfo_hex_digits ( hfinfo ) , value ) ;
 * ( -- ptr ) = '(' ;
 * ( -- ptr ) = ' ' ;
 ptr = isint ? int_to_str_back ( ptr , ( gint32 ) value ) : uint_to_str_back ( ptr , value ) ;
 return ptr ;
 case BASE_OCT : return oct_to_str_back ( ptr , value ) ;
 case BASE_HEX : return hex_to_str_back ( ptr , hfinfo_hex_digits ( hfinfo ) , value ) ;
 case BASE_HEX_DEC : * ( -- ptr ) = ')' ;
 ptr = isint ? int_to_str_back ( ptr , ( gint32 ) value ) : uint_to_str_back ( ptr , value ) ;
 * ( -- ptr ) = '(' ;
 * ( -- ptr ) = ' ' ;
 ptr = hex_to_str_back ( ptr , hfinfo_hex_digits ( hfinfo ) , value ) ;
 return ptr ;
 case BASE_PT_UDP : case BASE_PT_TCP : case BASE_PT_DCCP : case BASE_PT_SCTP : port_with_resolution_to_str_buf ( buf , 32 , display_to_port_type ( ( field_display_e ) display ) , value ) ;
 return buf ;
 default : g_assert_not_reached ( ) ;
 }
 return ptr ;
 }