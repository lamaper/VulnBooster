void do_close_connection ( struct st_command * command ) {
 DBUG_ENTER ( "do_close_connection" ) ;
 struct st_connection * con ;
 static DYNAMIC_STRING ds_connection ;
 const struct command_arg close_connection_args [ ] = {
 {
 "connection_name" , ARG_STRING , TRUE , & ds_connection , "Name of the connection to close." }
 }
 ;
 check_command_args ( command , command -> first_argument , close_connection_args , sizeof ( close_connection_args ) / sizeof ( struct command_arg ) , ' ' ) ;
 DBUG_PRINT ( "enter" , ( "connection name: '%s'" , ds_connection . str ) ) ;
 if ( ! ( con = find_connection_by_name ( ds_connection . str ) ) ) die ( "connection '%s' not found in connection pool" , ds_connection . str ) ;
 DBUG_PRINT ( "info" , ( "Closing connection %s" , con -> name ) ) ;

 if ( con -> mysql -> net . vio ) {
 vio_delete ( con -> mysql -> net . vio ) ;
 con -> mysql -> net . vio = 0 ;
 }
 }


 con -> stmt = 0 ;
 mysql_close ( con -> mysql ) ;
 con -> mysql = 0 ;
 if ( con -> util_mysql ) mysql_close ( con -> util_mysql ) ;
 con -> util_mysql = 0 ;
 con -> pending = FALSE ;
 my_free ( con -> name ) ;
 if ( ! ( con -> name = my_strdup ( "-closed_connection-" , MYF ( MY_WME ) ) ) ) die ( "Out of memory" ) ;
 if ( con == cur_con ) {
 var_set_int ( "$mysql_get_server_version" , 0xFFFFFFFF ) ;
 var_set_string ( "$CURRENT_CONNECTION" , con -> name ) ;
 }
 if ( ! disable_connect_log && ! disable_query_log ) {
 DYNAMIC_STRING * ds = & ds_res ;
 dynstr_append_mem ( ds , "disconnect " , 11 ) ;
 replace_dynstr_append ( ds , ds_connection . str ) ;
 dynstr_append_mem ( ds , ";
\n" , 2 ) ;
 }
 dynstr_free ( & ds_connection ) ;
 DBUG_VOID_RETURN ;
 }