static int init_server_components ( ) {
 DBUG_ENTER ( "init_server_components" ) ;
 mdl_init ( ) ;
 if ( table_def_init ( ) | hostname_cache_init ( ) ) unireg_abort ( 1 ) ;
 query_cache_set_min_res_unit ( query_cache_min_res_unit ) ;
 query_cache_init ( ) ;
 query_cache_resize ( query_cache_size ) ;
 my_rnd_init ( & sql_rand , ( ulong ) server_start_time , ( ulong ) server_start_time / 2 ) ;
 setup_fpu ( ) ;
 init_thr_lock ( ) ;
 my_uuid_init ( ( ulong ) ( my_rnd ( & sql_rand ) ) * 12345 , 12345 ) ;


 if ( opt_error_log && ! opt_abort ) {
 if ( ! log_error_file_ptr [ 0 ] ) fn_format ( log_error_file , pidfile_name , mysql_data_home , ".err" , MY_REPLACE_EXT ) ;
 else fn_format ( log_error_file , log_error_file_ptr , mysql_data_home , ".err" , MY_UNPACK_FILENAME | MY_SAFE_PATH ) ;
 log_error_file_ptr = log_error_file ;
 if ( ! log_error_file [ 0 ] ) opt_error_log = 0 ;
 else {
 my_bool res ;





 }
 error_handler_hook = my_message_sql ;
 proc_info_hook = set_thd_proc_info ;

 buffered_logs . cleanup ( ) ;

 sql_print_error ( "Out of memory" ) ;
 unireg_abort ( 1 ) ;
 }
 if ( delegates_init ( ) ) unireg_abort ( 1 ) ;
 if ( ! opt_bin_log_used ) {
 if ( opt_log_slave_updates ) sql_print_warning ( "You need to use --log-bin to make " "--log-slave-updates work." ) ;
 if ( binlog_format_used ) sql_print_warning ( "You need to use --log-bin to make " "--binlog-format work." ) ;
 }
 DBUG_ASSERT ( ( uint ) global_system_variables . binlog_format <= array_elements ( binlog_format_names ) - 1 ) ;

 if ( opt_bin_log ) {
 sql_print_error ( "using --replicate-same-server-id in conjunction with \ --log-slave-updates is impossible, it would lead to infinite loops in this \ server." ) ;
 unireg_abort ( 1 ) ;
 }
 else sql_print_warning ( "using --replicate-same-server-id in conjunction with \ --log-slave-updates would lead to infinite loops in this server. However this \ will be ignored as the --log-bin option is not defined." ) ;
 }

 if ( opt_bin_log ) {
 if ( opt_bin_logname [ 0 ] && opt_bin_logname [ strlen ( opt_bin_logname ) - 1 ] == FN_LIBCHAR ) {
 sql_print_error ( "Path '%s' is a directory name, please specify \ a file name for --log-bin option" , opt_bin_logname ) ;
 unireg_abort ( 1 ) ;
 }
 if ( opt_binlog_index_name && opt_binlog_index_name [ strlen ( opt_binlog_index_name ) - 1 ] == FN_LIBCHAR ) {
 sql_print_error ( "Path '%s' is a directory name, please specify \ a file name for --log-bin-index option" , opt_binlog_index_name ) ;
 unireg_abort ( 1 ) ;
 }
 char buf [ FN_REFLEN ] ;
 const char * ln ;
 ln = mysql_bin_log . generate_name ( opt_bin_logname , "-bin" , 1 , buf ) ;
 if ( ! opt_bin_logname [ 0 ] && ! opt_binlog_index_name ) {
 sql_print_warning ( "No argument was provided to --log-bin and " "neither --log-basename or --log-bin-index where " "used;
 This may cause repliction to break when this " "server acts as a master and has its hostname " "changed! Please use '--log-basename=%s' or " "'--log-bin=%s' to avoid this problem." , opt_log_basename , ln ) ;
 }
 if ( ln == buf ) {
 opt_bin_logname = my_once_strdup ( buf , MYF ( MY_WME ) ) ;
 }
 if ( mysql_bin_log . open_index_file ( opt_binlog_index_name , ln , TRUE ) ) {
 unireg_abort ( 1 ) ;
 }
 }
 process_key_caches ( & ha_init_key_cache , 0 ) ;
 init_global_table_stats ( ) ;
 init_global_index_stats ( ) ;
 if ( ha_init_errors ( ) ) DBUG_RETURN ( 1 ) ;
 tc_log = 0 ;
 if ( plugin_init ( & remaining_argc , remaining_argv , ( opt_noacl ? PLUGIN_INIT_SKIP_PLUGIN_TABLE : 0 ) | ( opt_abort ? PLUGIN_INIT_SKIP_INITIALIZATION : 0 ) ) ) {
 sql_print_error ( "Failed to initialize plugins." ) ;
 unireg_abort ( 1 ) ;
 }
 plugins_are_initialized = TRUE ;
 have_csv = plugin_status ( STRING_WITH_LEN ( "csv" ) , MYSQL_STORAGE_ENGINE_PLUGIN ) ;
 have_ndbcluster = plugin_status ( STRING_WITH_LEN ( "ndbcluster" ) , MYSQL_STORAGE_ENGINE_PLUGIN ) ;
 have_partitioning = plugin_status ( STRING_WITH_LEN ( "partition" ) , MYSQL_STORAGE_ENGINE_PLUGIN ) ;
 if ( remaining_argc > 1 ) {
 int ho_error ;
 struct my_option no_opts [ ] = {
 {
 0 , 0 , 0 , 0 , 0 , 0 , GET_NO_ARG , NO_ARG , 0 , 0 , 0 , 0 , 0 , 0 }
 }
 ;
 my_getopt_skip_unknown = 0 ;
 if ( ( ho_error = handle_options ( & remaining_argc , & remaining_argv , no_opts , mysqld_get_one_option ) ) ) unireg_abort ( ho_error ) ;
 remaining_argc ++ ;
 remaining_argv -- ;
 my_getopt_skip_unknown = TRUE ;
 if ( remaining_argc > 1 ) {
 fprintf ( stderr , "%s: Too many arguments (first extra is '%s').\n" , my_progname , remaining_argv [ 1 ] ) ;
 unireg_abort ( 1 ) ;
 }
 }
 if ( opt_abort ) unireg_abort ( 0 ) ;
 if ( ! DEFAULT_ERRMSGS [ 0 ] [ 0 ] ) unireg_abort ( 1 ) ;
 if ( ha_init ( ) ) {
 sql_print_error ( "Can't init databases" ) ;
 unireg_abort ( 1 ) ;
 }
 if ( opt_bootstrap ) log_output_options = LOG_FILE ;
 else logger . init_log_tables ( ) ;
 if ( log_output_options & LOG_NONE ) {
 if ( ( log_output_options & LOG_NONE ) && ( log_output_options & ~ LOG_NONE ) ) sql_print_warning ( "There were other values specified to " "log-output besides NONE. Disabling slow " "and general logs anyway." ) ;
 logger . set_handlers ( LOG_FILE , LOG_NONE , LOG_NONE ) ;
 }
 else {
 LEX_STRING csv_name = {
 C_STRING_WITH_LEN ( "csv" ) }
 ;
 if ( ! plugin_is_ready ( & csv_name , MYSQL_STORAGE_ENGINE_PLUGIN ) ) {
 sql_print_error ( "CSV engine is not present, falling back to the " "log files" ) ;
 log_output_options = ( log_output_options & ~ LOG_TABLE ) | LOG_FILE ;
 }
 logger . set_handlers ( LOG_FILE , opt_slow_log ? log_output_options : LOG_NONE , opt_log ? log_output_options : LOG_NONE ) ;
 }
 LEX_STRING name = {
 default_storage_engine , strlen ( default_storage_engine ) }
 ;
 plugin_ref plugin ;
 handlerton * hton ;
 if ( ( plugin = ha_resolve_by_name ( 0 , & name ) ) ) hton = plugin_data ( plugin , handlerton * ) ;
 else {
 sql_print_error ( "Unknown/unsupported storage engine: %s" , default_storage_engine ) ;
 unireg_abort ( 1 ) ;
 }
 if ( ! ha_storage_engine_is_enabled ( hton ) ) {
 if ( ! opt_bootstrap ) {
 sql_print_error ( "Default storage engine (%s) is not available" , default_storage_engine ) ;
 unireg_abort ( 1 ) ;
 }
 DBUG_ASSERT ( global_system_variables . table_plugin ) ;
 }
 else {
 mysql_mutex_lock ( & LOCK_global_system_variables ) ;
 plugin_unlock ( 0 , global_system_variables . table_plugin ) ;
 global_system_variables . table_plugin = plugin ;
 mysql_mutex_unlock ( & LOCK_global_system_variables ) ;
 }

 sql_print_error ( "Aria engine is not enabled or did not start. The Aria engine must be enabled to continue as mysqld was configured with --with-aria-tmp-tables" ) ;
 unireg_abort ( 1 ) ;
 }
 internal_tmp_table_max_key_length = maria_max_key_length ( ) ;
 internal_tmp_table_max_key_segments = maria_max_key_segments ( ) ;

 internal_tmp_table_max_key_segments = myisam_max_key_segments ( ) ;

 if ( tc_log -> open ( opt_bin_log ? opt_bin_logname : opt_tc_log_file ) ) {
 sql_print_error ( "Can't init tc log" ) ;
 unireg_abort ( 1 ) ;
 }
 if ( ha_recover ( 0 ) ) {
 unireg_abort ( 1 ) ;
 }
 if ( opt_bin_log && mysql_bin_log . open ( opt_bin_logname , LOG_BIN , 0 , WRITE_CACHE , 0 , max_binlog_size , 0 , TRUE ) ) unireg_abort ( 1 ) ;

 time_t purge_time = server_start_time - expire_logs_days * 24 * 60 * 60 ;
 if ( purge_time >= 0 ) mysql_bin_log . purge_logs_before_date ( purge_time ) ;
 }


 if ( setreuid ( ( uid_t ) - 1 , 0 ) == - 1 ) {
 sql_perror ( "setreuid" ) ;
 unireg_abort ( 1 ) ;
 }
 if ( mlockall ( MCL_CURRENT ) ) {
 if ( global_system_variables . log_warnings ) sql_print_warning ( "Failed to lock memory. Errno: %d\n" , errno ) ;
 locked_in_memory = 0 ;
 }
 if ( user_info ) set_user ( mysqld_user , user_info ) ;
 }
 else # endif locked_in_memory = 0 ;
 ft_init_stopwords ( ) ;
 init_max_user_conn ( ) ;
 init_update_queries ( ) ;
 init_global_user_stats ( ) ;
 init_global_client_stats ( ) ;
 DBUG_RETURN ( 0 ) ;
 }