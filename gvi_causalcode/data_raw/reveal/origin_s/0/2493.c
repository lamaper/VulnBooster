int main ( void ) {
 int result = OK ;
 process_cgivars ( ) ;
 reset_cgi_vars ( ) ;
 result = read_cgi_config_file ( get_cgi_config_location ( ) ) ;
 if ( result == ERROR ) {
 document_header ( CGI_ID , FALSE , "Error" ) ;
 print_error ( get_cgi_config_location ( ) , ERROR_CGI_CFG_FILE ) ;
 document_footer ( CGI_ID ) ;
 return ERROR ;
 }
 result = read_main_config_file ( main_config_file ) ;
 if ( result == ERROR ) {
 document_header ( CGI_ID , FALSE , "Error" ) ;
 print_error ( main_config_file , ERROR_CGI_MAIN_CFG ) ;
 document_footer ( CGI_ID ) ;
 return ERROR ;
 }
 strcpy ( command_file , get_cmd_file_location ( ) ) ;
 if ( strcmp ( start_time_string , "" ) ) string_to_time ( start_time_string , & start_time ) ;
 if ( strcmp ( end_time_string , "" ) ) string_to_time ( end_time_string , & end_time ) ;
 result = read_all_object_configuration_data ( main_config_file , READ_ALL_OBJECT_DATA ) ;
 if ( result == ERROR ) {
 document_header ( CGI_ID , FALSE , "Error" ) ;
 print_error ( NULL , ERROR_CGI_OBJECT_DATA ) ;
 document_footer ( CGI_ID ) ;
 return ERROR ;
 }
 result = read_all_status_data ( get_cgi_config_location ( ) , READ_ALL_STATUS_DATA ) ;
 if ( result == ERROR && daemon_check == TRUE ) {
 document_header ( CGI_ID , FALSE , "Error" ) ;
 print_error ( NULL , ERROR_CGI_STATUS_DATA ) ;
 document_footer ( CGI_ID ) ;
 free_memory ( ) ;
 return ERROR ;
 }
 document_header ( CGI_ID , TRUE , "External Command Interface" ) ;
 get_authentication_information ( & current_authdata ) ;
 if ( display_header == TRUE ) {
 printf ( "\n<!-- Image \"stop.png\" has been taken from \"http://fedoraproject.org/wiki/Template:Admon/caution\" -->\n\n" ) ;
 printf ( "<table border=0 width=100%%>\n" ) ;
 printf ( "<tr>\n" ) ;
 printf ( "<td align=left valign=top width=33%%>\n" ) ;
 display_info_table ( "External Command Interface" , & current_authdata , daemon_check ) ;
 printf ( "</td>\n" ) ;
 printf ( "<td align=center valign=top width=33%%>\n" ) ;
 printf ( "</td>\n" ) ;
 printf ( "<td align=right valign=bottom width=33%%>\n" ) ;
 printf ( "</td>\n" ) ;
 printf ( "</tr>\n" ) ;
 printf ( "</table>\n" ) ;
 }
 if ( command_type == CMD_NONE ) {
 print_generic_error_message ( "Error: No command was specified!" , NULL , 2 ) ;
 }
 else if ( is_authorized_for_read_only ( & current_authdata ) == TRUE ) {
 print_generic_error_message ( "Error: It appears as though you do not have permission to perform any commands!" , NULL , 1 ) ;
 }
 else if ( command_mode == CMDMODE_REQUEST ) request_command_data ( command_type ) ;
 else if ( command_mode == CMDMODE_COMMIT ) commit_command_data ( command_type ) ;
 document_footer ( CGI_ID ) ;
 free_memory ( ) ;
 free_object_data ( ) ;
 return OK ;
 }