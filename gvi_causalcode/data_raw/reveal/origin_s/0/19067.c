static void sig_server_connecting ( SERVER_REC * server , IPADDR * ip ) {
 char ipaddr [ MAX_IP_LEN ] ;
 g_return_if_fail ( server != NULL ) ;
 if ( ip == NULL ) ipaddr [ 0 ] = '\0' ;
 else net_ip2host ( ip , ipaddr ) ;
 printformat ( server , NULL , MSGLEVEL_CLIENTNOTICE , ! server -> connrec -> reconnecting ? TXT_CONNECTING : TXT_RECONNECTING , server -> connrec -> address , ipaddr , server -> connrec -> port ) ;
 }