static const char * hfinfo_format_text ( const header_field_info * hfinfo , const guchar * string ) {
 switch ( hfinfo -> display ) {
 case STR_ASCII : return format_text ( string , strlen ( string ) ) ;
 case STR_UNICODE : return string ;
 }
 return format_text ( string , strlen ( string ) ) ;
 }