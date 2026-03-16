static void process_flags ( int argc , char * * argv ) {
 int c ;
 static struct option long_options [ ] = {
 {
 "command" , required_argument , NULL , 'c' }
 , {
 "help" , no_argument , NULL , 'h' }
 , {
 "login" , no_argument , NULL , 'l' }
 , {
 "preserve-environment" , no_argument , NULL , 'p' }
 , {
 "shell" , required_argument , NULL , 's' }
 , {
 NULL , 0 , NULL , '\0' }
 }
 ;
 while ( ( c = getopt_long ( argc , argv , "c:hlmps:" , long_options , NULL ) ) != - 1 ) {
 switch ( c ) {
 case 'c' : command = optarg ;
 break ;
 case 'h' : usage ( E_SUCCESS ) ;
 break ;
 case 'l' : fakelogin = true ;
 break ;
 case 'm' : case 'p' : change_environment = false ;
 break ;
 case 's' : shellstr = optarg ;
 break ;
 default : usage ( E_USAGE ) ;
 }
 }
 if ( ( optind < argc ) && ( strcmp ( argv [ optind ] , "-" ) == 0 ) ) {
 fakelogin = true ;
 optind ++ ;
 if ( ( optind < argc ) && ( strcmp ( argv [ optind ] , "--" ) == 0 ) ) {
 optind ++ ;
 }
 }
 if ( ( optind < argc ) && ( '-' != argv [ optind ] [ 0 ] ) ) {
 STRFCPY ( name , argv [ optind ++ ] ) ;
 if ( ( optind < argc ) && ( strcmp ( argv [ optind ] , "--" ) == 0 ) ) {
 optind ++ ;
 }
 }
 if ( '\0' == name [ 0 ] ) {
 struct passwd * root_pw = getpwnam ( "root" ) ;
 if ( ( NULL != root_pw ) && ( 0 == root_pw -> pw_uid ) ) {
 ( void ) strcpy ( name , "root" ) ;
 }
 else {
 root_pw = getpwuid ( 0 ) ;
 if ( NULL == root_pw ) {
 SYSLOG ( ( LOG_CRIT , "There is no UID 0 user." ) ) ;
 su_failure ( caller_tty , true ) ;
 }
 ( void ) strcpy ( name , root_pw -> pw_name ) ;
 }
 }
 doshell = ( argc == optind ) ;
 if ( NULL != command ) {
 doshell = false ;
 }
 }