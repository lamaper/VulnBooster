static void help ( void ) {
 unsigned int i_opt ;
 printf ( "Help\n" ) ;
 printf ( " Usage:\n" " androiddump --extcap-interfaces [--adb-server-ip=<arg>] [--adb-server-tcp-port=<arg>]\n" " androiddump --extcap-interface=INTERFACE --extcap-dlts\n" " androiddump --extcap-interface=INTERFACE --extcap-config\n" " androiddump --extcap-interface=INTERFACE --fifo=PATH_FILENAME --capture \n" ) ;
 printf ( "\n Parameters:\n" ) ;
 for ( i_opt = 0 ;
 i_opt < ( sizeof ( longopts ) / sizeof ( longopts [ 0 ] ) ) - 1 ;
 i_opt += 1 ) {
 printf ( " --%s%s\n" , longopts [ i_opt ] . name , ( longopts [ i_opt ] . has_arg == required_argument ) ? "=<arg>" : ( ( longopts [ i_opt ] . has_arg == optional_argument ) ? "[=arg]" : "" ) ) ;
 }
 }