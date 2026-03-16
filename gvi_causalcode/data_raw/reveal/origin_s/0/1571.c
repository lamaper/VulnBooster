my_bool mysqld_get_one_option ( int optid , const struct my_option * opt __attribute__ ( ( unused ) ) , char * argument ) {
 switch ( optid ) {
 case '#' : # ifndef DBUG_OFF if ( ! argument ) argument = ( char * ) default_dbug_option ;
 if ( argument [ 0 ] == '0' && ! argument [ 1 ] ) {
 DEBUGGER_OFF ;
 break ;
 }
 DEBUGGER_ON ;
 if ( argument [ 0 ] == '1' && ! argument [ 1 ] ) break ;
 DBUG_SET_INITIAL ( argument ) ;
 opt_endinfo = 1 ;


 case OPT_DEPRECATED_OPTION : sql_print_warning ( "'%s' is deprecated. It does nothing and exists only " "for compatiblity with old my.cnf files." , opt -> name ) ;
 break ;
 case 'a' : global_system_variables . sql_mode = MODE_ANSI ;
 global_system_variables . tx_isolation = ISO_SERIALIZABLE ;
 break ;
 case 'b' : strmake_buf ( mysql_home , argument ) ;
 break ;
 case 'C' : if ( default_collation_name == compiled_default_collation_name ) default_collation_name = 0 ;
 break ;
 case 'l' : WARN_DEPRECATED ( NULL , 7 , 0 , "--log" , "'--general-log'/'--general-log-file'" ) ;
 opt_log = 1 ;
 break ;
 case 'h' : strmake_buf ( mysql_real_data_home , argument ) ;
 mysql_real_data_home_ptr = mysql_real_data_home ;
 break ;
 case 'u' : if ( ! mysqld_user || ! strcmp ( mysqld_user , argument ) ) mysqld_user = argument ;
 else sql_print_warning ( "Ignoring user change to '%s' because the user was set to '%s' earlier on the command line\n" , argument , mysqld_user ) ;
 break ;
 case 'L' : strmake_buf ( lc_messages_dir , argument ) ;
 break ;
 case OPT_BINLOG_FORMAT : binlog_format_used = true ;
 break ;

 opt_abort = 1 ;
 break ;

 else if ( argument == disabled_my_option ) global_system_variables . log_warnings = 0L ;
 else global_system_variables . log_warnings = atoi ( argument ) ;
 break ;
 case 'T' : test_flags = argument ? ( uint ) atoi ( argument ) : 0 ;
 opt_endinfo = 1 ;
 break ;
 case OPT_THREAD_CONCURRENCY : WARN_DEPRECATED_NO_REPLACEMENT ( NULL , "THREAD_CONCURRENCY" ) ;
 break ;
 case ( int ) OPT_ISAM_LOG : opt_myisam_log = 1 ;
 break ;
 case ( int ) OPT_BIN_LOG : opt_bin_log = test ( argument != disabled_my_option ) ;
 opt_bin_log_used = 1 ;
 break ;
 case ( int ) OPT_LOG_BASENAME : {
 if ( opt_log_basename [ 0 ] == 0 || strchr ( opt_log_basename , FN_EXTCHAR ) || strchr ( opt_log_basename , FN_LIBCHAR ) ) {
 sql_print_error ( "Wrong argument for --log-basename. It can't be empty or contain '.' or '" FN_DIRSEP "'" ) ;
 return 1 ;
 }
 if ( log_error_file_ptr != disabled_my_option ) log_error_file_ptr = opt_log_basename ;
 make_default_log_name ( & opt_logname , ".log" , false ) ;
 make_default_log_name ( & opt_slow_logname , "-slow.log" , false ) ;
 make_default_log_name ( & opt_bin_logname , "-bin" , true ) ;
 make_default_log_name ( & opt_binlog_index_name , "-bin.index" , true ) ;
 make_default_log_name ( & opt_relay_logname , "-relay-bin" , true ) ;
 make_default_log_name ( & opt_relaylog_index_name , "-relay-bin.index" , true ) ;
 pidfile_name_ptr = pidfile_name ;
 strmake ( pidfile_name , argument , sizeof ( pidfile_name ) - 5 ) ;
 strmov ( fn_ext ( pidfile_name ) , ".pid" ) ;
 if ( ! opt_bin_logname || ! opt_relaylog_index_name || ! opt_logname || ! opt_slow_logname || ! pidfile_name_ptr ) return 1 ;
 break ;
 }

 rpl_filter -> add_ignore_db ( argument ) ;
 break ;
 }
 case ( int ) OPT_REPLICATE_DO_DB : {
 rpl_filter -> add_do_db ( argument ) ;
 break ;
 }
 case ( int ) OPT_REPLICATE_REWRITE_DB : {
 char * key = argument , * p , * val ;
 if ( ! ( p = strstr ( argument , "->" ) ) ) {
 sql_print_error ( "Bad syntax in replicate-rewrite-db - missing '->'!\n" ) ;
 return 1 ;
 }
 val = p -- ;
 while ( my_isspace ( mysqld_charset , * p ) && p > argument ) * p -- = 0 ;
 if ( p == argument ) {
 sql_print_error ( "Bad syntax in replicate-rewrite-db - empty FROM db!\n" ) ;
 return 1 ;
 }
 * val = 0 ;
 val += 2 ;
 while ( * val && my_isspace ( mysqld_charset , * val ) ) val ++ ;
 if ( ! * val ) {
 sql_print_error ( "Bad syntax in replicate-rewrite-db - empty TO db!\n" ) ;
 return 1 ;
 }
 rpl_filter -> add_db_rewrite ( key , val ) ;
 break ;
 }
 case ( int ) OPT_BINLOG_IGNORE_DB : {
 binlog_filter -> add_ignore_db ( argument ) ;
 break ;
 }
 case ( int ) OPT_BINLOG_DO_DB : {
 binlog_filter -> add_do_db ( argument ) ;
 break ;
 }
 case ( int ) OPT_REPLICATE_DO_TABLE : {
 if ( rpl_filter -> add_do_table ( argument ) ) {
 sql_print_error ( "Could not add do table rule '%s'!\n" , argument ) ;
 return 1 ;
 }
 break ;
 }
 case ( int ) OPT_REPLICATE_WILD_DO_TABLE : {
 if ( rpl_filter -> add_wild_do_table ( argument ) ) {
 sql_print_error ( "Could not add do table rule '%s'!\n" , argument ) ;
 return 1 ;
 }
 break ;
 }
 case ( int ) OPT_REPLICATE_WILD_IGNORE_TABLE : {
 if ( rpl_filter -> add_wild_ignore_table ( argument ) ) {
 sql_print_error ( "Could not add ignore table rule '%s'!\n" , argument ) ;
 return 1 ;
 }
 break ;
 }
 case ( int ) OPT_REPLICATE_IGNORE_TABLE : {
 if ( rpl_filter -> add_ignore_table ( argument ) ) {
 sql_print_error ( "Could not add ignore table rule '%s'!\n" , argument ) ;
 return 1 ;
 }
 break ;
 }

 opt_slow_log = 1 ;
 break ;
 case ( int ) OPT_SAFE : opt_specialflag |= SPECIAL_SAFE_MODE | SPECIAL_NO_NEW_FUNC ;
 delay_key_write_options = ( uint ) DELAY_KEY_WRITE_NONE ;
 myisam_recover_options = HA_RECOVER_DEFAULT ;
 ha_open_options &= ~ ( HA_OPEN_DELAY_KEY_WRITE ) ;


 break ;
 case ( int ) OPT_SKIP_PRIOR : opt_specialflag |= SPECIAL_NO_PRIOR ;
 sql_print_warning ( "The --skip-thread-priority startup option is deprecated " "and will be removed in MySQL 7.0. This option has no effect " "as the implied behavior is already the default." ) ;
 break ;
 case ( int ) OPT_SKIP_HOST_CACHE : opt_specialflag |= SPECIAL_NO_HOST_CACHE ;
 break ;
 case ( int ) OPT_SKIP_RESOLVE : opt_skip_name_resolve = 1 ;
 opt_specialflag |= SPECIAL_NO_RESOLVE ;
 break ;
 case ( int ) OPT_WANT_CORE : test_flags |= TEST_CORE_ON_SIGNAL ;
 break ;
 case OPT_CONSOLE : if ( opt_console ) opt_error_log = 0 ;
 break ;
 case OPT_BOOTSTRAP : opt_noacl = opt_bootstrap = 1 ;
 break ;
 case OPT_SERVER_ID : server_id_supplied = 1 ;
 break ;
 case OPT_ONE_THREAD : thread_handling = SCHEDULER_NO_THREADS ;
 break ;
 case OPT_LOWER_CASE_TABLE_NAMES : lower_case_table_names_used = 1 ;
 break ;

 opt_debug_sync_timeout = DEBUG_SYNC_DEFAULT_WAIT_TIMEOUT ;
 }
 break ;

 else global_system_variables . optimizer_switch &= ~ OPTIMIZER_SWITCH_ENGINE_CONDITION_PUSHDOWN ;
 break ;
 case OPT_LOG_ERROR : if ( argument == NULL ) log_error_file_ptr = const_cast < char * > ( "" ) ;
 break ;
 case OPT_MAX_LONG_DATA_SIZE : max_long_data_size_used = true ;
 break ;
 case OPT_IGNORE_DB_DIRECTORY : opt_ignore_db_dirs = NULL ;
 if ( * argument == 0 ) ignore_db_dirs_reset ( ) ;
 else {
 if ( push_ignored_db_dir ( argument ) ) {
 sql_print_error ( "Can't start server: " "cannot process --ignore-db-dir=%.*s" , FN_REFLEN , argument ) ;
 return 1 ;
 }
 }
 break ;
 }
 return 0 ;
 }