int commit_command ( int cmd ) {
 time_t current_time ;
 time_t scheduled_time ;
 time_t notification_time ;
 char * temp_buffer = NULL ;
 int x = 0 , dummy ;
 time ( & current_time ) ;
 scheduled_time = current_time + ( schedule_delay * 60 ) ;
 notification_time = current_time + ( notification_delay * 60 ) ;
 switch ( cmd ) {
 case CMD_START_EXECUTING_SVC_CHECKS : case CMD_STOP_EXECUTING_SVC_CHECKS : case CMD_START_ACCEPTING_PASSIVE_SVC_CHECKS : case CMD_STOP_ACCEPTING_PASSIVE_SVC_CHECKS : case CMD_ENABLE_EVENT_HANDLERS : case CMD_DISABLE_EVENT_HANDLERS : case CMD_START_OBSESSING_OVER_SVC_CHECKS : case CMD_STOP_OBSESSING_OVER_SVC_CHECKS : case CMD_ENABLE_FLAP_DETECTION : case CMD_DISABLE_FLAP_DETECTION : case CMD_ENABLE_FAILURE_PREDICTION : case CMD_DISABLE_FAILURE_PREDICTION : case CMD_ENABLE_PERFORMANCE_DATA : case CMD_DISABLE_PERFORMANCE_DATA : case CMD_START_EXECUTING_HOST_CHECKS : case CMD_STOP_EXECUTING_HOST_CHECKS : case CMD_START_ACCEPTING_PASSIVE_HOST_CHECKS : case CMD_STOP_ACCEPTING_PASSIVE_HOST_CHECKS : case CMD_START_OBSESSING_OVER_HOST_CHECKS : case CMD_STOP_OBSESSING_OVER_HOST_CHECKS : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , NULL ) ;
 break ;
 case CMD_ENABLE_HOST_FLAP_DETECTION : case CMD_DISABLE_HOST_FLAP_DETECTION : case CMD_ENABLE_PASSIVE_HOST_CHECKS : case CMD_DISABLE_PASSIVE_HOST_CHECKS : case CMD_START_OBSESSING_OVER_HOST : case CMD_STOP_OBSESSING_OVER_HOST : case CMD_DEL_ALL_HOST_COMMENTS : case CMD_ENABLE_ALL_NOTIFICATIONS_BEYOND_HOST : case CMD_DISABLE_ALL_NOTIFICATIONS_BEYOND_HOST : case CMD_ENABLE_HOST_EVENT_HANDLER : case CMD_DISABLE_HOST_EVENT_HANDLER : case CMD_ENABLE_HOST_CHECK : case CMD_DISABLE_HOST_CHECK : case CMD_REMOVE_HOST_ACKNOWLEDGEMENT : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , commands [ x ] . host_name ) ;
 }
 break ;
 case CMD_ENABLE_SVC_FLAP_DETECTION : case CMD_DISABLE_SVC_FLAP_DETECTION : case CMD_ENABLE_PASSIVE_SVC_CHECKS : case CMD_DISABLE_PASSIVE_SVC_CHECKS : case CMD_START_OBSESSING_OVER_SVC : case CMD_STOP_OBSESSING_OVER_SVC : case CMD_DEL_ALL_SVC_COMMENTS : case CMD_ENABLE_SVC_NOTIFICATIONS : case CMD_DISABLE_SVC_NOTIFICATIONS : case CMD_ENABLE_SVC_EVENT_HANDLER : case CMD_DISABLE_SVC_EVENT_HANDLER : case CMD_ENABLE_SVC_CHECK : case CMD_DISABLE_SVC_CHECK : case CMD_REMOVE_SVC_ACKNOWLEDGEMENT : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s" , commands [ x ] . host_name , commands [ x ] . description ) ;
 }
 break ;
 case CMD_ADD_HOST_COMMENT : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%d;
%s;
%s" , commands [ x ] . host_name , persistent_comment , comment_author , comment_data ) ;
 }
 break ;
 case CMD_ADD_SVC_COMMENT : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s;
%d;
%s;
%s" , commands [ x ] . host_name , commands [ x ] . description , persistent_comment , comment_author , comment_data ) ;
 }
 break ;
 case CMD_DEL_HOST_COMMENT : case CMD_DEL_SVC_COMMENT : case CMD_DEL_HOST_DOWNTIME : case CMD_DEL_SVC_DOWNTIME : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( multi_ids [ x ] == FALSE ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%lu" , multi_ids [ x ] ) ;
 }
 break ;
 case CMD_DEL_DOWNTIME_BY_HOST_NAME : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , commands [ x ] . host_name ) ;
 }
 break ;
 case CMD_DELAY_HOST_NOTIFICATION : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu" , commands [ x ] . host_name , notification_time ) ;
 }
 break ;
 case CMD_DELAY_SVC_NOTIFICATION : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s;
