static int get_options ( int * argc , char * * * argv ) {
 int ho_error ;
 MYSQL_PARAMETERS * mysql_params = mysql_get_parameters ( ) ;
 opt_max_allowed_packet = * mysql_params -> p_max_allowed_packet ;
 opt_net_buffer_length = * mysql_params -> p_net_buffer_length ;
 md_result_file = stdout ;
 if ( load_defaults ( "my" , load_default_groups , argc , argv ) ) return 1 ;
 defaults_argv = * argv ;
 if ( my_hash_init ( & ignore_table , charset_info , 16 , 0 , 0 , ( my_hash_get_key ) get_table_key , my_free , 0 ) ) return ( EX_EOM ) ;
 if ( my_hash_insert ( & ignore_table , ( uchar * ) my_strdup ( "mysql.apply_status" , MYF ( MY_WME ) ) ) || my_hash_insert ( & ignore_table , ( uchar * ) my_strdup ( "mysql.schema" , MYF ( MY_WME ) ) ) || my_hash_insert ( & ignore_table , ( uchar * ) my_strdup ( "mysql.general_log" , MYF ( MY_WME ) ) ) || my_hash_insert ( & ignore_table , ( uchar * ) my_strdup ( "mysql.slow_log" , MYF ( MY_WME ) ) ) ) return ( EX_EOM ) ;
 if ( ( ho_error = handle_options ( argc , argv , my_long_options , get_one_option ) ) ) return ( ho_error ) ;
 * mysql_params -> p_max_allowed_packet = opt_max_allowed_packet ;
 * mysql_params -> p_net_buffer_length = opt_net_buffer_length ;
 if ( debug_info_flag ) my_end_arg = MY_CHECK_ERROR | MY_GIVE_INFO ;
 if ( debug_check_flag ) my_end_arg = MY_CHECK_ERROR ;
 if ( opt_delayed ) opt_lock = 0 ;
 if ( ! path && ( enclosed || opt_enclosed || escaped || lines_terminated || fields_terminated ) ) {
 fprintf ( stderr , "%s: You must use option --tab with --fields-...\n" , my_progname_short ) ;
 return ( EX_USAGE ) ;
 }
 if ( opt_slave_data ) {
 opt_lock_all_tables = ! opt_single_transaction ;
 opt_master_data = 0 ;
 opt_delete_master_logs = 0 ;
 }
 if ( opt_delete_master_logs && ! opt_master_data ) opt_master_data = MYSQL_OPT_MASTER_DATA_COMMENTED_SQL ;
 if ( opt_single_transaction && opt_lock_all_tables ) {
 fprintf ( stderr , "%s: You can't use --single-transaction and " "--lock-all-tables at the same time.\n" , my_progname_short ) ;
 return ( EX_USAGE ) ;
 }
 if ( opt_master_data ) {
 opt_lock_all_tables = ! opt_single_transaction ;
 opt_slave_data = 0 ;
 }
 if ( opt_single_transaction || opt_lock_all_tables ) lock_tables = 0 ;
 if ( enclosed && opt_enclosed ) {
 fprintf ( stderr , "%s: You can't use ..enclosed.. and ..optionally-enclosed.. at the same time.\n" , my_progname_short ) ;
 return ( EX_USAGE ) ;
 }
 if ( ( opt_databases || opt_alldbs ) && path ) {
 fprintf ( stderr , "%s: --databases or --all-databases can't be used with --tab.\n" , my_progname_short ) ;
 return ( EX_USAGE ) ;
 }
 if ( strcmp ( default_charset , charset_info -> csname ) && ! ( charset_info = get_charset_by_csname ( default_charset , MY_CS_PRIMARY , MYF ( MY_WME ) ) ) ) exit ( 1 ) ;
 if ( ( * argc < 1 && ! opt_alldbs ) || ( * argc > 0 && opt_alldbs ) ) {
 short_usage ( stderr ) ;
 return EX_USAGE ;
 }
 if ( tty_password ) opt_password = get_tty_password ( NullS ) ;
 return ( 0 ) ;
 }