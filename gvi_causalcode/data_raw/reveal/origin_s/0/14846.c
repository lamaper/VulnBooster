static int com_use ( String * buffer __attribute__ ( ( unused ) ) , char * line ) {
 char * tmp , buff [ FN_REFLEN + 1 ] ;
 int select_db ;
 bzero ( buff , sizeof ( buff ) ) ;
 strmake_buf ( buff , line ) ;
 tmp = get_arg ( buff , GET ) ;
 if ( ! tmp || ! * tmp ) {
 put_info ( "USE must be followed by a database name" , INFO_ERROR ) ;
 return 0 ;
 }
 get_current_db ( ) ;
 if ( ! current_db || cmp_database ( charset_info , current_db , tmp ) ) {
 if ( one_database ) {
 skip_updates = 1 ;
 select_db = 0 ;
 }
 else select_db = 2 ;
 }
 else {
 skip_updates = 0 ;
 select_db = 1 ;
 }
 if ( select_db ) {
 if ( ! connected && reconnect ( ) ) return opt_reconnect ? - 1 : 1 ;
 if ( mysql_select_db ( & mysql , tmp ) ) {
 if ( mysql_errno ( & mysql ) != CR_SERVER_GONE_ERROR ) return put_error ( & mysql ) ;
 if ( reconnect ( ) ) return opt_reconnect ? - 1 : 1 ;
 if ( mysql_select_db ( & mysql , tmp ) ) return put_error ( & mysql ) ;
 }
 my_free ( current_db ) ;
 current_db = my_strdup ( tmp , MYF ( MY_WME ) ) ;


 put_info ( "Database changed" , INFO_INFO ) ;
 return 0 ;
 }