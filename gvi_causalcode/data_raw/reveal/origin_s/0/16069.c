static int do_flush_tables_read_lock ( MYSQL * mysql_con ) {
 return ( mysql_query_with_error_report ( mysql_con , 0 , ( ( opt_master_data != 0 ) ? "FLUSH /*!40101 LOCAL */ TABLES" : "FLUSH TABLES" ) ) || mysql_query_with_error_report ( mysql_con , 0 , "FLUSH TABLES WITH READ LOCK" ) ) ;
 }