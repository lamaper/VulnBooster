static int do_show_slave_status ( MYSQL * mysql_con ) {
 MYSQL_RES * slave = 0 ;
 const char * comment_prefix = ( opt_slave_data == MYSQL_OPT_SLAVE_DATA_COMMENTED_SQL ) ? "-- " : "" ;
 if ( mysql_query_with_error_report ( mysql_con , & slave , "SHOW SLAVE STATUS" ) ) {
 if ( ! ignore_errors ) {
 fprintf ( stderr , "%s: Error: Slave not set up\n" , my_progname_short ) ;
 }
 mysql_free_result ( slave ) ;
 return 1 ;
 }
 else {
 MYSQL_ROW row = mysql_fetch_row ( slave ) ;
 if ( row && row [ 9 ] && row [ 21 ] ) {
 if ( opt_comments ) fprintf ( md_result_file , "\n--\n-- Position to start replication or point-in-time " "recovery from (the master of this slave)\n--\n\n" ) ;
 fprintf ( md_result_file , "%sCHANGE MASTER TO " , comment_prefix ) ;
 if ( opt_include_master_host_port ) {
 if ( row [ 1 ] ) fprintf ( md_result_file , "MASTER_HOST='%s', " , row [ 1 ] ) ;
 if ( row [ 3 ] ) fprintf ( md_result_file , "MASTER_PORT=%s, " , row [ 3 ] ) ;
 }
 fprintf ( md_result_file , "MASTER_LOG_FILE='%s', MASTER_LOG_POS=%s;
\n" , row [ 9 ] , row [ 21 ] ) ;
 check_io ( md_result_file ) ;
 }
 mysql_free_result ( slave ) ;
 }
 return 0 ;
 }