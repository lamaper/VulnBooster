static void cmd_server_add_modify ( const char * data , gboolean add ) {
 GHashTable * optlist ;
 SERVER_SETUP_REC * rec ;
 char * addr , * portstr , * password , * value , * chatnet ;
 void * free_arg ;
 int port ;
 if ( ! cmd_get_params ( data , & free_arg , 3 | PARAM_FLAG_OPTIONS , "server add" , & optlist , & addr , & portstr , & password ) ) return ;
 if ( * addr == '\0' ) cmd_param_error ( CMDERR_NOT_ENOUGH_PARAMS ) ;
 value = g_hash_table_lookup ( optlist , "port" ) ;
 if ( * portstr != '\0' ) port = atoi ( portstr ) ;
 else if ( value != NULL && * value != '\0' ) port = atoi ( value ) ;
 else if ( g_hash_table_lookup ( optlist , "tls" ) || g_hash_table_lookup ( optlist , "ssl" ) ) port = DEFAULT_SERVER_ADD_TLS_PORT ;
 else port = DEFAULT_SERVER_ADD_PORT ;
 chatnet = g_hash_table_lookup ( optlist , "network" ) ;
 rec = server_setup_find ( addr , port , chatnet ) ;
 if ( rec == NULL ) {
 if ( add == FALSE ) {
 cmd_params_free ( free_arg ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_SETUPSERVER_NOT_FOUND , addr , port ) ;
 return ;
 }
 rec = create_server_setup ( optlist ) ;
 if ( rec == NULL ) {
 cmd_params_free ( free_arg ) ;
 return ;
 }
 rec -> address = g_strdup ( addr ) ;
 rec -> port = port ;
 }
 else {
 if ( * portstr != '\0' || g_hash_table_lookup ( optlist , "port" ) ) rec -> port = port ;
 if ( * password != '\0' ) g_free_and_null ( rec -> password ) ;
 if ( g_hash_table_lookup ( optlist , "host" ) ) {
 g_free_and_null ( rec -> own_host ) ;
 rec -> own_ip4 = rec -> own_ip6 = NULL ;
 }
 }
 if ( g_hash_table_lookup ( optlist , "6" ) ) rec -> family = AF_INET6 ;
 else if ( g_hash_table_lookup ( optlist , "4" ) ) rec -> family = AF_INET ;
 if ( g_hash_table_lookup ( optlist , "tls" ) || g_hash_table_lookup ( optlist , "ssl" ) ) {
 rec -> use_tls = TRUE ;
 }
 else if ( g_hash_table_lookup ( optlist , "notls" ) || g_hash_table_lookup ( optlist , "nossl" ) ) {
 rec -> use_tls = FALSE ;
 rec -> tls_verify = FALSE ;
 }
 value = g_hash_table_lookup ( optlist , "tls_cert" ) ;
 if ( value == NULL ) value = g_hash_table_lookup ( optlist , "ssl_cert" ) ;
 if ( value != NULL && * value != '\0' ) rec -> tls_cert = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "tls_pkey" ) ;
 if ( value == NULL ) value = g_hash_table_lookup ( optlist , "ssl_pkey" ) ;
 if ( value != NULL && * value != '\0' ) rec -> tls_pkey = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "tls_pass" ) ;
 if ( value == NULL ) value = g_hash_table_lookup ( optlist , "ssl_pass" ) ;
 if ( value != NULL && * value != '\0' ) rec -> tls_pass = g_strdup ( value ) ;
 if ( g_hash_table_lookup ( optlist , "tls_verify" ) || g_hash_table_lookup ( optlist , "ssl_verify" ) ) rec -> tls_verify = TRUE ;
 else if ( g_hash_table_lookup ( optlist , "notls_verify" ) || g_hash_table_lookup ( optlist , "nossl_verify" ) ) rec -> tls_verify = FALSE ;
 value = g_hash_table_lookup ( optlist , "tls_cafile" ) ;
 if ( value == NULL ) value = g_hash_table_lookup ( optlist , "ssl_cafile" ) ;
 if ( value != NULL && * value != '\0' ) rec -> tls_cafile = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "tls_capath" ) ;
 if ( value == NULL ) value = g_hash_table_lookup ( optlist , "ssl_capath" ) ;
 if ( value != NULL && * value != '\0' ) rec -> tls_capath = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "tls_ciphers" ) ;
 if ( value == NULL ) value = g_hash_table_lookup ( optlist , "ssl_ciphers" ) ;
 if ( value != NULL && * value != '\0' ) rec -> tls_ciphers = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "tls_pinned_cert" ) ;
 if ( value == NULL ) value = g_hash_table_lookup ( optlist , "ssl_pinned_cert" ) ;
 if ( value != NULL && * value != '\0' ) rec -> tls_pinned_cert = g_strdup ( value ) ;
 value = g_hash_table_lookup ( optlist , "tls_pinned_pubkey" ) ;
 if ( value == NULL ) value = g_hash_table_lookup ( optlist , "ssl_pinned_pubkey" ) ;
 if ( value != NULL && * value != '\0' ) rec -> tls_pinned_pubkey = g_strdup ( value ) ;
 if ( ( rec -> tls_cafile != NULL && rec -> tls_cafile [ 0 ] != '\0' ) || ( rec -> tls_capath != NULL && rec -> tls_capath [ 0 ] != '\0' ) ) rec -> tls_verify = TRUE ;
 if ( ( rec -> tls_cert != NULL && rec -> tls_cert [ 0 ] != '\0' ) || rec -> tls_verify == TRUE ) rec -> use_tls = TRUE ;
 if ( g_hash_table_lookup ( optlist , "auto" ) ) rec -> autoconnect = TRUE ;
 if ( g_hash_table_lookup ( optlist , "noauto" ) ) rec -> autoconnect = FALSE ;
 if ( g_hash_table_lookup ( optlist , "proxy" ) ) rec -> no_proxy = FALSE ;
 if ( g_hash_table_lookup ( optlist , "noproxy" ) ) rec -> no_proxy = TRUE ;
 if ( * password != '\0' && g_strcmp0 ( password , "-" ) != 0 ) rec -> password = g_strdup ( password ) ;
 value = g_hash_table_lookup ( optlist , "host" ) ;
 if ( value != NULL && * value != '\0' ) {
 rec -> own_host = g_strdup ( value ) ;
 rec -> own_ip4 = rec -> own_ip6 = NULL ;
 }
 signal_emit ( "server add fill" , 2 , rec , optlist ) ;
 server_setup_add ( rec ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_SETUPSERVER_ADDED , addr , port ) ;
 cmd_params_free ( free_arg ) ;
 }