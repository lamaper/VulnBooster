void do_system ( struct st_command * command ) {
 DYNAMIC_STRING ds_cmd ;
 DBUG_ENTER ( "do_system" ) ;
 if ( strlen ( command -> first_argument ) == 0 ) {
 report_or_die ( "Missing arguments to system, nothing to do!" ) ;
 return ;
 }
 init_dynamic_string ( & ds_cmd , 0 , command -> query_len + 64 , 256 ) ;
 do_eval ( & ds_cmd , command -> first_argument , command -> end , ! is_windows ) ;


 if ( my_system ( & ds_cmd ) ) {
 if ( command -> abort_on_error ) report_or_die ( "system command '%s' failed" , command -> first_argument ) ;
 else {
 dynstr_append ( & ds_res , "system command '" ) ;
 replace_dynstr_append ( & ds_res , command -> first_argument ) ;
 dynstr_append ( & ds_res , "' failed\n" ) ;
 }
 }
 command -> last_argument = command -> end ;
 dynstr_free ( & ds_cmd ) ;
 DBUG_VOID_RETURN ;
 }