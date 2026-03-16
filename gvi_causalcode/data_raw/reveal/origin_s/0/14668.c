int process_cgivars ( void ) {
 char * * variables ;
 char * temp_buffer = NULL ;
 int error = FALSE ;
 int x ;
 int z = 0 ;
 int sticky_ack_set = FALSE ;
 int send_notification_set = FALSE ;
 variables = getcgivars ( ) ;
 for ( x = 0 ;
 variables [ x ] != NULL ;
 x ++ ) {
 if ( strlen ( variables [ x ] ) >= MAX_INPUT_BUFFER - 1 ) continue ;
 else if ( ! strcmp ( variables [ x ] , "cmd_typ" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 command_type = atoi ( variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "attr" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 attr = strtoul ( variables [ x ] , NULL , 10 ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "cmd_mod" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 command_mode = atoi ( variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "com_id" ) || ! strcmp ( variables [ x ] , "down_id" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 multi_ids [ z ] = strtoul ( variables [ x ] , NULL , 10 ) ;
 z ++ ;
 }
 else if ( ! strcmp ( variables [ x ] , "not_dly" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 notification_delay = atoi ( variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "sched_dly" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 schedule_delay = atoi ( variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "com_author" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( ( comment_author = ( char * ) strdup ( variables [ x ] ) ) == NULL ) comment_author = "" ;
 strip_html_brackets ( comment_author ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "com_data" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( ( comment_data = ( char * ) strdup ( variables [ x ] ) ) == NULL ) comment_data = "" ;
 strip_html_brackets ( comment_data ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "host" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( ( host_name = ( char * ) strdup ( variables [ x ] ) ) == NULL ) host_name = "" ;
 else {
 strip_html_brackets ( host_name ) ;
 commands [ x ] . host_name = host_name ;
 }
 }
 else if ( ! strcmp ( variables [ x ] , "hostgroup" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( ( hostgroup_name = ( char * ) strdup ( variables [ x ] ) ) == NULL ) hostgroup_name = "" ;
 strip_html_brackets ( hostgroup_name ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "service" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( ( service_desc = ( char * ) strdup ( variables [ x ] ) ) == NULL ) service_desc = "" ;
 else {
 strip_html_brackets ( service_desc ) ;
 commands [ ( x - 2 ) ] . description = service_desc ;
 }
 }
 else if ( ! strcmp ( variables [ x ] , "hostservice" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 temp_buffer = strtok ( variables [ x ] , "^" ) ;
 if ( ( host_name = ( char * ) strdup ( temp_buffer ) ) == NULL ) host_name = "" ;
 else {
 strip_html_brackets ( host_name ) ;
 commands [ x ] . host_name = host_name ;
 }
 temp_buffer = strtok ( NULL , "" ) ;
 if ( ( service_desc = ( char * ) strdup ( temp_buffer ) ) == NULL ) service_desc = "" ;
 else {
 strip_html_brackets ( service_desc ) ;
 commands [ x ] . description = service_desc ;
 }
 }
 else if ( ! strcmp ( variables [ x ] , "servicegroup" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( ( servicegroup_name = ( char * ) strdup ( variables [ x ] ) ) == NULL ) servicegroup_name = "" ;
 strip_html_brackets ( servicegroup_name ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "persistent" ) ) persistent_comment = TRUE ;
 else if ( ! strcmp ( variables [ x ] , "send_notification" ) ) send_notification_set = TRUE ;
 else if ( ! strcmp ( variables [ x ] , "sticky_ack" ) ) sticky_ack_set = TRUE ;
 else if ( ! strcmp ( variables [ x ] , "use_ack_end_time" ) ) use_ack_end_time = TRUE ;
 else if ( ! strcmp ( variables [ x ] , "use_disabled_notif_end_time" ) ) use_disabled_notif_end_time = TRUE ;
 else if ( ! strcmp ( variables [ x ] , "force_check" ) ) force_check = TRUE ;
 else if ( ! strcmp ( variables [ x ] , "ahas" ) ) affect_host_and_services = TRUE ;
 else if ( ! strcmp ( variables [ x ] , "ptc" ) ) propagate_to_children = TRUE ;
 else if ( ! strcmp ( variables [ x ] , "fixed" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 fixed = ( atoi ( variables [ x ] ) > 0 ) ? TRUE : FALSE ;
 }
 else if ( ! strcmp ( variables [ x ] , "trigger" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 triggered_by = strtoul ( variables [ x ] , NULL , 10 ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "childoptions" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 child_options = atoi ( variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "plugin_output" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( strlen ( variables [ x ] ) >= MAX_INPUT_BUFFER - 1 ) {
 error = TRUE ;
 break ;
 }
 else strcpy ( plugin_output , variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "performance_data" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( strlen ( variables [ x ] ) >= MAX_INPUT_BUFFER - 1 ) {
 error = TRUE ;
 break ;
 }
 else strcpy ( performance_data , variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "plugin_state" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 plugin_state = atoi ( variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "hours" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( atoi ( variables [ x ] ) < 0 ) {
 error = TRUE ;
 break ;
 }
 duration += ( unsigned long ) ( atoi ( variables [ x ] ) * 3600 ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "minutes" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 if ( atoi ( variables [ x ] ) < 0 ) {
 error = TRUE ;
 break ;
 }
 duration += ( unsigned long ) ( atoi ( variables [ x ] ) * 60 ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "start_time" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 start_time_string = ( char * ) malloc ( strlen ( variables [ x ] ) + 1 ) ;
 if ( start_time_string == NULL ) start_time_string = "" ;
 else strcpy ( start_time_string , variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "end_time" ) ) {
 x ++ ;
 if ( variables [ x ] == NULL ) {
 error = TRUE ;
 break ;
 }
 end_time_string = ( char * ) malloc ( strlen ( variables [ x ] ) + 1 ) ;
 if ( end_time_string == NULL ) end_time_string = "" ;
 else strcpy ( end_time_string , variables [ x ] ) ;
 }
 else if ( ! strcmp ( variables [ x ] , "force_notification" ) ) force_notification = NOTIFICATION_OPTION_FORCED ;
 else if ( ! strcmp ( variables [ x ] , "broadcast_notification" ) ) broadcast_notification = NOTIFICATION_OPTION_BROADCAST ;
 else if ( ! strcmp ( variables [ x ] , "nodaemoncheck" ) ) daemon_check = FALSE ;
 }
 if ( command_mode == CMDMODE_COMMIT ) {
 send_notification = send_notification_set ;
 sticky_ack = sticky_ack_set ;
 }
 free_cgivars ( variables ) ;
 return error ;
 }