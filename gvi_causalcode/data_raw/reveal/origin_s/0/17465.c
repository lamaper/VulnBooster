static void bug31418_impl ( ) {
 MYSQL con ;
 my_bool is_null ;
 int rc = 0 ;
 DIE_UNLESS ( mysql_client_init ( & con ) ) ;
 DIE_UNLESS ( mysql_real_connect ( & con , opt_host , opt_user , opt_password , opt_db ? opt_db : "test" , opt_port , opt_unix_socket , CLIENT_FOUND_ROWS ) ) ;
 is_null = query_int_variable ( & con , "IS_FREE_LOCK('bug31418')" , & rc ) ;
 DIE_UNLESS ( ! is_null && rc ) ;
 is_null = query_int_variable ( & con , "IS_USED_LOCK('bug31418')" , & rc ) ;
 DIE_UNLESS ( is_null ) ;
 query_int_variable ( & con , "GET_LOCK('bug31418', 1)" , & rc ) ;
 DIE_UNLESS ( rc ) ;
 is_null = query_int_variable ( & con , "IS_FREE_LOCK('bug31418')" , & rc ) ;
 DIE_UNLESS ( ! is_null && ! rc ) ;
 is_null = query_int_variable ( & con , "IS_USED_LOCK('bug31418')" , & rc ) ;
 DIE_UNLESS ( ! is_null && rc ) ;
 bug20023_change_user ( & con ) ;
 is_null = query_int_variable ( & con , "IS_FREE_LOCK('bug31418')" , & rc ) ;
 DIE_UNLESS ( ! is_null && rc ) ;
 is_null = query_int_variable ( & con , "IS_USED_LOCK('bug31418')" , & rc ) ;
 DIE_UNLESS ( is_null ) ;
 mysql_close ( & con ) ;
 }