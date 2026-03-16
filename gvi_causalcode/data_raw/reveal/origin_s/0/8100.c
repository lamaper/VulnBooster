static int mysql_init_variables ( void ) {
 opt_skip_slave_start = opt_reckless_slave = 0 ;
 mysql_home [ 0 ] = pidfile_name [ 0 ] = log_error_file [ 0 ] = 0 ;


 opt_bin_log = opt_bin_log_used = 0 ;
 opt_disable_networking = opt_skip_show_db = 0 ;
 opt_skip_name_resolve = 0 ;
 opt_ignore_builtin_innodb = 0 ;
 opt_logname = opt_binlog_index_name = opt_slow_logname = 0 ;
 opt_log_basename = 0 ;
 opt_tc_log_file = ( char * ) "tc.log" ;
 opt_secure_auth = 0 ;
 opt_bootstrap = opt_myisam_log = 0 ;
 mqh_used = 0 ;
 kill_in_progress = 0 ;
 cleanup_done = 0 ;
 server_id_supplied = 0 ;
 test_flags = select_errors = dropping_tables = ha_open_options = 0 ;
 thread_count = thread_running = kill_cached_threads = wake_thread = 0 ;
 slave_open_temp_tables = 0 ;
 cached_thread_count = 0 ;
 opt_endinfo = using_udf_functions = 0 ;
 opt_using_transactions = 0 ;
 abort_loop = select_thread_in_use = signal_thread_in_use = 0 ;
 ready_to_exit = shutdown_in_progress = grant_option = 0 ;
 aborted_threads = aborted_connects = 0 ;
 subquery_cache_miss = subquery_cache_hit = 0 ;
 delayed_insert_threads = delayed_insert_writes = delayed_rows_in_use = 0 ;
 delayed_insert_errors = thread_created = 0 ;
 specialflag = 0 ;
 binlog_cache_use = binlog_cache_disk_use = 0 ;
 max_used_connections = slow_launch_threads = 0 ;
 mysqld_user = mysqld_chroot = opt_init_file = opt_bin_logname = 0 ;
 prepared_stmt_count = 0 ;
 mysqld_unix_port = opt_mysql_tmpdir = my_bind_addr_str = NullS ;
 bzero ( ( uchar * ) & mysql_tmpdir_list , sizeof ( mysql_tmpdir_list ) ) ;
 bzero ( ( char * ) & global_status_var , sizeof ( global_status_var ) ) ;
 opt_large_pages = 0 ;
 opt_super_large_pages = 0 ;


 system_charset_info = & my_charset_utf8_general_ci ;
 files_charset_info = & my_charset_utf8_general_ci ;
 national_charset_info = & my_charset_utf8_general_ci ;
 table_alias_charset = & my_charset_bin ;
 character_set_filesystem = & my_charset_bin ;
 opt_specialflag = SPECIAL_ENGLISH ;
 unix_sock = base_ip_sock = extra_ip_sock = INVALID_SOCKET ;
 mysql_home_ptr = mysql_home ;
 pidfile_name_ptr = pidfile_name ;
 log_error_file_ptr = log_error_file ;
 protocol_version = PROTOCOL_VERSION ;
 what_to_log = ~ ( 1L << ( uint ) COM_TIME ) ;
 refresh_version = 2L ;
 executed_events = 0 ;
 global_query_id = thread_id = 1L ;
 my_atomic_rwlock_init ( & global_query_id_lock ) ;
 my_atomic_rwlock_init ( & thread_running_lock ) ;
 strnmov ( server_version , MYSQL_SERVER_VERSION , sizeof ( server_version ) - 1 ) ;
 threads . empty ( ) ;
 thread_cache . empty ( ) ;
 key_caches . empty ( ) ;
 if ( ! ( dflt_key_cache = get_or_create_key_cache ( default_key_cache_base . str , default_key_cache_base . length ) ) ) {
 sql_print_error ( "Cannot allocate the keycache" ) ;
 return 1 ;
 }
 multi_keycache_init ( ) ;
 mysql_real_data_home_len = strmake_buf ( mysql_real_data_home , get_relative_path ( MYSQL_DATADIR ) ) - mysql_real_data_home ;
 master_info_file = ( char * ) "master.info" , relay_log_info_file = ( char * ) "relay-log.info" ;
 report_user = report_password = report_host = 0 ;
 opt_relay_logname = opt_relaylog_index_name = 0 ;
 charsets_dir = 0 ;
 default_character_set_name = ( char * ) MYSQL_DEFAULT_CHARSET_NAME ;
 default_collation_name = compiled_default_collation_name ;
 character_set_filesystem_name = ( char * ) "binary" ;
 lc_messages = ( char * ) "en_US" ;
 lc_time_names_name = ( char * ) "en_US" ;

 current_dbug_option = default_dbug_option ;
























 char prg_dev [ LIBLEN ] ;
 char executing_path_name [ LIBLEN ] ;
 if ( ! test_if_hard_path ( my_progname ) ) {
 GetModuleFileName ( NULL , executing_path_name , sizeof ( executing_path_name ) ) ;
 my_path ( prg_dev , executing_path_name , NULL ) ;
 }
 else my_path ( prg_dev , my_progname , "mysql/bin" ) ;
 strcat ( prg_dev , "/../" ) ;
 cleanup_dirname ( mysql_home , prg_dev ) ;
 }

 if ( ! ( tmpenv = getenv ( "MY_BASEDIR_VERSION" ) ) ) tmpenv = DEFAULT_MYSQL_HOME ;
 strmake_buf ( mysql_home , tmpenv ) ;

 }