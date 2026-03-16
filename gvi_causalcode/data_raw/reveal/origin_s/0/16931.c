int main ( int argc , char * * argv ) {
 int option_idx = 0 ;
 int result ;
 const char * adb_server_ip = NULL ;
 unsigned short * adb_server_tcp_port = NULL ;
 unsigned int logcat_text = 0 ;
 const char * default_adb_server_ip = "127.0.0.1" ;
 unsigned short default_adb_server_tcp_port = 5037 ;
 unsigned short local_adb_server_tcp_port ;
 unsigned short local_bt_server_tcp_port ;
 unsigned short local_bt_local_tcp_port ;
 unsigned short * bt_server_tcp_port = NULL ;
 unsigned int bt_forward_socket = 0 ;
 const char * bt_local_ip = NULL ;
 unsigned short * bt_local_tcp_port = NULL ;
 unsigned short default_bt_server_tcp_port = 4330 ;
 const char * default_bt_local_ip = "127.0.0.1" ;
 unsigned short default_bt_local_tcp_port = 4330 ;
 extcap_parameters * extcap_conf = NULL ;

 attach_parent_console ( ) ;

 optind = 0 ;
 if ( argc == 1 ) {
 help ( ) ;
 return EXIT_CODE_SUCCESS ;
 }
 extcap_conf = g_new0 ( extcap_parameters , 1 ) ;
 extcap_base_set_util_info ( extcap_conf , ANDROIDDUMP_VERSION_MAJOR , ANDROIDDUMP_VERSION_MINOR , ANDROIDDUMP_VERSION_RELEASE , NULL ) ;
 while ( ( result = getopt_long ( argc , argv , "" , longopts , & option_idx ) ) != - 1 ) {
 switch ( result ) {
 case OPT_VERSION : printf ( "%s.%s.%s\n" , ANDROIDDUMP_VERSION_MAJOR , ANDROIDDUMP_VERSION_MINOR , ANDROIDDUMP_VERSION_RELEASE ) ;
 return EXIT_CODE_SUCCESS ;
 case OPT_VERBOSE : if ( optarg ) verbose = ( g_ascii_strncasecmp ( optarg , "TRUE" , 4 ) == 0 ) ;
 else verbose = 1 ;
 {
 int j = 0 ;
 verbose_print ( "VERBOSE: Command line: " ) ;
 while ( j < argc ) {
 verbose_print ( "%s " , argv [ j ] ) ;
 j += 1 ;
 }
 verbose_print ( "\n" ) ;
 }
 break ;
 case OPT_HELP : help ( ) ;
 return EXIT_CODE_SUCCESS ;
 case OPT_CONFIG_ADB_SERVER_IP : adb_server_ip = optarg ;
 break ;
 case OPT_CONFIG_ADB_SERVER_TCP_PORT : adb_server_tcp_port = & local_adb_server_tcp_port ;
 if ( ! optarg ) {
 errmsg_print ( "ERROR: Impossible exception. Parameter required argument, but there is no it right now." ) ;
 return EXIT_CODE_GENERIC ;
 }
 * adb_server_tcp_port = ( unsigned short ) g_ascii_strtoull ( optarg , NULL , 10 ) ;
 break ;
 case OPT_CONFIG_LOGCAT_TEXT : logcat_text = ( g_ascii_strncasecmp ( optarg , "TRUE" , 4 ) == 0 ) ;
 break ;
 case OPT_CONFIG_BT_SERVER_TCP_PORT : bt_server_tcp_port = & local_bt_server_tcp_port ;
 if ( ! optarg ) {
 errmsg_print ( "ERROR: Impossible exception. Parameter required argument, but there is no it right now." ) ;
 return EXIT_CODE_GENERIC ;
 }
 * bt_server_tcp_port = ( unsigned short ) g_ascii_strtoull ( optarg , NULL , 10 ) ;
 break ;
 case OPT_CONFIG_BT_FORWARD_SOCKET : bt_forward_socket = ( g_ascii_strncasecmp ( optarg , "TRUE" , 4 ) == 0 ) ;
 break ;
 case OPT_CONFIG_BT_LOCAL_IP : bt_local_ip = optarg ;
 break ;
 case OPT_CONFIG_BT_LOCAL_TCP_PORT : bt_local_tcp_port = & local_bt_local_tcp_port ;
 if ( ! optarg ) {
 errmsg_print ( "ERROR: Impossible exception. Parameter required argument, but there is no it right now." ) ;
 return EXIT_CODE_GENERIC ;
 }
 * bt_local_tcp_port = ( unsigned short ) g_ascii_strtoull ( optarg , NULL , 10 ) ;
 break ;
 default : if ( ! extcap_base_parse_options ( extcap_conf , result - EXTCAP_OPT_LIST_INTERFACES , optarg ) ) {
 printf ( "Invalid argument <%s>. Try --help.\n" , argv [ optind - 1 ] ) ;
 return EXIT_CODE_GENERIC ;
 }
 }
 }
 if ( ! adb_server_ip ) adb_server_ip = default_adb_server_ip ;
 if ( ! adb_server_tcp_port ) adb_server_tcp_port = & default_adb_server_tcp_port ;
 if ( ! bt_server_tcp_port ) bt_server_tcp_port = & default_bt_server_tcp_port ;
 if ( ! bt_local_ip ) bt_local_ip = default_bt_local_ip ;
 if ( ! bt_local_tcp_port ) bt_local_tcp_port = & default_bt_local_tcp_port ;

 if ( result != 0 ) {
 errmsg_print ( "ERROR: WSAStartup failed with error: %d" , result ) ;
 return EXIT_CODE_GENERIC ;
 }

 if ( extcap_base_handle_interface ( extcap_conf ) ) return EXIT_CODE_SUCCESS ;
 if ( extcap_conf -> show_config ) return list_config ( extcap_conf -> interface ) ;
 if ( extcap_conf -> capture ) {
 if ( extcap_conf -> interface && ( is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_LOGCAT_MAIN ) || is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_LOGCAT_SYSTEM ) || is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_LOGCAT_RADIO ) || is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_LOGCAT_EVENTS ) ) ) if ( logcat_text ) return capture_android_logcat_text ( extcap_conf -> interface , extcap_conf -> fifo , adb_server_ip , adb_server_tcp_port ) ;
 else return capture_android_logcat ( extcap_conf -> interface , extcap_conf -> fifo , adb_server_ip , adb_server_tcp_port ) ;
 else if ( extcap_conf -> interface && ( is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_LOGCAT_TEXT_MAIN ) || is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_LOGCAT_TEXT_SYSTEM ) || is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_LOGCAT_TEXT_RADIO ) || is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_LOGCAT_TEXT_EVENTS ) || ( is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_LOGCAT_TEXT_CRASH ) ) ) ) return capture_android_logcat_text ( extcap_conf -> interface , extcap_conf -> fifo , adb_server_ip , adb_server_tcp_port ) ;
 else if ( extcap_conf -> interface && is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_BLUETOOTH_HCIDUMP ) ) return capture_android_bluetooth_hcidump ( extcap_conf -> interface , extcap_conf -> fifo , adb_server_ip , adb_server_tcp_port ) ;
 else if ( extcap_conf -> interface && is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_BLUETOOTH_EXTERNAL_PARSER ) ) return capture_android_bluetooth_external_parser ( extcap_conf -> interface , extcap_conf -> fifo , adb_server_ip , adb_server_tcp_port , bt_server_tcp_port , bt_forward_socket , bt_local_ip , bt_local_tcp_port ) ;
 else if ( extcap_conf -> interface && ( is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_BLUETOOTH_BTSNOOP_NET ) ) ) return capture_android_bluetooth_btsnoop_net ( extcap_conf -> interface , extcap_conf -> fifo , adb_server_ip , adb_server_tcp_port ) ;
 else if ( extcap_conf -> interface && ( is_specified_interface ( extcap_conf -> interface , INTERFACE_ANDROID_WIFI_TCPDUMP ) ) ) return capture_android_wifi_tcpdump ( extcap_conf -> interface , extcap_conf -> fifo , adb_server_ip , adb_server_tcp_port ) ;
 else return EXIT_CODE_GENERIC ;
 }
 extcap_base_cleanup ( & extcap_conf ) ;
 return EXIT_CODE_SUCCESS ;
 }