void set_current_connection ( struct st_connection * con ) {
 cur_con = con ;
 var_set_int ( "$mysql_get_server_version" , mysql_get_server_version ( con -> mysql ) ) ;
 var_set_string ( "$CURRENT_CONNECTION" , con -> name ) ;
 }