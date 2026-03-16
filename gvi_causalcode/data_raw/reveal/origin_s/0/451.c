static void test_bug10760 ( ) {
 MYSQL_STMT * stmt ;
 MYSQL_BIND my_bind [ 1 ] ;
 int rc ;
 const char * stmt_text ;
 char id_buf [ 20 ] ;
 ulong id_len ;
 int i = 0 ;
 ulong type ;
 myheader ( "test_bug10760" ) ;
 mysql_query ( mysql , "drop table if exists t1, t2" ) ;
 rc = mysql_query ( mysql , "create table t1 (id integer not null primary key)" " engine=MyISAM" ) ;
 myquery ( rc ) ;
 for ( ;
 i < 42 ;
 ++ i ) {
 char buf [ 100 ] ;
 sprintf ( buf , "insert into t1 (id) values (%d)" , i + 1 ) ;
 rc = mysql_query ( mysql , buf ) ;
 myquery ( rc ) ;
 }
 mysql_autocommit ( mysql , FALSE ) ;
 stmt = mysql_stmt_init ( mysql ) ;
 type = ( ulong ) CURSOR_TYPE_READ_ONLY ;
 mysql_stmt_attr_set ( stmt , STMT_ATTR_CURSOR_TYPE , ( const void * ) & type ) ;
 stmt_text = "select id from t1 order by 1" ;
 rc = mysql_stmt_prepare ( stmt , stmt_text , strlen ( stmt_text ) ) ;
 check_execute ( stmt , rc ) ;
 rc = mysql_stmt_execute ( stmt ) ;
 check_execute ( stmt , rc ) ;
 rc = mysql_query ( mysql , "update t1 set id=id+100" ) ;
 if ( rc && ! opt_silent ) printf ( "Got error (as expected): %s\n" , mysql_error ( mysql ) ) ;
 rc = mysql_rollback ( mysql ) ;
 myquery ( rc ) ;
 rc = mysql_stmt_fetch ( stmt ) ;
 check_execute ( stmt , rc ) ;
 if ( ! have_innodb ) {
 if ( ! opt_silent ) printf ( "Testing that cursors are closed at COMMIT/ROLLBACK requires " "InnoDB.\n" ) ;
 }
 else {
 stmt_text = "select id from t1 order by 1" ;
 rc = mysql_stmt_prepare ( stmt , stmt_text , strlen ( stmt_text ) ) ;
 check_execute ( stmt , rc ) ;
 rc = mysql_query ( mysql , "alter table t1 engine=InnoDB" ) ;
 myquery ( rc ) ;
 memset ( my_bind , 0 , sizeof ( my_bind ) ) ;
 my_bind [ 0 ] . buffer_type = MYSQL_TYPE_STRING ;
 my_bind [ 0 ] . buffer = ( void * ) id_buf ;
 my_bind [ 0 ] . buffer_length = sizeof ( id_buf ) ;
 my_bind [ 0 ] . length = & id_len ;
 check_execute ( stmt , rc ) ;
 mysql_stmt_bind_result ( stmt , my_bind ) ;
 rc = mysql_stmt_execute ( stmt ) ;
 rc = mysql_stmt_fetch ( stmt ) ;
 DIE_UNLESS ( rc == 0 ) ;
 if ( ! opt_silent ) printf ( "Fetched row %s\n" , id_buf ) ;
 rc = mysql_rollback ( mysql ) ;
 myquery ( rc ) ;

 DIE_UNLESS ( rc ) ;
 if ( ! opt_silent ) printf ( "Got error (as expected): %s\n" , mysql_error ( mysql ) ) ;

 mysql_stmt_close ( stmt ) ;
 rc = mysql_query ( mysql , "drop table t1" ) ;
 myquery ( rc ) ;
 mysql_autocommit ( mysql , TRUE ) ;
 }