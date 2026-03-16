void request_command_data ( int cmd ) {
 char start_time [ MAX_DATETIME_LENGTH ] ;
 contact * temp_contact ;
 scheduled_downtime * temp_downtime ;
 host * temp_host = NULL ;
 char action [ MAX_INPUT_BUFFER ] ;
 int found_trigger_objects = FALSE ;
 temp_contact = find_contact ( current_authdata . username ) ;
 if ( temp_contact != NULL && temp_contact -> alias != NULL ) comment_author = temp_contact -> alias ;
 else comment_author = current_authdata . username ;
 printf ( "<BR>" ) ;
 switch ( cmd ) {
 case CMD_ADD_HOST_COMMENT : case CMD_ADD_SVC_COMMENT : snprintf ( action , sizeof ( action ) , "Add %s comments" , ( cmd == CMD_ADD_HOST_COMMENT ) ? "host" : "service" ) ;
 break ;
 case CMD_DEL_HOST_COMMENT : case CMD_DEL_SVC_COMMENT : snprintf ( action , sizeof ( action ) , "Delete %s comments" , ( cmd == CMD_DEL_HOST_COMMENT ) ? "host" : "service" ) ;
 break ;
 case CMD_DELAY_HOST_NOTIFICATION : case CMD_DELAY_SVC_NOTIFICATION : snprintf ( help_text , sizeof ( help_text ) , "This command is used to delay the next problem notification that is sent out for specified %s. The notification delay will be disregarded if " "the %s changes state before the next notification is scheduled to be sent out. This command has no effect if the %s are currently %s." , ( cmd == CMD_DELAY_HOST_NOTIFICATION ) ? "hosts" : "services" , ( cmd == CMD_DELAY_HOST_NOTIFICATION ) ? "hosts" : "services" , ( cmd == CMD_DELAY_HOST_NOTIFICATION ) ? "hosts" : "services" , ( cmd == CMD_DELAY_HOST_NOTIFICATION ) ? "UP" : "in an OK state" ) ;
 snprintf ( action , sizeof ( action ) , "Delay a %s notification" , ( cmd == CMD_DELAY_HOST_NOTIFICATION ) ? "host" : "service" ) ;
 break ;
 case CMD_SCHEDULE_HOST_CHECK : case CMD_SCHEDULE_SVC_CHECK : snprintf ( help_text , sizeof ( help_text ) , "This command is used to schedule the next check of these %s. %s will re-queue the %s to be checked at the time you specify." , ( cmd == CMD_SCHEDULE_HOST_CHECK ) ? "hosts" : "services" , PROGRAM_NAME , ( cmd == CMD_SCHEDULE_HOST_CHECK ) ? "host" : "service" ) ;
 snprintf ( action , sizeof ( action ) , "Schedule %s checks" , ( cmd == CMD_SCHEDULE_HOST_CHECK ) ? "host" : "service" ) ;
 break ;
 case CMD_ENABLE_SVC_CHECK : case CMD_DISABLE_SVC_CHECK : snprintf ( action , sizeof ( action ) , "%s active service checks on a program-wide basis" , ( cmd == CMD_ENABLE_SVC_CHECK ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_NOTIFICATIONS : case CMD_DISABLE_NOTIFICATIONS : snprintf ( help_text , sizeof ( help_text ) , "This command is used to %s host and service notifications on a program-wide basis" , ( cmd == CMD_ENABLE_NOTIFICATIONS ) ? "enable" : "disable" ) ;
 snprintf ( action , sizeof ( action ) , "%s notifications on a program-wide basis" , ( cmd == CMD_ENABLE_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_DISABLE_NOTIFICATIONS_EXPIRE_TIME : snprintf ( help_text , sizeof ( help_text ) , "This command is used to disable host and service notifications on a program-wide basis, with a given expire time" ) ;
 snprintf ( action , sizeof ( action ) , "Disable notifications on a program-wide basis, with expire time" ) ;
 break ;
 case CMD_SHUTDOWN_PROCESS : case CMD_RESTART_PROCESS : snprintf ( action , sizeof ( action ) , "%s the %s process" , ( cmd == CMD_SHUTDOWN_PROCESS ) ? "Shutdown" : "Restart" , PROGRAM_NAME ) ;
 break ;
 case CMD_ENABLE_HOST_SVC_CHECKS : case CMD_DISABLE_HOST_SVC_CHECKS : if ( cmd == CMD_ENABLE_HOST_SVC_CHECKS ) snprintf ( help_text , sizeof ( help_text ) , "This command is used to enable active checks of all services associated with the specified host" ) ;
 else {
 snprintf ( help_text , sizeof ( help_text ) , "This command is used to disable active checks of all services associated with the specified host. " "When a service is disabled %s will not monitor the service. Doing this will prevent any notifications being sent out for " "the specified service while it is disabled. In order to have %s check the service in the future you will have to re-enable the service. " "Note that disabling service checks may not necessarily prevent notifications from being sent out about the host which those services are associated with." , PROGRAM_NAME , PROGRAM_NAME ) ;
 }
 snprintf ( action , sizeof ( action ) , "%s active checks of all services on these hosts" , ( cmd == CMD_ENABLE_HOST_SVC_CHECKS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_SCHEDULE_HOST_SVC_CHECKS : snprintf ( action , sizeof ( action ) , "Schedule a check of all services for these hosts" ) ;
 break ;
 case CMD_DEL_ALL_HOST_COMMENTS : case CMD_DEL_ALL_SVC_COMMENTS : snprintf ( action , sizeof ( action ) , "Delete all comments for these %s" , ( cmd == CMD_DEL_ALL_HOST_COMMENTS ) ? "hosts" : "services" ) ;
 break ;
 case CMD_ENABLE_SVC_NOTIFICATIONS : case CMD_DISABLE_SVC_NOTIFICATIONS : snprintf ( action , sizeof ( action ) , "%s notifications for these services" , ( cmd == CMD_ENABLE_SVC_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_HOST_NOTIFICATIONS : case CMD_DISABLE_HOST_NOTIFICATIONS : snprintf ( action , sizeof ( action ) , "%s notifications for these hosts" , ( cmd == CMD_ENABLE_HOST_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_ALL_NOTIFICATIONS_BEYOND_HOST : case CMD_DISABLE_ALL_NOTIFICATIONS_BEYOND_HOST : snprintf ( help_text , sizeof ( help_text ) , "This command is used to %s notifications for all hosts and services that lie <i>beyond</i> the specified host (from the view of %s)." , ( cmd == CMD_ENABLE_ALL_NOTIFICATIONS_BEYOND_HOST ) ? "enable" : "disable" , PROGRAM_NAME ) ;
 snprintf ( action , sizeof ( action ) , "%s notifications for all hosts and services beyond these hosts" , ( cmd == CMD_ENABLE_ALL_NOTIFICATIONS_BEYOND_HOST ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_HOST_SVC_NOTIFICATIONS : case CMD_DISABLE_HOST_SVC_NOTIFICATIONS : snprintf ( action , sizeof ( action ) , "%s notifications for all services on these hosts" , ( cmd == CMD_ENABLE_HOST_SVC_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ACKNOWLEDGE_HOST_PROBLEM : case CMD_ACKNOWLEDGE_SVC_PROBLEM : snprintf ( action , sizeof ( action ) , "Acknowledge %s problems" , ( cmd == CMD_ACKNOWLEDGE_HOST_PROBLEM ) ? "host" : "service" ) ;
 break ;
 case CMD_START_EXECUTING_HOST_CHECKS : case CMD_STOP_EXECUTING_HOST_CHECKS : snprintf ( action , sizeof ( action ) , "%s executing host checks on a program-wide basis" , ( cmd == CMD_START_EXECUTING_HOST_CHECKS ) ? "Start" : "Stop" ) ;
 break ;
 case CMD_START_EXECUTING_SVC_CHECKS : case CMD_STOP_EXECUTING_SVC_CHECKS : if ( cmd == CMD_START_EXECUTING_SVC_CHECKS ) snprintf ( help_text , sizeof ( help_text ) , "This command is used to resume execution of active service checks on a program-wide basis. Individual services which are disabled will still not be checked." ) ;
 else snprintf ( help_text , sizeof ( help_text ) , "This command is used to temporarily stop %s from actively executing any service checks. This will have the side effect of preventing any notifications from being sent out (for any and all services and hosts). " "Service checks will not be executed again until you issue a command to resume service check execution." , PROGRAM_NAME ) ;
 snprintf ( action , sizeof ( action ) , "%s executing active service checks" , ( cmd == CMD_START_EXECUTING_SVC_CHECKS ) ? "Start" : "Stop" ) ;
 break ;
 case CMD_START_ACCEPTING_PASSIVE_SVC_CHECKS : case CMD_STOP_ACCEPTING_PASSIVE_SVC_CHECKS : snprintf ( help_text , sizeof ( help_text ) , "This command is used to make %s %s accepting passive service check results that it finds in the external command file." , PROGRAM_NAME , ( cmd == CMD_START_ACCEPTING_PASSIVE_SVC_CHECKS ) ? "start" : "stop" ) ;
 snprintf ( action , sizeof ( action ) , "%s accepting passive service checks on a program-wide basis" , ( cmd == CMD_START_ACCEPTING_PASSIVE_SVC_CHECKS ) ? "Start" : "Stop" ) ;
 break ;
 case CMD_ENABLE_PASSIVE_SVC_CHECKS : case CMD_DISABLE_PASSIVE_SVC_CHECKS : if ( cmd == CMD_ENABLE_PASSIVE_SVC_CHECKS ) snprintf ( help_text , sizeof ( help_text ) , "This command is used to allow %s to accept passive service check results that it finds in the external command file for this particular service." , PROGRAM_NAME ) ;
 else snprintf ( help_text , sizeof ( help_text ) , "This command is used to stop %s accepting passive service check results that it finds in the external command file for this particular service. All passive check results that are found for this service will be ignored." , PROGRAM_NAME ) ;
 snprintf ( action , sizeof ( action ) , "%s accepting passive service checks for these services" , ( cmd == CMD_ENABLE_PASSIVE_SVC_CHECKS ) ? "Start" : "Stop" ) ;
 break ;
 case CMD_ENABLE_EVENT_HANDLERS : case CMD_DISABLE_EVENT_HANDLERS : if ( cmd == CMD_ENABLE_EVENT_HANDLERS ) snprintf ( help_text , sizeof ( help_text ) , "This command is used to allow %s to run host and service event handlers." , PROGRAM_NAME ) ;
 else snprintf ( help_text , sizeof ( help_text ) , "This command is used to temporarily prevent %s from running any host or service event handlers." , PROGRAM_NAME ) ;
 snprintf ( action , sizeof ( action ) , "%s event handlers on a program-wide basis" , ( cmd == CMD_ENABLE_EVENT_HANDLERS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_HOST_EVENT_HANDLER : case CMD_DISABLE_HOST_EVENT_HANDLER : snprintf ( help_text , sizeof ( help_text ) , "This command is used to %s the event handler for the selected hosts" , ( cmd == CMD_ENABLE_HOST_EVENT_HANDLER ) ? "enable" : "disable" ) ;
 snprintf ( action , sizeof ( action ) , "%s the event handler for these hosts" , ( cmd == CMD_ENABLE_HOST_EVENT_HANDLER ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_SVC_EVENT_HANDLER : case CMD_DISABLE_SVC_EVENT_HANDLER : snprintf ( help_text , sizeof ( help_text ) , "This command is used to %s the event handler for the selected services" , ( cmd == CMD_ENABLE_SVC_EVENT_HANDLER ) ? "enable" : "disable" ) ;
 snprintf ( action , sizeof ( action ) , "%s the event handler for these services" , ( cmd == CMD_ENABLE_SVC_EVENT_HANDLER ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_HOST_CHECK : case CMD_DISABLE_HOST_CHECK : if ( cmd == CMD_DISABLE_HOST_CHECK ) snprintf ( help_text , sizeof ( help_text ) , "This command is used to temporarily prevent %s from actively checking the status of a particular host. If %s needs to check the status of this host, it will assume that it is in the same state that it was in before checks were disabled." , PROGRAM_NAME , PROGRAM_NAME ) ;
 snprintf ( action , sizeof ( action ) , "%s active host checks" , ( cmd == CMD_ENABLE_HOST_CHECK ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_STOP_OBSESSING_OVER_SVC_CHECKS : case CMD_START_OBSESSING_OVER_SVC_CHECKS : if ( cmd == CMD_START_OBSESSING_OVER_SVC_CHECKS ) snprintf ( help_text , sizeof ( help_text ) , "This command is used to have %s start obsessing over service checks. Read the documentation on distributed monitoring for more information on this." , PROGRAM_NAME ) ;
 snprintf ( action , sizeof ( action ) , "%s obsessing over service checks on a program-wide basis" , ( cmd == CMD_STOP_OBSESSING_OVER_SVC_CHECKS ) ? "Stop" : "Start" ) ;
 break ;
 case CMD_REMOVE_HOST_ACKNOWLEDGEMENT : case CMD_REMOVE_SVC_ACKNOWLEDGEMENT : snprintf ( help_text , sizeof ( help_text ) , "This command is used to remove an acknowledgement for %s problems. Once the acknowledgement is removed, notifications may start being " "sent out about the %s problem." , ( cmd == CMD_REMOVE_HOST_ACKNOWLEDGEMENT ) ? "host" : "service" , ( cmd == CMD_REMOVE_HOST_ACKNOWLEDGEMENT ) ? "host" : "service" ) ;
 snprintf ( action , sizeof ( action ) , "Remove %s acknowledgements" , ( cmd == CMD_REMOVE_HOST_ACKNOWLEDGEMENT ) ? "host" : "service" ) ;
 break ;
 case CMD_SCHEDULE_HOST_DOWNTIME : case CMD_SCHEDULE_SVC_DOWNTIME : snprintf ( help_text , sizeof ( help_text ) , "This command is used to schedule downtime for these %s. During the specified downtime, %s will not send notifications out about the %s. " "When the scheduled downtime expires, %s will send out notifications for this %s as it normally would. Scheduled downtimes are preserved " "across program shutdowns and restarts." , ( cmd == CMD_SCHEDULE_HOST_DOWNTIME ) ? "hosts" : "services" , PROGRAM_NAME , ( cmd == CMD_SCHEDULE_HOST_DOWNTIME ) ? "hosts" : "services" , PROGRAM_NAME , ( cmd == CMD_SCHEDULE_HOST_DOWNTIME ) ? "hosts" : "services" ) ;
 snprintf ( action , sizeof ( action ) , "Schedule downtime for these %s" , ( cmd == CMD_SCHEDULE_HOST_DOWNTIME ) ? "hosts" : "services" ) ;
 break ;
 case CMD_DEL_DOWNTIME_BY_HOST_NAME : snprintf ( help_text , sizeof ( help_text ) , "This command is used to delete all downtimes for a host and all its services specified by the host name already supplied." ) ;
 snprintf ( action , sizeof ( action ) , "Remove downtimes for all services for these hosts and the hosts themself" ) ;
 break ;
 case CMD_SCHEDULE_HOST_SVC_DOWNTIME : snprintf ( help_text , sizeof ( help_text ) , "This command is used to schedule downtime for a particular host and all of its services. During the specified downtime, %s will not send notifications out about the host. " "Normally, a host in downtime will not send alerts about any services in a failed state. This option will explicitly set downtime for all services for this host. " "When the scheduled downtime expires, %s will send out notifications for this host as it normally would. Scheduled downtimes are preserved " "across program shutdowns and restarts." , PROGRAM_NAME , PROGRAM_NAME ) ;
 snprintf ( action , sizeof ( action ) , "Schedule downtime for all services for these hosts and the hosts themself" ) ;
 break ;
 case CMD_PROCESS_HOST_CHECK_RESULT : case CMD_PROCESS_SERVICE_CHECK_RESULT : snprintf ( help_text , sizeof ( help_text ) , "This command is used to submit a passive check result for these %s. " "It is particularly useful for resetting security-related %s to %s states once they have been dealt with." , ( cmd == CMD_PROCESS_HOST_CHECK_RESULT ) ? "hosts" : "services" , ( cmd == CMD_PROCESS_HOST_CHECK_RESULT ) ? "hosts" : "services" , ( cmd == CMD_PROCESS_HOST_CHECK_RESULT ) ? "UP" : "OK" ) ;
 snprintf ( action , sizeof ( action ) , "Submit a passive check result for these %s" , ( cmd == CMD_PROCESS_HOST_CHECK_RESULT ) ? "hosts" : "services" ) ;
 break ;
 case CMD_ENABLE_HOST_FLAP_DETECTION : case CMD_DISABLE_HOST_FLAP_DETECTION : snprintf ( action , sizeof ( action ) , "%s flap detection for these hosts" , ( cmd == CMD_ENABLE_HOST_FLAP_DETECTION ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_SVC_FLAP_DETECTION : case CMD_DISABLE_SVC_FLAP_DETECTION : snprintf ( action , sizeof ( action ) , "%s flap detection for these services" , ( cmd == CMD_ENABLE_SVC_FLAP_DETECTION ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_FLAP_DETECTION : case CMD_DISABLE_FLAP_DETECTION : snprintf ( action , sizeof ( action ) , "%s flap detection for hosts and services on a program-wide basis" , ( cmd == CMD_ENABLE_FLAP_DETECTION ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_HOSTGROUP_SVC_NOTIFICATIONS : case CMD_DISABLE_HOSTGROUP_SVC_NOTIFICATIONS : snprintf ( action , sizeof ( action ) , "%s notifications for all services in a particular hostgroup" , ( cmd == CMD_ENABLE_HOSTGROUP_SVC_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_HOSTGROUP_HOST_NOTIFICATIONS : case CMD_DISABLE_HOSTGROUP_HOST_NOTIFICATIONS : snprintf ( action , sizeof ( action ) , "%s notifications for all hosts in a particular hostgroup" , ( cmd == CMD_ENABLE_HOSTGROUP_HOST_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_HOSTGROUP_SVC_CHECKS : case CMD_DISABLE_HOSTGROUP_SVC_CHECKS : snprintf ( action , sizeof ( action ) , "%s active checks of all services in a particular hostgroup" , ( cmd == CMD_ENABLE_HOSTGROUP_SVC_CHECKS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_DEL_HOST_DOWNTIME : case CMD_DEL_SVC_DOWNTIME : snprintf ( action , sizeof ( action ) , "Cancel scheduled downtime for these %s" , ( cmd == CMD_DEL_HOST_DOWNTIME ) ? "hosts" : "services" ) ;
 break ;
 case CMD_ENABLE_FAILURE_PREDICTION : case CMD_DISABLE_FAILURE_PREDICTION : snprintf ( action , sizeof ( action ) , "%s failure prediction for hosts and service on a program-wide basis" , ( cmd == CMD_ENABLE_FAILURE_PREDICTION ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_PERFORMANCE_DATA : case CMD_DISABLE_PERFORMANCE_DATA : snprintf ( action , sizeof ( action ) , "%s performance data processing for hosts and services on a program-wide basis" , ( cmd == CMD_ENABLE_PERFORMANCE_DATA ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_SCHEDULE_HOSTGROUP_HOST_DOWNTIME : case CMD_SCHEDULE_HOSTGROUP_SVC_DOWNTIME : snprintf ( action , sizeof ( action ) , "Schedule downtime for all %s in a particular hostgroup" , ( cmd == CMD_SCHEDULE_HOSTGROUP_HOST_DOWNTIME ) ? "hosts" : "services" ) ;
 break ;
 case CMD_START_ACCEPTING_PASSIVE_HOST_CHECKS : case CMD_STOP_ACCEPTING_PASSIVE_HOST_CHECKS : snprintf ( action , sizeof ( action ) , "%s accepting passive host checks on a program-wide basis" , ( cmd == CMD_START_ACCEPTING_PASSIVE_HOST_CHECKS ) ? "Start" : "Stop" ) ;
 break ;
 case CMD_ENABLE_PASSIVE_HOST_CHECKS : case CMD_DISABLE_PASSIVE_HOST_CHECKS : snprintf ( action , sizeof ( action ) , "%s accepting passive checks for these hosts" , ( cmd == CMD_ENABLE_PASSIVE_HOST_CHECKS ) ? "Start" : "Stop" ) ;
 break ;
 case CMD_START_OBSESSING_OVER_HOST_CHECKS : case CMD_STOP_OBSESSING_OVER_HOST_CHECKS : snprintf ( action , sizeof ( action ) , "%s obsessing over host checks on a program-wide basis" , ( cmd == CMD_START_OBSESSING_OVER_HOST_CHECKS ) ? "Start" : "Stop" ) ;
 break ;
 case CMD_START_OBSESSING_OVER_SVC : case CMD_STOP_OBSESSING_OVER_SVC : snprintf ( action , sizeof ( action ) , "%s obsessing over these services" , ( cmd == CMD_START_OBSESSING_OVER_SVC ) ? "Start" : "Stop" ) ;
 break ;
 case CMD_START_OBSESSING_OVER_HOST : case CMD_STOP_OBSESSING_OVER_HOST : snprintf ( action , sizeof ( action ) , "%s obsessing over these hosts" , ( cmd == CMD_START_OBSESSING_OVER_HOST ) ? "Start" : "Stop" ) ;
 break ;
 case CMD_ENABLE_SERVICEGROUP_SVC_NOTIFICATIONS : case CMD_DISABLE_SERVICEGROUP_SVC_NOTIFICATIONS : snprintf ( action , sizeof ( action ) , "%s notifications for all services in a particular servicegroup" , ( cmd == CMD_ENABLE_SERVICEGROUP_SVC_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_SERVICEGROUP_HOST_NOTIFICATIONS : case CMD_DISABLE_SERVICEGROUP_HOST_NOTIFICATIONS : snprintf ( action , sizeof ( action ) , "%s notifications for all hosts in a particular servicegroup" , ( cmd == CMD_ENABLE_SERVICEGROUP_HOST_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_ENABLE_SERVICEGROUP_SVC_CHECKS : case CMD_DISABLE_SERVICEGROUP_SVC_CHECKS : snprintf ( action , sizeof ( action ) , "%s active checks of all services in a particular servicegroup" , ( cmd == CMD_ENABLE_SERVICEGROUP_SVC_CHECKS ) ? "Enable" : "Disable" ) ;
 break ;
 case CMD_SCHEDULE_SERVICEGROUP_HOST_DOWNTIME : snprintf ( action , sizeof ( action ) , "Schedule downtime for all hosts in a particular servicegroup" ) ;
 break ;
 case CMD_SCHEDULE_SERVICEGROUP_SVC_DOWNTIME : snprintf ( action , sizeof ( action ) , "Schedule downtime for all services in a particular servicegroup" ) ;
 break ;
 case CMD_SEND_CUSTOM_HOST_NOTIFICATION : case CMD_SEND_CUSTOM_SVC_NOTIFICATION : snprintf ( help_text , sizeof ( help_text ) , "This command is used to send a custom notification about the specified %s. Useful in emergencies when you need to notify admins of an issue regarding a monitored system or service." , ( cmd == CMD_SEND_CUSTOM_HOST_NOTIFICATION ) ? "host" : "service" ) ;
 snprintf ( action , sizeof ( action ) , "Send a custom %s notification" , ( cmd == CMD_SEND_CUSTOM_HOST_NOTIFICATION ) ? "host" : "service" ) ;
 break ;
 case CMD_CHANGE_HOST_MODATTR : snprintf ( action , sizeof ( action ) , "Reset modified attributes for Host(s)." ) ;
 break ;
 case CMD_CHANGE_SVC_MODATTR : snprintf ( action , sizeof ( action ) , "Reset modified attributes for Service(s)." ) ;
 break ;
 default : print_generic_error_message ( "Sorry Dave, I can't let you do that..." , "Executing an unknown command? Shame on you!" , 2 ) ;
 return ;
 }
 help_text [ sizeof ( help_text ) - 1 ] = '\x0' ;
 action [ sizeof ( action ) - 1 ] = '\x0' ;
 printf ( "<script language=\"JavaScript\">\n" ) ;
 printf ( "function check_input(){
\n" " if (document.getElementById('com_data')) {
\n" " if (document.getElementById('com_data').value == '') {
\n" " document.getElementById('com_data_error').style.display = '';
\n" " return false;
\n" " }
 else {
\n" " document.getElementById('com_data_error').style.display = 'none';
\n" " }
\n" " }
\n" " if (document.getElementById('plugin_output')) {
\n" " if (document.getElementById('plugin_output').value == '') {
\n" " document.getElementById('plugin_output_error').style.display = '';
\n" " return false;
\n" " }
 else {
\n" " document.getElementById('plugin_output_error').style.display = 'none';
\n" " }
\n" " }
\n" " if (document.getElementById('not_dly')) {
\n" " if (parseInt(document.getElementById('not_dly').value) == 0 ) {
\n" " document.getElementById('not_dly_error').style.display = '';
\n" " return false;
\n" " }
\n" " }
\n" " return true;
\n" "}
\n" "</script>\n" ) ;
 printf ( "<div align='center'>\n" ) ;
 printf ( "<form method='post' action='%s' onSubmit=\"return check_input();
\">\n" , CMD_CGI ) ;
 printf ( "<INPUT TYPE='HIDDEN' NAME='cmd_typ' VALUE='%d'><INPUT TYPE='HIDDEN' NAME='cmd_mod' VALUE='%d'>\n" , cmd , CMDMODE_COMMIT ) ;
 printf ( "<TABLE CELLSPACING='0' CELLPADDING='0'><TR><TD CLASS='boxFrame BoxWidth'>\n" ) ;
 printf ( "<TABLE CELLSPACING='2' CELLPADDING='0' class='contentTable'>\n" ) ;
 printf ( "<tr CLASS='sectionHeader'><td COLSPAN='2'>Action</td></tr>\n" ) ;
 printf ( "<tr><td COLSPAN='2'>%s " , action ) ;
 if ( strlen ( help_text ) > 2 ) print_help_box ( help_text ) ;
 printf ( "</td></tr>\n" ) ;
 switch ( cmd ) {
 case CMD_ADD_SVC_COMMENT : case CMD_ACKNOWLEDGE_SVC_PROBLEM : case CMD_ADD_HOST_COMMENT : case CMD_ACKNOWLEDGE_HOST_PROBLEM : if ( cmd == CMD_ACKNOWLEDGE_SVC_PROBLEM || cmd == CMD_ADD_SVC_COMMENT ) print_object_list ( PRINT_SERVICE_LIST ) ;
 else print_object_list ( PRINT_HOST_LIST ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 print_form_element ( PRINT_PERSISTENT , cmd ) ;
 if ( cmd == CMD_ACKNOWLEDGE_HOST_PROBLEM || cmd == CMD_ACKNOWLEDGE_SVC_PROBLEM ) {
 print_form_element ( PRINT_EXPIRE_ACKNOWLEDGEMENT , cmd ) ;
 print_form_element ( PRINT_STICKY_ACK , cmd ) ;
 print_form_element ( PRINT_SEND_NOTFICATION , cmd ) ;
 }
 break ;
 case CMD_DEL_HOST_DOWNTIME : case CMD_DEL_SVC_DOWNTIME : case CMD_DEL_HOST_COMMENT : case CMD_DEL_SVC_COMMENT : if ( cmd == CMD_DEL_HOST_COMMENT || cmd == CMD_DEL_SVC_COMMENT ) print_object_list ( PRINT_COMMENT_LIST ) ;
 else print_object_list ( PRINT_DOWNTIME_LIST ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 break ;
 case CMD_DEL_DOWNTIME_BY_HOST_NAME : print_object_list ( PRINT_HOST_LIST ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 break ;
 case CMD_DELAY_SVC_NOTIFICATION : case CMD_DELAY_HOST_NOTIFICATION : if ( cmd == CMD_DELAY_SVC_NOTIFICATION ) print_object_list ( PRINT_SERVICE_LIST ) ;
 else print_object_list ( PRINT_HOST_LIST ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 print_form_element ( PRINT_NOTIFICATION_DELAY , cmd ) ;
 break ;
 case CMD_SCHEDULE_SVC_CHECK : case CMD_SCHEDULE_HOST_CHECK : case CMD_SCHEDULE_HOST_SVC_CHECKS : if ( cmd == CMD_SCHEDULE_SVC_CHECK ) print_object_list ( PRINT_SERVICE_LIST ) ;
 else print_object_list ( PRINT_HOST_LIST ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 print_form_element ( PRINT_CHECK_TIME , cmd ) ;
 print_form_element ( PRINT_FORCE_CHECK , cmd ) ;
 break ;
 case CMD_ENABLE_SVC_CHECK : case CMD_DISABLE_SVC_CHECK : case CMD_DEL_ALL_SVC_COMMENTS : case CMD_ENABLE_SVC_NOTIFICATIONS : case CMD_DISABLE_SVC_NOTIFICATIONS : case CMD_ENABLE_PASSIVE_SVC_CHECKS : case CMD_DISABLE_PASSIVE_SVC_CHECKS : case CMD_ENABLE_SVC_EVENT_HANDLER : case CMD_DISABLE_SVC_EVENT_HANDLER : case CMD_REMOVE_SVC_ACKNOWLEDGEMENT : case CMD_ENABLE_SVC_FLAP_DETECTION : case CMD_DISABLE_SVC_FLAP_DETECTION : case CMD_START_OBSESSING_OVER_SVC : case CMD_STOP_OBSESSING_OVER_SVC : print_object_list ( PRINT_SERVICE_LIST ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 break ;
 case CMD_ENABLE_HOST_SVC_CHECKS : case CMD_DISABLE_HOST_SVC_CHECKS : case CMD_ENABLE_HOST_SVC_NOTIFICATIONS : case CMD_DISABLE_HOST_SVC_NOTIFICATIONS : case CMD_ENABLE_HOST_NOTIFICATIONS : case CMD_DISABLE_HOST_NOTIFICATIONS : case CMD_DEL_ALL_HOST_COMMENTS : case CMD_ENABLE_ALL_NOTIFICATIONS_BEYOND_HOST : case CMD_DISABLE_ALL_NOTIFICATIONS_BEYOND_HOST : case CMD_ENABLE_HOST_EVENT_HANDLER : case CMD_DISABLE_HOST_EVENT_HANDLER : case CMD_ENABLE_HOST_CHECK : case CMD_DISABLE_HOST_CHECK : case CMD_REMOVE_HOST_ACKNOWLEDGEMENT : case CMD_ENABLE_HOST_FLAP_DETECTION : case CMD_DISABLE_HOST_FLAP_DETECTION : case CMD_ENABLE_PASSIVE_HOST_CHECKS : case CMD_DISABLE_PASSIVE_HOST_CHECKS : case CMD_START_OBSESSING_OVER_HOST : case CMD_STOP_OBSESSING_OVER_HOST : print_object_list ( PRINT_HOST_LIST ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 if ( cmd == CMD_ENABLE_HOST_SVC_CHECKS || cmd == CMD_DISABLE_HOST_SVC_CHECKS || cmd == CMD_ENABLE_HOST_SVC_NOTIFICATIONS || cmd == CMD_DISABLE_HOST_SVC_NOTIFICATIONS || cmd == CMD_ENABLE_HOST_NOTIFICATIONS || cmd == CMD_DISABLE_HOST_NOTIFICATIONS ) {
 if ( enforce_comments_on_actions != TRUE ) print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 }
 if ( cmd == CMD_ENABLE_HOST_SVC_CHECKS || cmd == CMD_DISABLE_HOST_SVC_CHECKS || cmd == CMD_ENABLE_HOST_SVC_NOTIFICATIONS || cmd == CMD_DISABLE_HOST_SVC_NOTIFICATIONS ) {
 snprintf ( help_text , sizeof ( help_text ) , "This %s %s of the host too." , ( cmd == CMD_ENABLE_HOST_SVC_CHECKS || cmd == CMD_ENABLE_HOST_SVC_NOTIFICATIONS ) ? "enables" : "disables" , ( cmd == CMD_ENABLE_HOST_SVC_CHECKS || cmd == CMD_DISABLE_HOST_SVC_CHECKS ) ? "checks" : "notifications" ) ;
 help_text [ sizeof ( help_text ) - 1 ] = '\x0' ;
 printf ( "<tr><td class=\"objectDescription descriptionleft\">%s For Host Too:" , ( cmd == CMD_ENABLE_HOST_SVC_CHECKS || cmd == CMD_ENABLE_HOST_SVC_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 print_help_box ( help_text ) ;
 printf ( "</td><td align=\"left\"><INPUT TYPE='checkbox' NAME='ahas'></td></tr>\n" ) ;
 }
 if ( cmd == CMD_ENABLE_HOST_NOTIFICATIONS || cmd == CMD_DISABLE_HOST_NOTIFICATIONS ) {
 snprintf ( help_text , sizeof ( help_text ) , "%s notifications te be sent out to child hosts." , ( cmd == CMD_ENABLE_HOST_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 help_text [ sizeof ( help_text ) - 1 ] = '\x0' ;
 printf ( "<tr><td class=\"objectDescription descriptionleft\">%s Notifications For Child Hosts Too:" , ( cmd == CMD_ENABLE_HOST_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 print_help_box ( help_text ) ;
 printf ( "</td><td align=\"left\"><INPUT TYPE='checkbox' NAME='ptc'></td></tr>\n" ) ;
 }
 break ;
 case CMD_ENABLE_NOTIFICATIONS : case CMD_DISABLE_NOTIFICATIONS : case CMD_SHUTDOWN_PROCESS : case CMD_RESTART_PROCESS : case CMD_START_EXECUTING_SVC_CHECKS : case CMD_STOP_EXECUTING_SVC_CHECKS : case CMD_START_ACCEPTING_PASSIVE_SVC_CHECKS : case CMD_STOP_ACCEPTING_PASSIVE_SVC_CHECKS : case CMD_ENABLE_EVENT_HANDLERS : case CMD_DISABLE_EVENT_HANDLERS : case CMD_START_OBSESSING_OVER_SVC_CHECKS : case CMD_STOP_OBSESSING_OVER_SVC_CHECKS : case CMD_ENABLE_FLAP_DETECTION : case CMD_DISABLE_FLAP_DETECTION : case CMD_ENABLE_FAILURE_PREDICTION : case CMD_DISABLE_FAILURE_PREDICTION : case CMD_ENABLE_PERFORMANCE_DATA : case CMD_DISABLE_PERFORMANCE_DATA : case CMD_START_EXECUTING_HOST_CHECKS : case CMD_STOP_EXECUTING_HOST_CHECKS : case CMD_START_ACCEPTING_PASSIVE_HOST_CHECKS : case CMD_STOP_ACCEPTING_PASSIVE_HOST_CHECKS : case CMD_START_OBSESSING_OVER_HOST_CHECKS : case CMD_STOP_OBSESSING_OVER_HOST_CHECKS : if ( cmd == CMD_DISABLE_NOTIFICATIONS ) {
 print_form_element ( PRINT_EXPIRE_DISABLE_NOTIFICATIONS , cmd ) ;
 }
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 else {
 if ( cmd != CMD_DISABLE_NOTIFICATIONS ) {
 printf ( "<tr><td COLSPAN=\"2\">&nbsp;
</td></tr>\n" ) ;
 printf ( "<tr><td CLASS='objectDescription' colspan=2>There are no options for this command.<br>Click the 'Commit' button to submit the command.</td></tr>\n" ) ;
 }
 }
 break ;
 case CMD_PROCESS_HOST_CHECK_RESULT : case CMD_PROCESS_SERVICE_CHECK_RESULT : if ( cmd == CMD_PROCESS_SERVICE_CHECK_RESULT ) print_object_list ( PRINT_SERVICE_LIST ) ;
 else print_object_list ( PRINT_HOST_LIST ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 snprintf ( help_text , sizeof ( help_text ) , "Set the state which should be send to %s for this %s." , PROGRAM_NAME , ( cmd == CMD_PROCESS_HOST_CHECK_RESULT ) ? "hosts" : "services" ) ;
 help_text [ sizeof ( help_text ) - 1 ] = '\x0' ;
 printf ( "<tr><td class=\"objectDescription descriptionleft\">Check Result:" ) ;
 print_help_box ( help_text ) ;
 printf ( "</td><td align=\"left\">\n" ) ;
 printf ( "\t<SELECT NAME='plugin_state'>\n" ) ;
 if ( cmd == CMD_PROCESS_SERVICE_CHECK_RESULT ) {
 printf ( "\t\t<OPTION VALUE=%d SELECTED>OK</OPTION>\n" , STATE_OK ) ;
 printf ( "\t\t<OPTION VALUE=%d>WARNING</OPTION>\n" , STATE_WARNING ) ;
 printf ( "\t\t<OPTION VALUE=%d>UNKNOWN</OPTION>\n" , STATE_UNKNOWN ) ;
 printf ( "\t\t<OPTION VALUE=%d>CRITICAL</OPTION>\n" , STATE_CRITICAL ) ;
 }
 else {
 printf ( "\t\t<OPTION VALUE=0 SELECTED>UP</OPTION>\n" ) ;
 printf ( "\t\t<OPTION VALUE=1>DOWN</OPTION>\n" ) ;
 printf ( "\t\t<OPTION VALUE=2>UNREACHABLE</OPTION>\n" ) ;
 }
 printf ( "\t</SELECT>\n" ) ;
 printf ( "</td></tr>\n" ) ;
 print_form_element ( PRINT_CHECK_OUTPUT_BOX , cmd ) ;
 print_form_element ( PRINT_PERFORMANCE_DATA_BOX , cmd ) ;
 break ;
 case CMD_SCHEDULE_HOST_DOWNTIME : case CMD_SCHEDULE_HOST_SVC_DOWNTIME : case CMD_SCHEDULE_SVC_DOWNTIME : if ( cmd == CMD_SCHEDULE_SVC_DOWNTIME ) print_object_list ( PRINT_SERVICE_LIST ) ;
 else print_object_list ( PRINT_HOST_LIST ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 snprintf ( help_text , sizeof ( help_text ) , "Define here if this downtime should get triggerd by another downtime of a particular %s." , ( cmd == CMD_PROCESS_HOST_CHECK_RESULT ) ? "host" : "service" ) ;
 help_text [ sizeof ( help_text ) - 1 ] = '\x0' ;
 printf ( "<tr id=\"trigger_select\"><td class=\"objectDescription descriptionleft\">Triggered By:" ) ;
 print_help_box ( help_text ) ;
 printf ( "</td><td align=\"left\">\n" ) ;
 printf ( "\t<SELECT name='trigger'>\n" ) ;
 printf ( "\t\t<OPTION VALUE='0'>N/A</OPTION>\n" ) ;
 for ( temp_downtime = scheduled_downtime_list ;
 temp_downtime != NULL ;
 temp_downtime = temp_downtime -> next ) {
 if ( temp_downtime -> type != HOST_DOWNTIME ) continue ;
 temp_host = find_host ( temp_downtime -> host_name ) ;
 if ( is_authorized_for_host ( temp_host , & current_authdata ) == FALSE ) continue ;
 printf ( "\t\t<OPTION VALUE='%lu'>" , temp_downtime -> downtime_id ) ;
 get_time_string ( & temp_downtime -> start_time , start_time , sizeof ( start_time ) , SHORT_DATE_TIME ) ;
 printf ( "ID: %lu, Host '%s' starting @ %s</OPTION>\n" , temp_downtime -> downtime_id , temp_downtime -> host_name , start_time ) ;
 found_trigger_objects = TRUE ;
 }
 for ( temp_downtime = scheduled_downtime_list ;
 temp_downtime != NULL ;
 temp_downtime = temp_downtime -> next ) {
 if ( temp_downtime -> type != SERVICE_DOWNTIME ) continue ;
 printf ( "\t\t<OPTION VALUE='%lu'>" , temp_downtime -> downtime_id ) ;
 get_time_string ( & temp_downtime -> start_time , start_time , sizeof ( start_time ) , SHORT_DATE_TIME ) ;
 printf ( "ID: %lu, Service '%s' on host '%s' starting @ %s</OPTION>\n" , temp_downtime -> downtime_id , temp_downtime -> service_description , temp_downtime -> host_name , start_time ) ;
 found_trigger_objects = TRUE ;
 }
 printf ( "\t</SELECT>\n" ) ;
 printf ( "</td></tr>\n" ) ;
 if ( ! found_trigger_objects ) printf ( "<tr style=\"display:none;
\"><td colspan=2><script language=\"JavaScript\">document.getElementById('trigger_select').style.display = 'none';
</script></td></tr>\n" ) ;
 print_form_element ( PRINT_START_TIME , cmd ) ;
 print_form_element ( PRINT_END_TIME , cmd ) ;
 print_form_element ( PRINT_FIXED_FLEXIBLE_TYPE , cmd ) ;
 if ( cmd == CMD_SCHEDULE_HOST_DOWNTIME ) {
 snprintf ( help_text , sizeof ( help_text ) , "Define here what should be done with the child hosts of these hosts." ) ;
 help_text [ sizeof ( help_text ) - 1 ] = '\x0' ;
 printf ( "<tr><td class=\"objectDescription descriptionleft\">Child Hosts:" ) ;
 print_help_box ( help_text ) ;
 printf ( "</td><td align=\"left\">\n" ) ;
 printf ( "\t<SELECT name='childoptions'>\n" ) ;
 printf ( "\t\t<OPTION VALUE='0'>Do nothing with child hosts</OPTION>\n" ) ;
 printf ( "\t\t<OPTION VALUE='1'>Schedule triggered downtime for all child hosts</OPTION>\n" ) ;
 printf ( "\t\t<OPTION VALUE='2'>Schedule non-triggered downtime for all child hosts</OPTION>\n" ) ;
 printf ( "\t</SELECT>\n" ) ;
 printf ( "</td></tr>\n" ) ;
 }
 break ;
 case CMD_ENABLE_HOSTGROUP_SVC_NOTIFICATIONS : case CMD_DISABLE_HOSTGROUP_SVC_NOTIFICATIONS : case CMD_ENABLE_HOSTGROUP_HOST_NOTIFICATIONS : case CMD_DISABLE_HOSTGROUP_HOST_NOTIFICATIONS : case CMD_ENABLE_HOSTGROUP_SVC_CHECKS : case CMD_DISABLE_HOSTGROUP_SVC_CHECKS : printf ( "<tr><td COLSPAN=\"2\">&nbsp;
</td></tr>\n" ) ;
 printf ( "<tr class=\"statusEven\" ><td width=\"50%%\" style=\"font-weight:bold;
\">Hostgroup Name:</td>" ) ;
 printf ( "<td><INPUT TYPE='HIDDEN' NAME='hostgroup' VALUE='%s'>%s</td></tr>\n" , escape_string ( hostgroup_name ) , escape_string ( hostgroup_name ) ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 if ( cmd == CMD_ENABLE_HOSTGROUP_SVC_CHECKS || cmd == CMD_DISABLE_HOSTGROUP_SVC_CHECKS || cmd == CMD_ENABLE_HOSTGROUP_SVC_NOTIFICATIONS || cmd == CMD_DISABLE_HOSTGROUP_SVC_NOTIFICATIONS ) {
 if ( enforce_comments_on_actions != TRUE ) print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 printf ( "<tr><td class=\"objectDescription descriptionleft\">%s For Hosts Too:</td><td align=\"left\">\n" , ( cmd == CMD_ENABLE_HOSTGROUP_SVC_CHECKS || cmd == CMD_ENABLE_HOSTGROUP_SVC_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 printf ( "<INPUT TYPE='checkbox' NAME='ahas'></td></tr>\n" ) ;
 }
 break ;
 case CMD_ENABLE_SERVICEGROUP_SVC_NOTIFICATIONS : case CMD_DISABLE_SERVICEGROUP_SVC_NOTIFICATIONS : case CMD_ENABLE_SERVICEGROUP_HOST_NOTIFICATIONS : case CMD_DISABLE_SERVICEGROUP_HOST_NOTIFICATIONS : case CMD_ENABLE_SERVICEGROUP_SVC_CHECKS : case CMD_DISABLE_SERVICEGROUP_SVC_CHECKS : printf ( "<tr><td COLSPAN=\"2\">&nbsp;
</td></tr>\n" ) ;
 printf ( "<tr class=\"statusEven\"><td width=\"50%%\" style=\"font-weight:bold;
\">Servicegroup Name:</td>" ) ;
 printf ( "<td><INPUT TYPE='HIDDEN' NAME='servicegroup' VALUE='%s'>%s</td></tr>\n" , escape_string ( servicegroup_name ) , escape_string ( servicegroup_name ) ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 }
 if ( cmd == CMD_ENABLE_SERVICEGROUP_SVC_CHECKS || cmd == CMD_DISABLE_SERVICEGROUP_SVC_CHECKS || cmd == CMD_ENABLE_SERVICEGROUP_SVC_NOTIFICATIONS || cmd == CMD_DISABLE_SERVICEGROUP_SVC_NOTIFICATIONS ) {
 if ( enforce_comments_on_actions != TRUE ) print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 printf ( "<tr><td class=\"objectDescription descriptionleft\">%s For Hosts Too:</td><td align=\"left\">\n" , ( cmd == CMD_ENABLE_SERVICEGROUP_SVC_CHECKS || cmd == CMD_ENABLE_SERVICEGROUP_SVC_NOTIFICATIONS ) ? "Enable" : "Disable" ) ;
 printf ( "<INPUT TYPE='checkbox' NAME='ahas'></td></tr>\n" ) ;
 }
 break ;
 case CMD_SCHEDULE_HOSTGROUP_HOST_DOWNTIME : case CMD_SCHEDULE_HOSTGROUP_SVC_DOWNTIME : case CMD_SCHEDULE_SERVICEGROUP_HOST_DOWNTIME : case CMD_SCHEDULE_SERVICEGROUP_SVC_DOWNTIME : printf ( "<tr><td COLSPAN=\"2\">&nbsp;
</td></tr>\n" ) ;
 printf ( "<tr class=\"statusEven\"><td width=\"50%%\" style=\"font-weight:bold;
\">" ) ;
 if ( cmd == CMD_SCHEDULE_HOSTGROUP_HOST_DOWNTIME || cmd == CMD_SCHEDULE_HOSTGROUP_SVC_DOWNTIME ) printf ( "Hostgroup Name:</td><td><INPUT TYPE='HIDDEN' NAME='hostgroup' VALUE='%s'>%s</td></tr>\n" , escape_string ( hostgroup_name ) , escape_string ( hostgroup_name ) ) ;
 else printf ( "Servicegroup Name:</td><td><INPUT TYPE='HIDDEN' NAME='servicegroup' VALUE='%s'>%s</td></tr>\n" , escape_string ( servicegroup_name ) , escape_string ( servicegroup_name ) ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 print_form_element ( PRINT_START_TIME , cmd ) ;
 print_form_element ( PRINT_END_TIME , cmd ) ;
 print_form_element ( PRINT_FIXED_FLEXIBLE_TYPE , cmd ) ;
 if ( cmd == CMD_SCHEDULE_HOSTGROUP_SVC_DOWNTIME || cmd == CMD_SCHEDULE_SERVICEGROUP_SVC_DOWNTIME ) {
 printf ( "<tr><td class=\"objectDescription descriptionleft\">Schedule Downtime For Hosts Too:</td><td align=\"left\">\n" ) ;
 printf ( "<INPUT TYPE='checkbox' NAME='ahas'></td></tr>\n" ) ;
 }
 break ;
 case CMD_SEND_CUSTOM_HOST_NOTIFICATION : case CMD_SEND_CUSTOM_SVC_NOTIFICATION : if ( cmd == CMD_SEND_CUSTOM_SVC_NOTIFICATION ) print_object_list ( PRINT_SERVICE_LIST ) ;
 else print_object_list ( PRINT_HOST_LIST ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 print_form_element ( PRINT_AUTHOR , cmd ) ;
 print_form_element ( PRINT_COMMENT_BOX , cmd ) ;
 print_form_element ( PRINT_FORCE_NOTIFICATION , cmd ) ;
 print_form_element ( PRINT_BROADCAST_NOTIFICATION , cmd ) ;
 break ;
 case CMD_CHANGE_HOST_MODATTR : print_object_list ( PRINT_HOST_LIST ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 printf ( "<tr class=\"statusEven\"><td width=\"50%%\" style=\"font-weight:bold;
\">Modified Attributes:</td>" ) ;
 printf ( "<td><INPUT TYPE='HIDDEN' NAME='attr' VALUE='%lu'>" , attr ) ;
 print_modified_attributes ( HTML_CONTENT , CMD_CGI , attr ) ;
 printf ( "</td></tr>\n" ) ;
 break ;
 case CMD_CHANGE_SVC_MODATTR : print_object_list ( PRINT_SERVICE_LIST ) ;
 print_form_element ( PRINT_COMMON_HEADER , cmd ) ;
 printf ( "<tr class=\"statusEven\"><td width=\"50%%\" style=\"font-weight:bold;
\">Modified Attributes:</td>" ) ;
 printf ( "<td><INPUT TYPE='HIDDEN' NAME='attr' VALUE='%lu'>" , attr ) ;
 print_modified_attributes ( HTML_CONTENT , CMD_CGI , attr ) ;
 printf ( "</td></tr>\n" ) ;
 break ;
 default : printf ( "<tr><td CLASS='objectDescription' COLSPAN=\"2\">This should not be happening... :-(</td></tr>\n" ) ;
 }
 printf ( "<tr><td COLSPAN=\"2\">&nbsp;
</td></tr>\n" ) ;
 printf ( "<tr CLASS='sectionHeader'><td COLSPAN=\"2\" class=\"commitButton\"><INPUT TYPE=\"submit\" NAME=\"btnSubmit\" VALUE=\"Commit\" class=\"submitButton\">&nbsp;
&nbsp;
|&nbsp;
&nbsp;
<a HREF=\"javascript:window.history.go(-1)\">Cancel</a></td></tr>\n" ) ;
 printf ( "</table>\n" ) ;
 printf ( "</td></tr></table>\n" ) ;
 printf ( "</form>\n" ) ;
 printf ( "</div>\n" ) ;
 return ;
 }