%lu" , commands [ x ] . host_name , commands [ x ] . description , notification_time ) ;
 }
 break ;
 case CMD_SCHEDULE_SVC_CHECK : case CMD_SCHEDULE_FORCED_SVC_CHECK : if ( force_check == TRUE ) cmd = CMD_SCHEDULE_FORCED_SVC_CHECK ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s;
%lu" , commands [ x ] . host_name , commands [ x ] . description , start_time ) ;
 }
 break ;
 case CMD_ENABLE_NOTIFICATIONS : case CMD_SHUTDOWN_PROCESS : case CMD_RESTART_PROCESS : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%lu" , scheduled_time ) ;
 break ;
 case CMD_DISABLE_NOTIFICATIONS : if ( is_authorized [ x ] ) {
 if ( end_time > 0 ) {
 cmd = CMD_DISABLE_NOTIFICATIONS_EXPIRE_TIME ;
 submit_result [ x ] = cmd_submitf ( cmd , "%lu;
%lu" , scheduled_time , end_time ) ;
 my_free ( temp_buffer ) ;
 }
 else {
 submit_result [ x ] = cmd_submitf ( cmd , "%lu" , scheduled_time ) ;
 }
 }
 break ;
 case CMD_ENABLE_HOST_SVC_CHECKS : case CMD_DISABLE_HOST_SVC_CHECKS : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , commands [ x ] . host_name ) ;
 }
 if ( affect_host_and_services == TRUE ) {
 cmd = ( cmd == CMD_ENABLE_HOST_SVC_CHECKS ) ? CMD_ENABLE_HOST_CHECK : CMD_DISABLE_HOST_CHECK ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] |= cmd_submitf ( cmd , "%s" , commands [ x ] . host_name ) ;
 }
 }
 break ;
 case CMD_SCHEDULE_HOST_SVC_CHECKS : if ( force_check == TRUE ) cmd = CMD_SCHEDULE_FORCED_HOST_SVC_CHECKS ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu" , commands [ x ] . host_name , scheduled_time ) ;
 }
 break ;
 case CMD_ENABLE_HOST_NOTIFICATIONS : case CMD_DISABLE_HOST_NOTIFICATIONS : if ( propagate_to_children == TRUE ) cmd = ( cmd == CMD_ENABLE_HOST_NOTIFICATIONS ) ? CMD_ENABLE_HOST_AND_CHILD_NOTIFICATIONS : CMD_DISABLE_HOST_AND_CHILD_NOTIFICATIONS ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , commands [ x ] . host_name ) ;
 }
 break ;
 case CMD_ENABLE_HOST_SVC_NOTIFICATIONS : case CMD_DISABLE_HOST_SVC_NOTIFICATIONS : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , commands [ x ] . host_name ) ;
 }
 if ( affect_host_and_services == TRUE ) {
 cmd = ( cmd == CMD_ENABLE_HOST_SVC_NOTIFICATIONS ) ? CMD_ENABLE_HOST_NOTIFICATIONS : CMD_DISABLE_HOST_NOTIFICATIONS ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] |= cmd_submitf ( cmd , "%s" , commands [ x ] . host_name ) ;
 }
 }
 break ;
 case CMD_ACKNOWLEDGE_HOST_PROBLEM : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) {
 if ( end_time > 0 ) {
 cmd = CMD_ACKNOWLEDGE_HOST_PROBLEM_EXPIRE ;
 dummy = asprintf ( & temp_buffer , "%s - The acknowledgement expires at: %s." , comment_data , end_time_string ) ;
 submit_result [ x ] = cmd_submitf ( cmd , "%s;
%d;
%d;
%d;
%lu;
%s;
%s" , commands [ x ] . host_name , ( sticky_ack == TRUE ) ? ACKNOWLEDGEMENT_STICKY : ACKNOWLEDGEMENT_NORMAL , send_notification , persistent_comment , end_time , comment_author , temp_buffer ) ;
 my_free ( temp_buffer ) ;
 }
 else submit_result [ x ] = cmd_submitf ( cmd , "%s;
%d;
%d;
%d;
%s;
%s" , commands [ x ] . host_name , ( sticky_ack == TRUE ) ? ACKNOWLEDGEMENT_STICKY : ACKNOWLEDGEMENT_NORMAL , send_notification , persistent_comment , comment_author , comment_data ) ;
 }
 }
 break ;
 case CMD_ACKNOWLEDGE_SVC_PROBLEM : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) {
 if ( end_time > 0 ) {
 cmd = CMD_ACKNOWLEDGE_SVC_PROBLEM_EXPIRE ;
 dummy = asprintf ( & temp_buffer , "%s - The acknowledgement expires at: %s." , comment_data , end_time_string ) ;
 submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s;
%d;
%d;
%d;
%lu;
%s;
%s" , commands [ x ] . host_name , commands [ x ] . description , ( sticky_ack == TRUE ) ? ACKNOWLEDGEMENT_STICKY : ACKNOWLEDGEMENT_NORMAL , send_notification , persistent_comment , end_time , comment_author , temp_buffer ) ;
 my_free ( temp_buffer ) ;
 }
 else submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s;
%d;
%d;
%d;
%s;
%s" , commands [ x ] . host_name , commands [ x ] . description , ( sticky_ack == TRUE ) ? ACKNOWLEDGEMENT_STICKY : ACKNOWLEDGEMENT_NORMAL , send_notification , persistent_comment , comment_author , comment_data ) ;
 }
 }
 break ;
 case CMD_PROCESS_SERVICE_CHECK_RESULT : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s;
