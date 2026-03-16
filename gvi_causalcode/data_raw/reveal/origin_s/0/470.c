static int com_go ( String * buffer , char * line __attribute__ ( ( unused ) ) ) {
 char buff [ 200 ] ;
 char time_buff [ 52 + 3 + 1 ] ;
 MYSQL_RES * result ;
 ulong timer , warnings = 0 ;
 uint error = 0 ;
 int err = 0 ;
 interrupted_query = 0 ;
 if ( ! status . batch ) {
 old_buffer = * buffer ;
 old_buffer . copy ( ) ;
 }
 LINT_INIT ( buff [ 0 ] ) ;
 remove_cntrl ( * buffer ) ;
 if ( buffer -> is_empty ( ) ) {
 if ( status . batch ) return 0 ;
 return put_info ( "No query specified\n" , INFO_ERROR ) ;
 }
 if ( ! connected && reconnect ( ) ) {
 buffer -> length ( 0 ) ;
 return opt_reconnect ? - 1 : 1 ;
 }
 if ( verbose ) ( void ) com_print ( buffer , 0 ) ;
 if ( skip_updates && ( buffer -> length ( ) < 4 || my_strnncoll ( charset_info , ( const uchar * ) buffer -> ptr ( ) , 4 , ( const uchar * ) "SET " , 4 ) ) ) {
 ( void ) put_info ( "Ignoring query to other database" , INFO_INFO ) ;
 return 0 ;
 }
 timer = start_timer ( ) ;
 executing_query = 1 ;
 error = mysql_real_query_for_lazy ( buffer -> ptr ( ) , buffer -> length ( ) ) ;
 report_progress_end ( ) ;

 buffer -> append ( vertical ? "\\G" : delimiter ) ;
 fix_history ( buffer ) ;
 }

 if ( error ) goto end ;
 do {
 char * pos ;
 if ( quick ) {
 if ( ! ( result = mysql_use_result ( & mysql ) ) && mysql_field_count ( & mysql ) ) {
 error = put_error ( & mysql ) ;
 goto end ;
 }
 }
 else {
 error = mysql_store_result_for_lazy ( & result ) ;
 if ( error ) goto end ;
 }
 if ( verbose >= 3 || ! opt_silent ) mysql_end_timer ( timer , time_buff ) ;
 else time_buff [ 0 ] = '\0' ;
 if ( result ) {
 if ( ! mysql_num_rows ( result ) && ! quick && ! column_types_flag ) {
 strmov ( buff , "Empty set" ) ;
 if ( opt_xml ) {
 init_pager ( ) ;
 print_table_data_xml ( result ) ;
 end_pager ( ) ;
 }
 }
 else {
 init_pager ( ) ;
 if ( opt_html ) print_table_data_html ( result ) ;
 else if ( opt_xml ) print_table_data_xml ( result ) ;
 else if ( vertical || ( auto_vertical_output && ( terminal_width < get_result_width ( result ) ) ) ) print_table_data_vertically ( result ) ;
 else if ( opt_silent && verbose <= 2 && ! output_tables ) print_tab_data ( result ) ;
 else print_table_data ( result ) ;
 sprintf ( buff , "%ld %s in set" , ( long ) mysql_num_rows ( result ) , ( long ) mysql_num_rows ( result ) == 1 ? "row" : "rows" ) ;
 end_pager ( ) ;
 if ( mysql_errno ( & mysql ) ) error = put_error ( & mysql ) ;
 }
 }
 else if ( mysql_affected_rows ( & mysql ) == ~ ( ulonglong ) 0 ) strmov ( buff , "Query OK" ) ;
 else sprintf ( buff , "Query OK, %ld %s affected" , ( long ) mysql_affected_rows ( & mysql ) , ( long ) mysql_affected_rows ( & mysql ) == 1 ? "row" : "rows" ) ;
 pos = strend ( buff ) ;
 if ( ( warnings = mysql_warning_count ( & mysql ) ) ) {
 * pos ++ = ',' ;
 * pos ++ = ' ' ;
 pos = int10_to_str ( warnings , pos , 10 ) ;
 pos = strmov ( pos , " warning" ) ;
 if ( warnings != 1 ) * pos ++ = 's' ;
 }
 strmov ( pos , time_buff ) ;
 put_info ( buff , INFO_RESULT ) ;
 if ( mysql_info ( & mysql ) ) put_info ( mysql_info ( & mysql ) , INFO_RESULT ) ;
 put_info ( "" , INFO_RESULT ) ;
 if ( result && ! mysql_eof ( result ) ) error = put_error ( & mysql ) ;
 else if ( unbuffered ) fflush ( stdout ) ;
 mysql_free_result ( result ) ;
 }
 while ( ! ( err = mysql_next_result ( & mysql ) ) ) ;
 if ( err >= 1 ) error = put_error ( & mysql ) ;
 end : if ( show_warnings == 1 && ( warnings >= 1 || error ) ) print_warnings ( ) ;
 if ( ! error && ! status . batch && ( mysql . server_status & SERVER_STATUS_DB_DROPPED ) ) get_current_db ( ) ;
 executing_query = 0 ;
 return error ;
 }