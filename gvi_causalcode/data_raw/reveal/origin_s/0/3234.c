static int do_show_master_status ( MYSQL * mysql_con , int consistent_binlog_pos ) {
 MYSQL_ROW row ;
 MYSQL_RES * UNINIT_VAR ( master ) ;
 char binlog_pos_file [ FN_REFLEN ] ;
 char binlog_pos_offset [ LONGLONG_LEN + 1 ] ;
 char * file , * offset ;
 const char * comment_prefix = ( opt_master_data == MYSQL_OPT_MASTER_DATA_COMMENTED_SQL ) ? "-- " : "" ;
 if ( consistent_binlog_pos ) {
 if ( ! check_consistent_binlog_pos ( binlog_pos_file , binlog_pos_offset ) ) return 1 ;
 file = binlog_pos_file ;
 offset = binlog_pos_offset ;
 }
 else {
 if ( mysql_query_with_error_report ( mysql_con , & master , "SHOW MASTER STATUS" ) ) return 1 ;
 row = mysql_fetch_row ( master ) ;
 if ( row && row [ 0 ] && row [ 1 ] ) {
 file = row [ 0 ] ;
 offset = row [ 1 ] ;
 }
 else {
 mysql_free_result ( master ) ;
 if ( ! ignore_errors ) {
 fprintf ( stderr , "%s: Error: Binlogging on server not active\n" , my_progname_short ) ;
 maybe_exit ( EX_MYSQLERR ) ;
 return 1 ;
 }
 else {
 return 0 ;
 }
 }
 }
 print_comment ( md_result_file , 0 , "\n--\n-- Position to start replication or point-in-time " "recovery from\n--\n\n" ) ;
 fprintf ( md_result_file , "%sCHANGE MASTER TO MASTER_LOG_FILE='%s', MASTER_LOG_POS=%s;
\n" , comment_prefix , file , offset ) ;
 check_io ( md_result_file ) ;
 if ( ! consistent_binlog_pos ) mysql_free_result ( master ) ;
 return 0 ;
 }