%d;
%s|%s" , commands [ x ] . host_name , commands [ x ] . description , plugin_state , plugin_output , performance_data ) ;
 }
 break ;
 case CMD_PROCESS_HOST_CHECK_RESULT : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%d;
%s|%s" , commands [ x ] . host_name , plugin_state , plugin_output , performance_data ) ;
 }
 break ;
 case CMD_SCHEDULE_HOST_DOWNTIME : if ( child_options == 1 ) cmd = CMD_SCHEDULE_AND_PROPAGATE_TRIGGERED_HOST_DOWNTIME ;
 else if ( child_options == 2 ) cmd = CMD_SCHEDULE_AND_PROPAGATE_HOST_DOWNTIME ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu;
%lu;
%d;
%lu;
%lu;
%s;
%s" , commands [ x ] . host_name , start_time , end_time , fixed , triggered_by , duration , comment_author , comment_data ) ;
 }
 break ;
 case CMD_SCHEDULE_HOST_SVC_DOWNTIME : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu;
%lu;
%d;
%lu;
%lu;
%s;
%s" , commands [ x ] . host_name , start_time , end_time , fixed , triggered_by , duration , comment_author , comment_data ) ;
 }
 break ;
 case CMD_SCHEDULE_SVC_DOWNTIME : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s;
%lu;
%lu;
%d;
%lu;
%lu;
%s;
%s" , commands [ x ] . host_name , commands [ x ] . description , start_time , end_time , fixed , triggered_by , duration , comment_author , comment_data ) ;
 }
 break ;
 case CMD_SCHEDULE_HOST_CHECK : if ( force_check == TRUE ) cmd = CMD_SCHEDULE_FORCED_HOST_CHECK ;
 for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu" , commands [ x ] . host_name , start_time ) ;
 }
 break ;
 case CMD_SEND_CUSTOM_HOST_NOTIFICATION : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%d;
%s;
%s" , commands [ x ] . host_name , ( force_notification | broadcast_notification ) , comment_author , comment_data ) ;
 }
 break ;
 case CMD_SEND_CUSTOM_SVC_NOTIFICATION : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s;
%d;
%s;
%s" , commands [ x ] . host_name , commands [ x ] . description , ( force_notification | broadcast_notification ) , comment_author , comment_data ) ;
 }
 break ;
 case CMD_ENABLE_HOSTGROUP_SVC_NOTIFICATIONS : case CMD_DISABLE_HOSTGROUP_SVC_NOTIFICATIONS : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , hostgroup_name ) ;
 if ( affect_host_and_services == TRUE ) {
 cmd = ( cmd == CMD_ENABLE_HOSTGROUP_SVC_NOTIFICATIONS ) ? CMD_ENABLE_HOSTGROUP_HOST_NOTIFICATIONS : CMD_DISABLE_HOSTGROUP_HOST_NOTIFICATIONS ;
 if ( is_authorized [ x ] ) submit_result [ x ] |= cmd_submitf ( cmd , "%s" , hostgroup_name ) ;
 }
 break ;
 case CMD_ENABLE_HOSTGROUP_HOST_NOTIFICATIONS : case CMD_DISABLE_HOSTGROUP_HOST_NOTIFICATIONS : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , hostgroup_name ) ;
 break ;
 case CMD_ENABLE_HOSTGROUP_SVC_CHECKS : case CMD_DISABLE_HOSTGROUP_SVC_CHECKS : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , hostgroup_name ) ;
 if ( affect_host_and_services == TRUE ) {
 cmd = ( cmd == CMD_ENABLE_HOSTGROUP_SVC_CHECKS ) ? CMD_ENABLE_HOSTGROUP_HOST_CHECKS : CMD_DISABLE_HOSTGROUP_HOST_CHECKS ;
 if ( is_authorized [ x ] ) submit_result [ x ] |= cmd_submitf ( cmd , "%s" , hostgroup_name ) ;
 }
 break ;
 case CMD_SCHEDULE_HOSTGROUP_HOST_DOWNTIME : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu;
