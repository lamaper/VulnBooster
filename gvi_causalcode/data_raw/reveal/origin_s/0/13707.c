static void test_bug15518 ( ) {
 MYSQL_STMT * stmt ;
 MYSQL * mysql1 ;
 int rc ;
 myheader ( "test_bug15518" ) ;
 mysql1 = mysql_client_init ( NULL ) ;
 if ( ! mysql_real_connect ( mysql1 , opt_host , opt_user , opt_password , opt_db ? opt_db : "test" , opt_port , opt_unix_socket , CLIENT_MULTI_STATEMENTS ) ) {
 fprintf ( stderr , "Failed to connect to the database\n" ) ;
 DIE_UNLESS ( 0 ) ;
 }
 stmt = mysql_stmt_init ( mysql1 ) ;
 rc = mysql_stmt_prepare ( stmt , "foo" , 3 ) ;
 if ( ! opt_silent ) fprintf ( stdout , "rc: %d, mysql_stmt_errno: %d, mysql_errno: %d\n" , rc , mysql_stmt_errno ( stmt ) , mysql_errno ( mysql1 ) ) ;
 DIE_UNLESS ( rc && mysql_stmt_errno ( stmt ) && mysql_errno ( mysql1 ) ) ;
 rc = mysql_stmt_prepare ( stmt , "SHOW STATUS" , 12 ) ;
 if ( ! opt_silent ) fprintf ( stdout , "rc: %d, mysql_stmt_errno: %d, mysql_errno: %d\n" , rc , mysql_stmt_errno ( stmt ) , mysql_errno ( mysql1 ) ) ;
 DIE_UNLESS ( ! rc || mysql_stmt_errno ( stmt ) || mysql_errno ( mysql1 ) ) ;
 mysql_stmt_close ( stmt ) ;
 DIE_UNLESS ( ! mysql_errno ( mysql1 ) ) ;
 stmt = mysql_stmt_init ( mysql1 ) ;
 rc = mysql_stmt_prepare ( stmt , "foo" , 3 ) ;
 if ( ! opt_silent ) fprintf ( stdout , "rc: %d, mysql_stmt_errno: %d, mysql_errno: %d\n" , rc , mysql_stmt_errno ( stmt ) , mysql_errno ( mysql1 ) ) ;
 DIE_UNLESS ( rc && mysql_stmt_errno ( stmt ) && mysql_errno ( mysql1 ) ) ;
 mysql_close ( mysql1 ) ;
 rc = mysql_stmt_prepare ( stmt , "SHOW STATUS" , 12 ) ;
 if ( ! opt_silent ) fprintf ( stdout , "rc: %d, mysql_stmt_errno: %d\n" , rc , mysql_stmt_errno ( stmt ) ) ;
 DIE_UNLESS ( rc && mysql_stmt_errno ( stmt ) ) ;
 mysql_stmt_close ( stmt ) ;
 }