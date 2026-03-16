static void add_load_option ( DYNAMIC_STRING * str , const char * option , const char * option_value ) {
 if ( ! option_value ) {
 return ;
 }
 dynstr_append_checked ( str , option ) ;
 if ( strncmp ( option_value , "0x" , sizeof ( "0x" ) - 1 ) == 0 ) {
 dynstr_append_checked ( str , option_value ) ;
 }
 else {
 field_escape ( str , option_value ) ;
 }
 }