%lu;
%d;
0;
%lu;
%s;
%s" , hostgroup_name , start_time , end_time , fixed , duration , comment_author , comment_data ) ;
 break ;
 case CMD_SCHEDULE_HOSTGROUP_SVC_DOWNTIME : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu;
%lu;
%d;
0;
%lu;
%s;
%s" , hostgroup_name , start_time , end_time , fixed , duration , comment_author , comment_data ) ;
 if ( affect_host_and_services == TRUE ) {
 if ( is_authorized [ x ] ) submit_result [ x ] |= cmd_submitf ( CMD_SCHEDULE_HOSTGROUP_HOST_DOWNTIME , "%s;
%lu;
%lu;
%d;
0;
%lu;
%s;
%s" , hostgroup_name , start_time , end_time , fixed , duration , comment_author , comment_data ) ;
 }
 break ;
 case CMD_ENABLE_SERVICEGROUP_SVC_NOTIFICATIONS : case CMD_DISABLE_SERVICEGROUP_SVC_NOTIFICATIONS : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , servicegroup_name ) ;
 if ( affect_host_and_services == TRUE ) {
 cmd = ( cmd == CMD_ENABLE_SERVICEGROUP_SVC_NOTIFICATIONS ) ? CMD_ENABLE_SERVICEGROUP_HOST_NOTIFICATIONS : CMD_DISABLE_SERVICEGROUP_HOST_NOTIFICATIONS ;
 if ( is_authorized [ x ] ) submit_result [ x ] |= cmd_submitf ( cmd , "%s" , servicegroup_name ) ;
 }
 break ;
 case CMD_ENABLE_SERVICEGROUP_HOST_NOTIFICATIONS : case CMD_DISABLE_SERVICEGROUP_HOST_NOTIFICATIONS : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , servicegroup_name ) ;
 break ;
 case CMD_ENABLE_SERVICEGROUP_SVC_CHECKS : case CMD_DISABLE_SERVICEGROUP_SVC_CHECKS : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s" , servicegroup_name ) ;
 if ( affect_host_and_services == TRUE ) {
 cmd = ( cmd == CMD_ENABLE_SERVICEGROUP_SVC_CHECKS ) ? CMD_ENABLE_SERVICEGROUP_HOST_CHECKS : CMD_DISABLE_SERVICEGROUP_HOST_CHECKS ;
 if ( is_authorized [ x ] ) submit_result [ x ] |= cmd_submitf ( cmd , "%s" , servicegroup_name ) ;
 }
 break ;
 case CMD_SCHEDULE_SERVICEGROUP_HOST_DOWNTIME : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu;
%lu;
%d;
0;
%lu;
%s;
%s" , servicegroup_name , start_time , end_time , fixed , duration , comment_author , comment_data ) ;
 break ;
 case CMD_SCHEDULE_SERVICEGROUP_SVC_DOWNTIME : if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu;
%lu;
%d;
0;
%lu;
%s;
%s" , servicegroup_name , start_time , end_time , fixed , duration , comment_author , comment_data ) ;
 if ( affect_host_and_services == TRUE ) {
 if ( is_authorized [ x ] ) submit_result [ x ] |= cmd_submitf ( CMD_SCHEDULE_SERVICEGROUP_HOST_DOWNTIME , "%s;
%lu;
%lu;
%d;
0;
%lu;
%s;
%s" , servicegroup_name , start_time , end_time , fixed , duration , comment_author , comment_data ) ;
 }
 break ;
 case CMD_CHANGE_HOST_MODATTR : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%lu" , commands [ x ] . host_name , attr ) ;
 }
 break ;
 case CMD_CHANGE_SVC_MODATTR : for ( x = 0 ;
 x < NUMBER_OF_STRUCTS ;
 x ++ ) {
 if ( commands [ x ] . host_name == NULL ) continue ;
 if ( is_authorized [ x ] ) submit_result [ x ] = cmd_submitf ( cmd , "%s;
%s;
%lu" , commands [ x ] . host_name , commands [ x ] . description , attr ) ;
 }
 break ;
 default : submit_result [ x ] = ERROR ;
 break ;
 }
 return OK ;
 }