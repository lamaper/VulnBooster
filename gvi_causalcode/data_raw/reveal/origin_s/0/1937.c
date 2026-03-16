static void set_ports ( ) {
 char * env ;
 if ( ! mysqld_port && ! opt_disable_networking ) {
 mysqld_port = MYSQL_PORT ;

 if ( ( serv_ptr = getservbyname ( "mysql" , "tcp" ) ) ) mysqld_port = ntohs ( ( u_short ) serv_ptr -> s_port ) ;

 }
 if ( ! mysqld_unix_port ) {



 }
 }