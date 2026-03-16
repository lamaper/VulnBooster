static void test_manual_sample ( ) {
 unsigned int param_count ;
 MYSQL_STMT * stmt ;
 short small_data ;
 int int_data ;
 int rc ;
 char str_data [ 50 ] ;
 ulonglong affected_rows ;
 MYSQL_BIND my_bind [ 3 ] ;
 my_bool is_null ;
 char query [ MAX_TEST_QUERY_LENGTH ] ;
 myheader ( "test_manual_sample" ) ;
 mysql_autocommit ( mysql , 1 ) ;
 if ( mysql_query ( mysql , "DROP TABLE IF EXISTS test_table" ) ) {
 fprintf ( stderr , "\n drop table failed" ) ;
 fprintf ( stderr , "\n %s" , mysql_error ( mysql ) ) ;
 exit ( 1 ) ;
 }
 if ( mysql_query ( mysql , "CREATE TABLE test_table(col1 int, col2 varchar(50), \ col3 smallint, \ col4 timestamp)" ) ) {
 fprintf ( stderr , "\n create table failed" ) ;
 fprintf ( stderr , "\n %s" , mysql_error ( mysql ) ) ;
 exit ( 1 ) ;
 }
 strmov ( query , "INSERT INTO test_table(col1, col2, col3) values(?, ?, ?)" ) ;
 if ( ! ( stmt = mysql_simple_prepare ( mysql , query ) ) ) {
 fprintf ( stderr , "\n prepare, insert failed" ) ;
 fprintf ( stderr , "\n %s" , mysql_error ( mysql ) ) ;
 exit ( 1 ) ;
 }
 if ( ! opt_silent ) fprintf ( stdout , "\n prepare, insert successful" ) ;
 param_count = mysql_stmt_param_count ( stmt ) ;
 if ( ! opt_silent ) fprintf ( stdout , "\n total parameters in insert: %d" , param_count ) ;
 if ( param_count != 3 ) {
 fprintf ( stderr , "\n invalid parameter count returned by MySQL" ) ;
 exit ( 1 ) ;
 }
 memset ( my_bind , 0 , sizeof ( my_bind ) ) ;
 my_bind [ 0 ] . buffer_type = MYSQL_TYPE_LONG ;
 my_bind [ 0 ] . buffer = ( void * ) & int_data ;
 my_bind [ 1 ] . buffer_type = MYSQL_TYPE_VAR_STRING ;
 my_bind [ 1 ] . buffer = ( void * ) str_data ;
 my_bind [ 1 ] . buffer_length = sizeof ( str_data ) ;
 my_bind [ 2 ] . buffer_type = MYSQL_TYPE_SHORT ;
 my_bind [ 2 ] . buffer = ( void * ) & small_data ;
 my_bind [ 2 ] . is_null = & is_null ;
 is_null = 0 ;
 if ( mysql_stmt_bind_param ( stmt , my_bind ) ) {
 fprintf ( stderr , "\n param bind failed" ) ;
 fprintf ( stderr , "\n %s" , mysql_stmt_error ( stmt ) ) ;
 exit ( 1 ) ;
 }
 int_data = 10 ;
 strmov ( str_data , "MySQL" ) ;
 is_null = 1 ;
 if ( mysql_stmt_execute ( stmt ) ) {
 fprintf ( stderr , "\n execute 1 failed" ) ;
 fprintf ( stderr , "\n %s" , mysql_stmt_error ( stmt ) ) ;
 exit ( 1 ) ;
 }
 affected_rows = mysql_stmt_affected_rows ( stmt ) ;
 if ( ! opt_silent ) fprintf ( stdout , "\n total affected rows: %ld" , ( ulong ) affected_rows ) ;
 if ( affected_rows != 1 ) {
 fprintf ( stderr , "\n invalid affected rows by MySQL" ) ;
 exit ( 1 ) ;
 }
 int_data = 1000 ;
 strmov ( str_data , "The most popular open source database" ) ;
 small_data = 1000 ;
 is_null = 0 ;
 if ( mysql_stmt_execute ( stmt ) ) {
 fprintf ( stderr , "\n execute 2 failed" ) ;
 fprintf ( stderr , "\n %s" , mysql_stmt_error ( stmt ) ) ;
 exit ( 1 ) ;
 }
 affected_rows = mysql_stmt_affected_rows ( stmt ) ;
 if ( ! opt_silent ) fprintf ( stdout , "\n total affected rows: %ld" , ( ulong ) affected_rows ) ;
 if ( affected_rows != 1 ) {
 fprintf ( stderr , "\n invalid affected rows by MySQL" ) ;
 exit ( 1 ) ;
 }
 if ( mysql_stmt_close ( stmt ) ) {
 fprintf ( stderr , "\n failed while closing the statement" ) ;
 fprintf ( stderr , "\n %s" , mysql_stmt_error ( stmt ) ) ;
 exit ( 1 ) ;
 }
 rc = my_stmt_result ( "SELECT * FROM test_table" ) ;
 DIE_UNLESS ( rc == 2 ) ;
 if ( mysql_query ( mysql , "DROP TABLE test_table" ) ) {
 fprintf ( stderr , "\n drop table failed" ) ;
 fprintf ( stderr , "\n %s" , mysql_error ( mysql ) ) ;
 exit ( 1 ) ;
 }
 if ( ! opt_silent ) fprintf ( stdout , "Success !!!" ) ;
 }