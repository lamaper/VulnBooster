void clean_up ( bool print_message ) {
 DBUG_PRINT ( "exit" , ( "clean_up" ) ) ;
 if ( cleanup_done ++ ) return ;
 close_active_mi ( ) ;
 stop_handle_manager ( ) ;
 release_ddl_log ( ) ;
 ha_binlog_end ( current_thd ) ;
 logger . cleanup_base ( ) ;
 injector : : free_instance ( ) ;
 mysql_bin_log . cleanup ( ) ;


 my_dboptions_cache_free ( ) ;
 ignore_db_dirs_free ( ) ;

 acl_free ( 1 ) ;
 grant_free ( ) ;

 hostname_cache_free ( ) ;
 item_user_lock_free ( ) ;
 lex_free ( ) ;
 item_create_cleanup ( ) ;
 table_def_start_shutdown ( ) ;
 plugin_shutdown ( ) ;
 udf_free ( ) ;
 ha_end ( ) ;
 if ( tc_log ) tc_log -> close ( ) ;
 delegates_destroy ( ) ;
 xid_cache_free ( ) ;
 table_def_free ( ) ;
 mdl_destroy ( ) ;
 key_caches . delete_elements ( ( void ( * ) ( const char * , uchar * ) ) free_key_cache ) ;
 wt_end ( ) ;
 multi_keycache_free ( ) ;
 sp_cache_end ( ) ;
 free_status_vars ( ) ;
 end_thr_alarm ( 1 ) ;
 my_free_open_file_info ( ) ;
 if ( defaults_argv ) free_defaults ( defaults_argv ) ;
 free_tmpdir ( & mysql_tmpdir_list ) ;
 bitmap_free ( & temp_pool ) ;
 free_max_user_conn ( ) ;
 free_global_user_stats ( ) ;
 free_global_client_stats ( ) ;
 free_global_table_stats ( ) ;
 free_global_index_stats ( ) ;
 delete_dynamic ( & all_options ) ;


 delete binlog_filter ;
 delete rpl_filter ;
 end_ssl ( ) ;




 if ( print_message && my_default_lc_messages && server_start_time ) sql_print_information ( ER_DEFAULT ( ER_SHUTDOWN_COMPLETE ) , my_progname ) ;
 cleanup_errmsgs ( ) ;
 MYSQL_CALLBACK ( thread_scheduler , end , ( ) ) ;
 mysql_library_end ( ) ;
 finish_client_errs ( ) ;
 ( void ) my_error_unregister ( ER_ERROR_FIRST , ER_ERROR_LAST ) ;
 DBUG_PRINT ( "quit" , ( "Error messages freed" ) ) ;
 logger . cleanup_end ( ) ;
 sys_var_end ( ) ;
 my_atomic_rwlock_destroy ( & global_query_id_lock ) ;
 my_atomic_rwlock_destroy ( & thread_running_lock ) ;
 free_charsets ( ) ;
 mysql_mutex_lock ( & LOCK_thread_count ) ;
 DBUG_PRINT ( "quit" , ( "got thread count lock" ) ) ;
 ready_to_exit = 1 ;
 mysql_cond_broadcast ( & COND_thread_count ) ;
 mysql_mutex_unlock ( & LOCK_thread_count ) ;
 DBUG_PRINT ( "quit" , ( "done with cleanup" ) ) ;
 }