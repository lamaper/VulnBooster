static int check_consistent_binlog_pos ( char * binlog_pos_file , char * binlog_pos_offset ) {
 MYSQL_RES * res ;
 MYSQL_ROW row ;
 int found ;
 if ( mysql_query_with_error_report ( mysql , & res , "SHOW STATUS LIKE 'binlog_snapshot_%'" ) ) return 0 ;
 found = 0 ;
 while ( ( row = mysql_fetch_row ( res ) ) ) {
 if ( 0 == strcmp ( row [ 0 ] , "Binlog_snapshot_file" ) ) {
 if ( binlog_pos_file ) strmake ( binlog_pos_file , row [ 1 ] , FN_REFLEN - 1 ) ;
 found ++ ;
 }
 else if ( 0 == strcmp ( row [ 0 ] , "Binlog_snapshot_position" ) ) {
 if ( binlog_pos_offset ) strmake ( binlog_pos_offset , row [ 1 ] , LONGLONG_LEN ) ;
 found ++ ;
 }
 }
 mysql_free_result ( res ) ;
 return ( found == 2 ) ;
 }