static int get_options ( int argc , char * * argv ) {
 char * tmp , * pagpoint ;
 int ho_error ;
 MYSQL_PARAMETERS * mysql_params = mysql_get_parameters ( ) ;
 tmp = ( char * ) getenv ( "MYSQL_HOST" ) ;
 if ( tmp ) current_host = my_strdup ( tmp , MYF ( MY_WME ) ) ;
 pagpoint = getenv ( "PAGER" ) ;
 if ( ! ( ( char * ) ( pagpoint ) ) ) {
 strmov ( pager , "stdout" ) ;
 opt_nopager = 1 ;
 }
 else strmov ( pager , pagpoint ) ;
 strmov ( default_pager , pager ) ;
 opt_max_allowed_packet = * mysql_params -> p_max_allowed_packet ;
 opt_net_buffer_length = * mysql_params -> p_net_buffer_length ;
 if ( ( ho_error = handle_options ( & argc , & argv , my_long_options , get_one_option ) ) ) exit ( ho_error ) ;
 * mysql_params -> p_max_allowed_packet = opt_max_allowed_packet ;
 * mysql_params -> p_net_buffer_length = opt_net_buffer_length ;
 if ( status . batch ) {
 strmov ( default_pager , "stdout" ) ;
 strmov ( pager , "stdout" ) ;
 opt_nopager = 1 ;
 default_pager_set = 0 ;
 opt_outfile = 0 ;
 opt_reconnect = 0 ;
 connect_flag = 0 ;
 opt_progress_reports = 0 ;
 }
 if ( argc > 1 ) {
 usage ( 0 ) ;
 exit ( 1 ) ;
 }
 if ( argc == 1 ) {
 skip_updates = 0 ;
 my_free ( current_db ) ;
 current_db = my_strdup ( * argv , MYF ( MY_WME ) ) ;
 }
 if ( tty_password ) opt_password = get_tty_password ( NullS ) ;
 if ( debug_info_flag ) my_end_arg = MY_CHECK_ERROR | MY_GIVE_INFO ;
 if ( debug_check_flag ) my_end_arg = MY_CHECK_ERROR ;
 if ( ignore_spaces ) connect_flag |= CLIENT_IGNORE_SPACE ;
 if ( opt_progress_reports ) connect_flag |= CLIENT_PROGRESS ;
 return ( 0 ) ;
 }