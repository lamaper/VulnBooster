int main ( int argc , char * * argv ) {
 extern char * __progname ;
 char * listen_ip ;
 char * errormsg ;


 char * username ;
 char * newroot ;
 char * context ;
 char * device ;
 char * pidfile ;
 int dnsd_fd ;
 int tun_fd ;
 int bind_fd ;
 int bind_enable ;
 int choice ;
 int port ;
 int mtu ;
 int skipipconfig ;
 char * netsize ;
 int ns_get_externalip ;
 int retval ;
 int max_idle_time = 0 ;
 struct sockaddr_storage dnsaddr ;
 int dnsaddr_len ;



 username = NULL ;
 newroot = NULL ;
 context = NULL ;
 device = NULL ;
 foreground = 0 ;
 bind_enable = 0 ;
 bind_fd = 0 ;
 mtu = 1130 ;
 listen_ip = NULL ;
 port = 53 ;
 ns_ip = INADDR_ANY ;
 ns_get_externalip = 0 ;
 check_ip = 1 ;
 skipipconfig = 0 ;
 debug = 0 ;
 netmask = 27 ;
 pidfile = NULL ;
 b32 = get_base32_encoder ( ) ;
 b64 = get_base64_encoder ( ) ;
 b64u = get_base64u_encoder ( ) ;
 b128 = get_base128_encoder ( ) ;
 retval = 0 ;


 if ( __progname == NULL ) __progname = argv [ 0 ] ;
 else __progname ++ ;

 srand ( time ( NULL ) ) ;
 fw_query_init ( ) ;
 while ( ( choice = getopt ( argc , argv , "vcsfhDu:t:d:m:l:p:n:b:P:z:F:i:" ) ) != - 1 ) {
 switch ( choice ) {
 case 'v' : version ( ) ;
 break ;
 case 'c' : check_ip = 0 ;
 break ;
 case 's' : skipipconfig = 1 ;
 break ;
 case 'f' : foreground = 1 ;
 break ;
 case 'h' : help ( ) ;
 break ;
 case 'D' : debug ++ ;
 break ;
 case 'u' : username = optarg ;
 break ;
 case 't' : newroot = optarg ;
 break ;
 case 'd' : device = optarg ;
 break ;
 case 'm' : mtu = atoi ( optarg ) ;
 break ;
 case 'l' : listen_ip = optarg ;
 break ;
 case 'p' : port = atoi ( optarg ) ;
 break ;
 case 'n' : if ( optarg && strcmp ( "auto" , optarg ) == 0 ) {
 ns_get_externalip = 1 ;
 }
 else {
 ns_ip = inet_addr ( optarg ) ;
 }
 break ;
 case 'b' : bind_enable = 1 ;
 bind_port = atoi ( optarg ) ;
 break ;
 case 'F' : pidfile = optarg ;
 break ;
 case 'i' : max_idle_time = atoi ( optarg ) ;
 break ;
 case 'P' : strncpy ( password , optarg , sizeof ( password ) ) ;
 password [ sizeof ( password ) - 1 ] = 0 ;
 memset ( optarg , 0 , strlen ( optarg ) ) ;
 break ;
 case 'z' : context = optarg ;
 break ;
 default : usage ( ) ;
 break ;
 }
 }
 argc -= optind ;
 argv += optind ;
 check_superuser ( usage ) ;
 if ( argc != 2 ) usage ( ) ;
 netsize = strchr ( argv [ 0 ] , '/' ) ;
 if ( netsize ) {
 * netsize = 0 ;
 netsize ++ ;
 netmask = atoi ( netsize ) ;
 }
 my_ip = inet_addr ( argv [ 0 ] ) ;
 if ( my_ip == INADDR_NONE ) {
 warnx ( "Bad IP address to use inside tunnel." ) ;
 usage ( ) ;
 }
 topdomain = strdup ( argv [ 1 ] ) ;
 if ( check_topdomain ( topdomain , & errormsg ) ) {
 warnx ( "Invalid topdomain: %s" , errormsg ) ;
 usage ( ) ;
 }
 if ( username != NULL ) {

 warnx ( "User %s does not exist!" , username ) ;
 usage ( ) ;
 }

 if ( mtu <= 0 ) {
 warnx ( "Bad MTU given." ) ;
 usage ( ) ;
 }
 if ( port < 1 || port > 65535 ) {
 warnx ( "Bad port number given." ) ;
 usage ( ) ;
 }
 if ( port != 53 ) {
 fprintf ( stderr , "ALERT! Other dns servers expect you to run on port 53.\n" ) ;
 fprintf ( stderr , "You must manually forward port 53 to port %d for things to work.\n" , port ) ;
 }
 if ( debug ) {
 fprintf ( stderr , "Debug level %d enabled, will stay in foreground.\n" , debug ) ;
 fprintf ( stderr , "Add more -D switches to set higher debug level.\n" ) ;
 foreground = 1 ;
 }
 dnsaddr_len = get_addr ( listen_ip , port , AF_INET , AI_PASSIVE | AI_NUMERICHOST , & dnsaddr ) ;
 if ( dnsaddr_len < 0 ) {
 warnx ( "Bad IP address to listen on." ) ;
 usage ( ) ;
 }
 if ( bind_enable ) {
 in_addr_t dns_ip = ( ( struct sockaddr_in * ) & dnsaddr ) -> sin_addr . s_addr ;
 if ( bind_port < 1 || bind_port > 65535 ) {
 warnx ( "Bad DNS server port number given." ) ;
 usage ( ) ;
 }
 if ( bind_port == port && ( dns_ip == INADDR_ANY || dns_ip == htonl ( 0x7f000001L ) ) ) {
 warnx ( "Forward port is same as listen port (%d), will create a loop!" , bind_port ) ;
 fprintf ( stderr , "Use -l to set listen ip to avoid this.\n" ) ;
 usage ( ) ;
 }
 fprintf ( stderr , "Requests for domains outside of %s will be forwarded to port %d\n" , topdomain , bind_port ) ;
 }
 if ( ns_get_externalip ) {
 struct in_addr extip ;
 int res = get_external_ip ( & extip ) ;
 if ( res ) {
 fprintf ( stderr , "Failed to get external IP via web service.\n" ) ;
 exit ( 3 ) ;
 }
 ns_ip = extip . s_addr ;
 fprintf ( stderr , "Using %s as external IP.\n" , inet_ntoa ( extip ) ) ;
 }
 if ( ns_ip == INADDR_NONE ) {
 warnx ( "Bad IP address to return as nameserver." ) ;
 usage ( ) ;
 }
 if ( netmask > 30 || netmask < 8 ) {
 warnx ( "Bad netmask (%d bits). Use 8-30 bits." , netmask ) ;
 usage ( ) ;
 }
 if ( strlen ( password ) == 0 ) {
 if ( NULL != getenv ( PASSWORD_ENV_VAR ) ) snprintf ( password , sizeof ( password ) , "%s" , getenv ( PASSWORD_ENV_VAR ) ) ;
 else read_password ( password , sizeof ( password ) ) ;
 }
 created_users = init_users ( my_ip , netmask ) ;
 if ( ( tun_fd = open_tun ( device ) ) == - 1 ) {
 retval = 1 ;
 goto cleanup0 ;
 }
 if ( ! skipipconfig ) {
 const char * other_ip = users_get_first_ip ( ) ;
 if ( tun_setip ( argv [ 0 ] , other_ip , netmask ) != 0 || tun_setmtu ( mtu ) != 0 ) {
 retval = 1 ;
 free ( ( void * ) other_ip ) ;
 goto cleanup1 ;
 }
 free ( ( void * ) other_ip ) ;
 }

 if ( nb_fds > 1 ) {
 retval = 1 ;
 warnx ( "Too many file descriptors received!\n" ) ;
 goto cleanup1 ;
 }
 else if ( nb_fds == 1 ) {
 dnsd_fd = SD_LISTEN_FDS_START ;
 }
 else {

 retval = 1 ;
 goto cleanup2 ;
 }


 if ( ( bind_fd = open_dns_from_host ( NULL , 0 , AF_INET , 0 ) ) < 0 ) {
 retval = 1 ;
 goto cleanup3 ;
 }
 }
 my_mtu = mtu ;
 if ( created_users < USERS ) {
 fprintf ( stderr , "Limiting to %d simultaneous users because of netmask /%d\n" , created_users , netmask ) ;
 }
 fprintf ( stderr , "Listening to dns for domain %s\n" , topdomain ) ;
 if ( foreground == 0 ) do_detach ( ) ;
 if ( pidfile != NULL ) do_pidfile ( pidfile ) ;



 signal ( SIGINT , sigint ) ;
 if ( username != NULL ) {

 gids [ 0 ] = pw -> pw_gid ;
 if ( setgroups ( 1 , gids ) < 0 || setgid ( pw -> pw_gid ) < 0 || setuid ( pw -> pw_uid ) < 0 ) {
 warnx ( "Could not switch to user %s!\n" , username ) ;
 usage ( ) ;
 }

 if ( context != NULL ) do_setcon ( context ) ;
 syslog ( LOG_INFO , "started, listening on port %d" , port ) ;
 tunnel ( tun_fd , dnsd_fd , bind_fd , max_idle_time ) ;
 syslog ( LOG_INFO , "stopping" ) ;
 cleanup3 : close_dns ( bind_fd ) ;
 cleanup2 : close_dns ( dnsd_fd ) ;
 cleanup1 : close_tun ( tun_fd ) ;
 cleanup0 : return retval ;
 }