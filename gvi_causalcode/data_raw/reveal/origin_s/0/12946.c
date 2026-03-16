static void cmd_network_add_modify ( const char * data , gboolean add ) {
 GHashTable * optlist ;
 char * name , * value ;
 void * free_arg ;
 IRC_CHATNET_REC * rec ;
 if ( ! cmd_get_params ( data , & free_arg , 1 | PARAM_FLAG_OPTIONS , "network add" , & optlist , & name ) ) return ;
 if ( * name == '\0' ) cmd_param_error ( CMDERR_NOT_ENOUGH_PARAMS ) ;
 rec = ircnet_find ( name ) ;
 if ( rec == NULL ) {
 if ( add == FALSE ) {
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , IRCTXT_NETWORK_NOT_FOUND , name ) ;
 cmd_params_free ( free_arg ) ;
 return ;
 }
 rec = g_new0 ( IRC_CHATNET_REC , 1 ) ;
 rec -> name = g_strdup ( name ) ;
 }
 else {
 if ( g_hash_table_lookup ( optlist , "nick" ) ) g_free_and_null ( rec -> nick ) ;
 if ( g_hash_table_lookup ( optlist , "alternate_nick" ) ) g_free_and_null ( rec -> alternate_nick ) ;
 if ( g_hash_table_lookup ( optlist , "user" ) ) g_free_and_null ( rec -> username ) ;
 if ( g_hash_table_lookup ( optlist , "realname" ) ) g_free_and_null ( rec -> realname ) ;
 if ( g_hash_table_lookup ( optlist , "host" ) ) {
 g_free_and_null ( rec -> own_host ) ;
 rec -> own_ip4 = rec -> own_ip6 = NULL ;
 }
 if ( g_hash_table_lookup ( optlist , "usermode" ) ) g_free_and_null ( rec -> usermode ) ;
 if ( g_hash_table_lookup ( optlist , "autosendcmd" ) ) g_free_and_null ( rec -> autosendcmd ) ;
 if ( g_hash_table_lookup ( optlist , "sasl_mechanism" ) ) g_free_and_null ( rec -> sasl_mechanism ) ;
 if ( g_hash_table_lookup ( optlist , "sasl_username" ) ) g_free_and_null ( rec -> sasl_username ) ;
 if ( g_hash_table_lookup ( optlist , "sasl_password" ) ) g_free_and_null ( rec -> sasl_password ) ;
 }
 value = g_hash_table_lookup ( optlist , "kicks" ) ;
 if ( value != NULL ) rec -> max_kicks = atoi ( value ) ;
 value = g_hash_table_lookup ( optlist , "msgs" ) ;
 if ( value != NULL ) rec -> max_msgs = atoi ( value ) ;
 value = g_hash_table_lookup ( optlist , "modes" ) ;
 if ( value != NULL ) rec -> max_modes = atoi ( value ) ;
 value = g_hash_table_lookup ( optlist , "whois" ) ;
 if ( value != NULL ) rec -> max_whois = atoi ( value ) ;
 value = g_hash_table_lookup ( optlist , "cmdspeed" ) ;
 if ( value != NULL ) rec -> cmd_queue_speed = atoi ( value ) ;
 value = g_hash_table_lookup ( optlist , "cmdmax" ) ;
 if ( value != NULL ) rec -> max_cmds_at_once = atoi ( value ) ;
 value = g_hash_table_lookup ( optlist , "querychans" ) ;
 if ( value != NULL ) rec -> max_query_chans = atoi ( value ) ;
 value = g_hash_table_lookup ( optlist , "nick" ) ;
 if ( value != NULL && * value != '\0' ) rec -> nick = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "alternate_nick" ) ;
 if ( value != NULL && * value != '\0' ) rec -> alternate_nick = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "user" ) ;
 if ( value != NULL && * value != '\0' ) rec -> username = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "realname" ) ;
 if ( value != NULL && * value != '\0' ) rec -> realname = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "host" ) ;
 if ( value != NULL && * value != '\0' ) {
 rec -> own_host = g_strdup ( value ) ;
 rec -> own_ip4 = rec -> own_ip6 = NULL ;
 }
 value = g_hash_table_lookup ( optlist , "usermode" ) ;
 if ( value != NULL && * value != '\0' ) rec -> usermode = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "autosendcmd" ) ;
 if ( value != NULL && * value != '\0' ) rec -> autosendcmd = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "sasl_mechanism" ) ;
 if ( value != NULL ) rec -> sasl_mechanism = * value != '\0' ? g_strdup ( value ) : NULL ;
 value = g_hash_table_lookup ( optlist , "sasl_username" ) ;
 if ( value != NULL ) rec -> sasl_username = * value != '\0' ? g_strdup ( value ) : NULL ;
 value = g_hash_table_lookup ( optlist , "sasl_password" ) ;
 if ( value != NULL ) rec -> sasl_password = * value != '\0' ? g_strdup ( value ) : NULL ;
 ircnet_create ( rec ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , IRCTXT_NETWORK_ADDED , name ) ;
 cmd_params_free ( free_arg ) ;
 }