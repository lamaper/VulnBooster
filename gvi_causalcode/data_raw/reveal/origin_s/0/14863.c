void commit_command_data ( int cmd ) {
 char error_string [ MAX_INPUT_BUFFER ] ;
 service * temp_service ;
 host * temp_host ;
 hostgroup * temp_hostgroup ;
 comment * temp_comment ;
 scheduled_downtime * temp_downtime ;
 servicegroup * temp_servicegroup = NULL ;
 contact * temp_contact = NULL ;
 int x = 0 ;
 int e = 0 ;
 short error_found = FALSE ;
 short cmd_has_objects = FALSE ;
 short row_color = 0 ;
 get_authentication_information ( & current_authdata ) ;
 is_authorized [ x ] = FALSE ;
 if ( lock_author_names == TRUE ) {
 temp_contact = find_contact ( current_authdata . username ) ;
 if ( temp_contact != NULL && temp_contact -> alias != NULL ) comment_author = temp_contact -> alias ;
 else comment_author = current_authdata . username ;
 }
 switch ( cmd ) {
 case CMD_ADD_HOST_COMMENT : case CMD_ADD_SVC_COMMENT : case CMD_ACKNOWLEDGE_HOST_PROBLEM : case CMD_ACKNOWLEDGE_SVC_PROBLEM : case CMD_SEND_CUSTOM_HOST_NOTIFICATION : case CMD_SEND_CUSTOM_SVC_NOTIFICATION : check_comment_sanity ( & e ) ;
 clean_comment_data ( comment_author ) ;
 clean_comment_data ( comment_data ) ;
 if ( use_ack_end_time == TRUE && ( cmd == CMD_ACKNOWLEDGE_HOST_PROBLEM || cmd == CMD_ACKNOWLEDGE_SVC_PROBLEM ) ) {
 time ( & start_time ) ;
 check_time_sanity ( & e ) ;
 }
 else end_time = 0L ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 cmd_has_objects = TRUE ;
 if ( commands [ x ] . host_name == NULL ) continue ;
 is_authorized [ x ] = FALSE ;
 if ( cmd == CMD_ADD_HOST_COMMENT || cmd == CMD_ACKNOWLEDGE_HOST_PROBLEM || cmd == CMD_SEND_CUSTOM_HOST_NOTIFICATION ) {
 temp_host = find_host ( commands [ x ] . host_name ) ;
 if ( is_authorized_for_host_commands ( temp_host , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 else {
 temp_service = find_service ( commands [ x ] . host_name , commands [ x ] . description ) ;
 if ( is_authorized_for_service_commands ( temp_service , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 }
 break ;
 case CMD_DEL_HOST_COMMENT : case CMD_DEL_SVC_COMMENT : if ( enforce_comments_on_actions == TRUE ) {
 check_comment_sanity ( & e ) ;
 clean_comment_data ( comment_author ) ;
 clean_comment_data ( comment_data ) ;
 }
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 cmd_has_objects = TRUE ;
 if ( multi_ids [ x ] == FALSE ) continue ;
 if ( multi_ids [ x ] == 0 ) {
 error [ e ++ ] . message = strdup ( "Comment id cannot be 0" ) ;
 continue ;
 }
 if ( cmd == CMD_DEL_HOST_COMMENT ) temp_comment = find_host_comment ( multi_ids [ x ] ) ;
 else temp_comment = find_service_comment ( multi_ids [ x ] ) ;
 is_authorized [ x ] = FALSE ;
 if ( cmd == CMD_DEL_HOST_COMMENT && temp_comment != NULL ) {
 temp_host = find_host ( temp_comment -> host_name ) ;
 if ( is_authorized_for_host_commands ( temp_host , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 if ( cmd == CMD_DEL_SVC_COMMENT && temp_comment != NULL ) {
 temp_service = find_service ( temp_comment -> host_name , temp_comment -> service_description ) ;
 if ( is_authorized_for_service_commands ( temp_service , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 }
 free_comment_data ( ) ;
 break ;
 case CMD_DEL_HOST_DOWNTIME : case CMD_DEL_SVC_DOWNTIME : if ( enforce_comments_on_actions == TRUE ) {
 check_comment_sanity ( & e ) ;
 clean_comment_data ( comment_author ) ;
 clean_comment_data ( comment_data ) ;
 }
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 cmd_has_objects = TRUE ;
 if ( multi_ids [ x ] == FALSE ) continue ;
 if ( multi_ids [ x ] == 0 ) {
 error [ e ++ ] . message = strdup ( "Downtime id cannot be 0" ) ;
 continue ;
 }
 if ( cmd == CMD_DEL_HOST_DOWNTIME ) temp_downtime = find_host_downtime ( multi_ids [ x ] ) ;
 else temp_downtime = find_service_downtime ( multi_ids [ x ] ) ;
 is_authorized [ x ] = FALSE ;
 if ( cmd == CMD_DEL_HOST_DOWNTIME && temp_downtime != NULL ) {
 temp_host = find_host ( temp_downtime -> host_name ) ;
 if ( is_authorized_for_host_commands ( temp_host , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 if ( cmd == CMD_DEL_SVC_DOWNTIME && temp_downtime != NULL ) {
 temp_service = find_service ( temp_downtime -> host_name , temp_downtime -> service_description ) ;
 if ( is_authorized_for_service_commands ( temp_service , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 }
 free_downtime_data ( ) ;
 break ;
 case CMD_SCHEDULE_SVC_CHECK : case CMD_ENABLE_SVC_CHECK : case CMD_DISABLE_SVC_CHECK : case CMD_DEL_ALL_SVC_COMMENTS : case CMD_ENABLE_SVC_NOTIFICATIONS : case CMD_DISABLE_SVC_NOTIFICATIONS : case CMD_ENABLE_PASSIVE_SVC_CHECKS : case CMD_DISABLE_PASSIVE_SVC_CHECKS : case CMD_ENABLE_SVC_EVENT_HANDLER : case CMD_DISABLE_SVC_EVENT_HANDLER : case CMD_REMOVE_SVC_ACKNOWLEDGEMENT : case CMD_PROCESS_SERVICE_CHECK_RESULT : case CMD_SCHEDULE_SVC_DOWNTIME : case CMD_DELAY_SVC_NOTIFICATION : case CMD_ENABLE_SVC_FLAP_DETECTION : case CMD_DISABLE_SVC_FLAP_DETECTION : case CMD_START_OBSESSING_OVER_SVC : case CMD_STOP_OBSESSING_OVER_SVC : if ( cmd == CMD_SCHEDULE_SVC_DOWNTIME || enforce_comments_on_actions == TRUE ) {
 check_comment_sanity ( & e ) ;
 if ( cmd == CMD_SCHEDULE_SVC_DOWNTIME ) check_time_sanity ( & e ) ;
 clean_comment_data ( comment_author ) ;
 clean_comment_data ( comment_data ) ;
 }
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 cmd_has_objects = TRUE ;
 if ( commands [ x ] . host_name == NULL || commands [ x ] . description == NULL ) continue ;
 is_authorized [ x ] = FALSE ;
 temp_service = find_service ( commands [ x ] . host_name , commands [ x ] . description ) ;
 if ( is_authorized_for_service_commands ( temp_service , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 if ( cmd == CMD_PROCESS_SERVICE_CHECK_RESULT && ! strcmp ( plugin_output , "" ) ) error [ e ++ ] . message = strdup ( "Check output cannot be blank" ) ;
 if ( cmd == CMD_DELAY_SVC_NOTIFICATION && notification_delay <= 0 ) error [ e ++ ] . message = strdup ( "Notification delay must be greater than 0" ) ;
 if ( cmd == CMD_SCHEDULE_SVC_CHECK && start_time == ( time_t ) 0 ) error [ e ++ ] . message = strdup ( "Start time must be non-zero or bad format has been submitted" ) ;
 break ;
 case CMD_ENABLE_NOTIFICATIONS : case CMD_DISABLE_NOTIFICATIONS : case CMD_SHUTDOWN_PROCESS : case CMD_RESTART_PROCESS : case CMD_START_EXECUTING_SVC_CHECKS : case CMD_STOP_EXECUTING_SVC_CHECKS : case CMD_START_ACCEPTING_PASSIVE_SVC_CHECKS : case CMD_STOP_ACCEPTING_PASSIVE_SVC_CHECKS : case CMD_ENABLE_EVENT_HANDLERS : case CMD_DISABLE_EVENT_HANDLERS : case CMD_START_OBSESSING_OVER_SVC_CHECKS : case CMD_STOP_OBSESSING_OVER_SVC_CHECKS : case CMD_ENABLE_FLAP_DETECTION : case CMD_DISABLE_FLAP_DETECTION : case CMD_ENABLE_FAILURE_PREDICTION : case CMD_DISABLE_FAILURE_PREDICTION : case CMD_ENABLE_PERFORMANCE_DATA : case CMD_DISABLE_PERFORMANCE_DATA : case CMD_START_EXECUTING_HOST_CHECKS : case CMD_STOP_EXECUTING_HOST_CHECKS : case CMD_START_ACCEPTING_PASSIVE_HOST_CHECKS : case CMD_STOP_ACCEPTING_PASSIVE_HOST_CHECKS : case CMD_START_OBSESSING_OVER_HOST_CHECKS : case CMD_STOP_OBSESSING_OVER_HOST_CHECKS : if ( use_disabled_notif_end_time == TRUE && cmd == CMD_DISABLE_NOTIFICATIONS ) {
 time ( & start_time ) ;
 check_time_sanity ( & e ) ;
 }
 else end_time = 0L ;
 if ( enforce_comments_on_actions == TRUE ) {
 check_comment_sanity ( & e ) ;
 clean_comment_data ( comment_author ) ;
 clean_comment_data ( comment_data ) ;
 }
 is_authorized [ x ] = FALSE ;
 if ( is_authorized_for_system_commands ( & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 break ;
 case CMD_ENABLE_HOST_SVC_CHECKS : case CMD_DISABLE_HOST_SVC_CHECKS : case CMD_DEL_ALL_HOST_COMMENTS : case CMD_SCHEDULE_HOST_SVC_CHECKS : case CMD_ENABLE_HOST_NOTIFICATIONS : case CMD_DISABLE_HOST_NOTIFICATIONS : case CMD_ENABLE_ALL_NOTIFICATIONS_BEYOND_HOST : case CMD_DISABLE_ALL_NOTIFICATIONS_BEYOND_HOST : case CMD_ENABLE_HOST_SVC_NOTIFICATIONS : case CMD_DISABLE_HOST_SVC_NOTIFICATIONS : case CMD_ENABLE_HOST_EVENT_HANDLER : case CMD_DISABLE_HOST_EVENT_HANDLER : case CMD_ENABLE_HOST_CHECK : case CMD_DISABLE_HOST_CHECK : case CMD_REMOVE_HOST_ACKNOWLEDGEMENT : case CMD_SCHEDULE_HOST_DOWNTIME : case CMD_SCHEDULE_HOST_SVC_DOWNTIME : case CMD_DELAY_HOST_NOTIFICATION : case CMD_ENABLE_HOST_FLAP_DETECTION : case CMD_DISABLE_HOST_FLAP_DETECTION : case CMD_PROCESS_HOST_CHECK_RESULT : case CMD_ENABLE_PASSIVE_HOST_CHECKS : case CMD_DISABLE_PASSIVE_HOST_CHECKS : case CMD_SCHEDULE_HOST_CHECK : case CMD_START_OBSESSING_OVER_HOST : case CMD_STOP_OBSESSING_OVER_HOST : case CMD_DEL_DOWNTIME_BY_HOST_NAME : if ( cmd == CMD_SCHEDULE_HOST_DOWNTIME || cmd == CMD_SCHEDULE_HOST_SVC_DOWNTIME || enforce_comments_on_actions == TRUE ) {
 check_comment_sanity ( & e ) ;
 if ( cmd == CMD_SCHEDULE_HOST_DOWNTIME || cmd == CMD_SCHEDULE_HOST_SVC_DOWNTIME ) check_time_sanity ( & e ) ;
 clean_comment_data ( comment_author ) ;
 clean_comment_data ( comment_data ) ;
 }
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 cmd_has_objects = TRUE ;
 if ( commands [ x ] . host_name == NULL ) continue ;
 is_authorized [ x ] = FALSE ;
 temp_host = find_host ( commands [ x ] . host_name ) ;
 if ( is_authorized_for_host_commands ( temp_host , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 if ( cmd == CMD_DELAY_HOST_NOTIFICATION && notification_delay <= 0 ) error [ e ++ ] . message = strdup ( "Notification delay must be greater than 0" ) ;
 if ( ( cmd == CMD_SCHEDULE_HOST_CHECK || cmd == CMD_SCHEDULE_HOST_SVC_CHECKS ) && start_time == ( time_t ) 0 ) error [ e ++ ] . message = strdup ( "Start time must be non-zero or bad format has been submitted" ) ;
 if ( cmd == CMD_PROCESS_HOST_CHECK_RESULT && ! strcmp ( plugin_output , "" ) ) error [ e ++ ] . message = strdup ( "Check output cannot be blank" ) ;
 break ;
 case CMD_ENABLE_HOSTGROUP_SVC_NOTIFICATIONS : case CMD_DISABLE_HOSTGROUP_SVC_NOTIFICATIONS : case CMD_ENABLE_HOSTGROUP_HOST_NOTIFICATIONS : case CMD_DISABLE_HOSTGROUP_HOST_NOTIFICATIONS : case CMD_ENABLE_HOSTGROUP_SVC_CHECKS : case CMD_DISABLE_HOSTGROUP_SVC_CHECKS : case CMD_SCHEDULE_HOSTGROUP_HOST_DOWNTIME : case CMD_SCHEDULE_HOSTGROUP_SVC_DOWNTIME : case CMD_ENABLE_SERVICEGROUP_SVC_NOTIFICATIONS : case CMD_DISABLE_SERVICEGROUP_SVC_NOTIFICATIONS : case CMD_ENABLE_SERVICEGROUP_HOST_NOTIFICATIONS : case CMD_DISABLE_SERVICEGROUP_HOST_NOTIFICATIONS : case CMD_ENABLE_SERVICEGROUP_SVC_CHECKS : case CMD_DISABLE_SERVICEGROUP_SVC_CHECKS : case CMD_SCHEDULE_SERVICEGROUP_HOST_DOWNTIME : case CMD_SCHEDULE_SERVICEGROUP_SVC_DOWNTIME : if ( cmd == CMD_SCHEDULE_SERVICEGROUP_HOST_DOWNTIME || cmd == CMD_SCHEDULE_SERVICEGROUP_SVC_DOWNTIME || cmd == CMD_SCHEDULE_HOSTGROUP_HOST_DOWNTIME || cmd == CMD_SCHEDULE_HOSTGROUP_SVC_DOWNTIME ) {
 check_comment_sanity ( & e ) ;
 check_time_sanity ( & e ) ;
 clean_comment_data ( comment_author ) ;
 clean_comment_data ( comment_data ) ;
 }
 else if ( enforce_comments_on_actions == TRUE ) {
 check_comment_sanity ( & e ) ;
 clean_comment_data ( comment_author ) ;
 clean_comment_data ( comment_data ) ;
 }
 is_authorized [ x ] = FALSE ;
 if ( cmd == CMD_ENABLE_HOSTGROUP_SVC_NOTIFICATIONS || cmd == CMD_DISABLE_HOSTGROUP_SVC_NOTIFICATIONS || cmd == CMD_ENABLE_HOSTGROUP_HOST_NOTIFICATIONS || cmd == CMD_DISABLE_HOSTGROUP_HOST_NOTIFICATIONS || cmd == CMD_ENABLE_HOSTGROUP_SVC_CHECKS || cmd == CMD_DISABLE_HOSTGROUP_SVC_CHECKS || cmd == CMD_SCHEDULE_HOSTGROUP_HOST_DOWNTIME || cmd == CMD_SCHEDULE_HOSTGROUP_SVC_DOWNTIME ) {
 temp_hostgroup = find_hostgroup ( hostgroup_name ) ;
 if ( is_authorized_for_hostgroup_commands ( temp_hostgroup , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 else {
 temp_servicegroup = find_servicegroup ( servicegroup_name ) ;
 if ( is_authorized_for_servicegroup_commands ( temp_servicegroup , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 break ;
 case CMD_CHANGE_HOST_MODATTR : case CMD_CHANGE_SVC_MODATTR : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 cmd_has_objects = TRUE ;
 if ( commands [ x ] . host_name == NULL ) continue ;
 is_authorized [ x ] = FALSE ;
 if ( cmd == CMD_CHANGE_HOST_MODATTR ) {
 temp_host = find_host ( commands [ x ] . host_name ) ;
 if ( is_authorized_for_host_commands ( temp_host , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 else {
 temp_service = find_service ( commands [ x ] . host_name , commands [ x ] . description ) ;
 if ( is_authorized_for_service_commands ( temp_service , & current_authdata ) == TRUE ) is_authorized [ x ] = TRUE ;
 }
 if ( attr != MODATTR_NONE ) {
 error [ e ++ ] . message = strdup ( "You cannot change modified attributes other than reset them!" ) ;
 }
 }
 break ;
 default : print_generic_error_message ( "Sorry Dave, I can't let you do that..." , "Executing an unknown command? Shame on you!" , 2 ) ;
 return ;
 }
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( strchr ( commands [ x ] . host_name , ';
' ) ) {
 snprintf ( error_string , sizeof ( error_string ) , "The hostname \"%s\" contains a semicolon" , commands [ x ] . host_name ) ;
 error_string [ sizeof ( error_string ) - 1 ] = '\x0' ;
 error [ e ++ ] . message = ( char * ) strdup ( error_string ) ;
 }
 if ( commands [ x ] . description != NULL && strchr ( commands [ x ] . description , ';
' ) ) {
 snprintf ( error_string , sizeof ( error_string ) , "The service description \"%s\" on host \"%s\" contains a semicolon" , commands [ x ] . description , commands [ x ] . host_name ) ;
 error_string [ sizeof ( error_string ) - 1 ] = '\x0' ;
 error [ e ++ ] . message = strdup ( error_string ) ;
 }
 }
 if ( hostgroup_name && strchr ( hostgroup_name , ';
' ) ) error [ e ++ ] . message = strdup ( "The hostgroup name contains a semicolon" ) ;
 if ( servicegroup_name && strchr ( servicegroup_name , ';
' ) ) error [ e ++ ] . message = strdup ( "The servicegroup name contains a semicolon" ) ;
 printf ( "<BR><DIV align='center'>\n" ) ;
 if ( check_external_commands == FALSE ) {
 print_generic_error_message ( "Sorry, but Icinga is currently not checking for external commands, so your command will not be committed!" , "Read the documentation for information on how to enable external commands..." , 2 ) ;
 return ;
 }
 if ( use_authentication == FALSE ) {
 print_generic_error_message ( "Sorry Dave, I can't let you do that..." , "It seems that you have chosen to not use the authentication functionality of the CGIs. I don't want to be personally responsible for what may happen as a result of allowing unauthorized users to issue commands to Icinga, so you'll have to disable this safeguard if you are really stubborn and want to invite trouble. Read the section on CGI authentication in the HTML documentation to learn how you can enable authentication and why you should want to." , 2 ) ;
 return ;
 }
 if ( e > 0 ) {
 printf ( "<DIV CLASS='errorBox'>\n" ) ;
 printf ( "<DIV CLASS='errorMessage'><table cellspacing=0 cellpadding=0 border=0><tr><td width=55><img src=\"%s%s\" border=0></td>" , url_images_path , CMD_STOP_ICON ) ;
 printf ( "<td CLASS='errorMessage'>Following errors occured.</td></tr></table></DIV>\n" ) ;
 printf ( "<table cellspacing=0 cellpadding=0 border=0 class='errorTable'>\n" ) ;
 for ( e = 0 ;
 e < NUMBER_OF_STRUCTS ;
 e ++ ) {
 if ( error [ e ] . message == NULL ) continue ;
 printf ( "<tr><td class='errorString'>ERROR:</td><td class='errorContent'>%s</td></tr>\n" , error [ e ] . message ) ;
 }
 printf ( "</table>\n</DIV>\n" ) ;
 printf ( "<BR>\n" ) ;
 printf ( "<table cellspacing=0 cellpadding=0 border=0 class='BoxWidth'><tr>\n" ) ;
 printf ( "<td align='left' width='50%%'><input type='submit' value='< Go back and fix it' onClick='window.history.go(-1);
' class='submitButton'></td>\n" ) ;
 printf ( "<td align='right' width='50%%'><input type='submit' value='Get me out of here' onClick='window.history.go(-2);
' class='submitButton'></td>\n" ) ;
 printf ( "</tr></table></DIV>" ) ;
 return ;
 }
 if ( cmd_has_objects == FALSE && is_authorized [ 0 ] == FALSE ) {
 print_generic_error_message ( "Sorry, but you are not authorized to commit the specified command." , "Read the section of the documentation that deals with authentication and authorization in the CGIs for more information." , 2 ) ;
 return ;
 }
 commit_command ( cmd ) ;
 if ( cmd_has_objects == FALSE ) {
 if ( submit_result [ 0 ] == OK ) {
 printf ( "<DIV CLASS='successBox'>\n" ) ;
 printf ( "<DIV CLASS='successMessage'>Your command request was successfully submitted to %s for processing.<BR><BR>\n" , PROGRAM_NAME ) ;
 printf ( "Note: It may take a while before the command is actually processed.</DIV>\n" ) ;
 printf ( "</DIV>\n" ) ;
 printf ( "<BR><input type='submit' value='Done' onClick='window.history.go(-2);
' class='submitButton'></DIV>\n" ) ;
 }
 else {
 print_generic_error_message ( "An error occurred while attempting to commit your command for processing." , "Unfortunately I can't determine the root cause of this problem." , 2 ) ;
 }
 }
 else {
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( cmd == CMD_DEL_HOST_COMMENT || cmd == CMD_DEL_SVC_COMMENT || cmd == CMD_DEL_HOST_DOWNTIME || cmd == CMD_DEL_SVC_DOWNTIME ) {
 if ( multi_ids [ x ] == FALSE ) continue ;
 }
 else {
 if ( commands [ x ] . host_name == NULL ) continue ;
 }
 if ( is_authorized [ x ] == FALSE || submit_result [ x ] == ERROR ) {
 error_found = TRUE ;
 break ;
 }
 }
 if ( error_found ) {
 print_generic_error_message ( "An error occurred while attempting to commit your command for processing." , "Not all commands could be send off successfully..." , 0 ) ;
 }
 else {
 printf ( "<DIV CLASS='successBox'>\n" ) ;
 printf ( "<DIV CLASS='successMessage'>Your command requests were successfully submitted to %s for processing.<BR><BR>\n" , PROGRAM_NAME ) ;
 printf ( "Note: It may take a while before the commands are actually processed.</DIV>\n" ) ;
 printf ( "</DIV>\n" ) ;
 }
 printf ( "<BR>\n" ) ;
 printf ( "<TABLE CELLSPACING='0' CELLPADDING=0 BORDER=0 CLASS='BoxWidth'>\n" ) ;
 printf ( "<tr class='BoxWidth'><td width='33%%'></td><td width='33%%' align='center'><input type='submit' value='Done' onClick='window.history.go(-2);
' class='submitButton'></td><td width='33%%' align='right'>\n" ) ;
 if ( ! error_found ) printf ( "<input type='submit' value='Let me see what has been done' onClick=\"document.getElementById('sumCommit').style.display = '';
\" class='submitButton'>\n" ) ;
 printf ( "</td></TR></TABLE>\n" ) ;
 printf ( "<BR><BR>\n" ) ;
 printf ( "<TABLE CELLSPACING='0' CELLPADDING='0' ID='sumCommit' %s><TR><TD CLASS='boxFrame BoxWidth'>\n" , ( error_found ) ? "" : "style='display:none;
'" ) ;
 printf ( "<table cellspacing=2 cellpadding=0 border=0 class='contentTable'>\n" ) ;
 if ( cmd == CMD_DEL_HOST_COMMENT || cmd == CMD_DEL_SVC_COMMENT ) printf ( "<tr class='sumHeader'><td width='80%%'>Comment ID</td><td width='20%%'>Status</td></tr>\n" ) ;
 else if ( cmd == CMD_DEL_HOST_DOWNTIME || cmd == CMD_DEL_SVC_DOWNTIME ) printf ( "<tr class='sumHeader'><td width='80%%'>Downtime ID</td><td width='20%%'>Status</td></tr>\n" ) ;
 else printf ( "<tr class='sumHeader'><td width='40%%'>Host</td><td width='40%%'>Service</td><td width='20%%'>Status</td></tr>\n" ) ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( cmd == CMD_DEL_HOST_COMMENT || cmd == CMD_DEL_SVC_COMMENT || cmd == CMD_DEL_HOST_DOWNTIME || cmd == CMD_DEL_SVC_DOWNTIME ) {
 if ( multi_ids [ x ] == FALSE ) continue ;
 row_color = ( row_color == 0 ) ? 1 : 0 ;
 printf ( "<tr class='status%s'><td>%lu</td><td>" , ( row_color == 0 ) ? "Even" : "Odd " , multi_ids [ x ] ) ;
 }
 else {
 if ( commands [ x ] . host_name == NULL ) continue ;
 row_color = ( row_color == 0 ) ? 1 : 0 ;
 printf ( "<tr class='status%s'><td>%s</td><td>%s</td><td>" , ( row_color == 0 ) ? "Even" : "Odd " , commands [ x ] . host_name , ( commands [ x ] . description != NULL ) ? commands [ x ] . description : "N/A" ) ;
 }
 if ( is_authorized [ x ] == FALSE ) printf ( "<DIV class='commitFailed'>Not Authorized</DIV>" ) ;
 else if ( submit_result [ x ] == ERROR ) printf ( "<DIV class='commitFailed'>FAILED</DIV>" ) ;
 else if ( submit_result [ x ] == OK ) printf ( "<DIV class='commitSuccess'>Successful</DIV>" ) ;
 else printf ( "<DIV class='commitUnknown'>Unknown</DIV>" ) ;
 printf ( "</TD><TR>\n" ) ;
 }
 printf ( "</TABLE>\n" ) ;
 printf ( "</TD></TR></TABLE></DIV>\n" ) ;
 }
 return ;
 }