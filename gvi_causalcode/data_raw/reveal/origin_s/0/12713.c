void close_connections ( ) {
 DBUG_ENTER ( "close_connections" ) ;
 for ( -- next_con ;
 next_con >= connections ;
 -- next_con ) {


 next_con -> stmt = 0 ;
 mysql_close ( next_con -> mysql ) ;
 next_con -> mysql = 0 ;
 if ( next_con -> util_mysql ) mysql_close ( next_con -> util_mysql ) ;
 my_free ( next_con -> name ) ;
 }
 my_free ( connections ) ;
 DBUG_VOID_RETURN ;
 }