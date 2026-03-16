int main ( int argc , char * * argv ) {
 char bin_log_name [ FN_REFLEN ] ;
 int exit_code ;
 int consistent_binlog_pos = 0 ;
 MY_INIT ( argv [ 0 ] ) ;
 sf_leaking_memory = 1 ;
 compatible_mode_normal_str [ 0 ] = 0 ;
 default_charset = ( char * ) mysql_universal_client_charset ;
 bzero ( ( char * ) & ignore_table , sizeof ( ignore_table ) ) ;
 exit_code = get_options ( & argc , & argv ) ;
 if ( exit_code ) {
 free_resources ( ) ;
 exit ( exit_code ) ;
 }
 sf_leaking_memory = 0 ;
 if ( opt_xml && ! opt_comments_used ) opt_comments = 0 ;
 if ( log_error_file ) {
 if ( ! ( stderror_file = freopen ( log_error_file , "a+" , stderr ) ) ) {
 free_resources ( ) ;
 exit ( EX_MYSQLERR ) ;
 }
 }
 if ( connect_to_db ( current_host , current_user , opt_password ) ) {
 free_resources ( ) ;
 exit ( EX_MYSQLERR ) ;
 }
 if ( ! path ) write_header ( md_result_file , * argv ) ;
 if ( opt_slave_data && do_stop_slave_sql ( mysql ) ) goto err ;
 if ( opt_single_transaction && opt_master_data ) {
 consistent_binlog_pos = check_consistent_binlog_pos ( NULL , NULL ) ;
 }
 if ( ( opt_lock_all_tables || ( opt_master_data && ! consistent_binlog_pos ) || ( opt_single_transaction && flush_logs ) ) && do_flush_tables_read_lock ( mysql ) ) goto err ;
 if ( opt_lock_all_tables || opt_master_data || ( opt_single_transaction && flush_logs ) || opt_delete_master_logs ) {
 if ( flush_logs || opt_delete_master_logs ) {
 if ( mysql_refresh ( mysql , REFRESH_LOG ) ) goto err ;
 verbose_msg ( "-- main : logs flushed successfully!\n" ) ;
 }
 flush_logs = 0 ;
 }
 if ( opt_delete_master_logs ) {
 if ( get_bin_log_name ( mysql , bin_log_name , sizeof ( bin_log_name ) ) ) goto err ;
 }
 if ( opt_single_transaction && start_transaction ( mysql ) ) goto err ;
 if ( opt_slave_apply && add_stop_slave ( ) ) goto err ;
 if ( opt_master_data && do_show_master_status ( mysql , consistent_binlog_pos ) ) goto err ;
 if ( opt_slave_data && do_show_slave_status ( mysql ) ) goto err ;
 if ( opt_single_transaction && do_unlock_tables ( mysql ) ) goto err ;
 if ( opt_alltspcs ) dump_all_tablespaces ( ) ;
 if ( extended_insert ) init_dynamic_string_checked ( & extended_row , "" , 1024 , 1024 ) ;
 if ( opt_alldbs ) {
 if ( ! opt_alltspcs && ! opt_notspcs ) dump_all_tablespaces ( ) ;
 dump_all_databases ( ) ;
 }
 else {
 int argument ;
 for ( argument = 0 ;
 argument < argc ;
 argument ++ ) {
 size_t argument_length = strlen ( argv [ argument ] ) ;
 if ( argument_length > NAME_LEN ) {
 die ( EX_CONSCHECK , "[ERROR] Argument '%s' is too long, it cannot be " "name for any table or database.\n" , argv [ argument ] ) ;
 }
 }
 if ( argc > 1 && ! opt_databases ) {
 if ( ! opt_alltspcs && ! opt_notspcs ) dump_tablespaces_for_tables ( * argv , ( argv + 1 ) , ( argc - 1 ) ) ;
 dump_selected_tables ( * argv , ( argv + 1 ) , ( argc - 1 ) ) ;
 }
 else {
 if ( ! opt_alltspcs && ! opt_notspcs ) dump_tablespaces_for_databases ( argv ) ;
 dump_databases ( argv ) ;
 }
 }
 if ( opt_slave_apply && add_slave_statements ( ) ) goto err ;
 if ( md_result_file && fflush ( md_result_file ) ) {
 if ( ! first_error ) first_error = EX_MYSQLERR ;
 goto err ;
 }
 if ( opt_delete_master_logs && purge_bin_logs_to ( mysql , bin_log_name ) ) goto err ;
 err : if ( opt_slave_data ) do_start_slave_sql ( mysql ) ;


 if ( ! path ) write_footer ( md_result_file ) ;
 free_resources ( ) ;
 if ( stderror_file ) fclose ( stderror_file ) ;
 return ( first_error ) ;
 }