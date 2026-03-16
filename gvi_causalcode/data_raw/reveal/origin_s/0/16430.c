static struct passwd * check_perms ( void ) {

 int ret ;

 if ( NULL == pw ) {
 ( void ) fprintf ( stderr , _ ( "No passwd entry for user '%s'\n" ) , name ) ;
 SYSLOG ( ( LOG_NOTICE , "No passwd entry for user '%s'" , name ) ) ;
 su_failure ( caller_tty , true ) ;
 }
 ( void ) signal ( SIGINT , SIG_IGN ) ;
 ( void ) signal ( SIGQUIT , SIG_IGN ) ;

 ret = pam_get_item ( pamh , PAM_USER , ( const void * * ) & tmp_name ) ;
 if ( ret != PAM_SUCCESS ) {
 SYSLOG ( ( LOG_ERR , "pam_get_item: internal PAM error\n" ) ) ;
 ( void ) fprintf ( stderr , "%s: Internal PAM error retrieving username\n" , Prog ) ;
 ( void ) pam_end ( pamh , ret ) ;
 su_failure ( caller_tty , 0 == pw -> pw_uid ) ;
 }
 if ( strcmp ( name , tmp_name ) != 0 ) {
 SYSLOG ( ( LOG_INFO , "Change user from '%s' to '%s' as requested by PAM" , name , tmp_name ) ) ;
 strncpy ( name , tmp_name , sizeof ( name ) - 1 ) ;
 name [ sizeof ( name ) - 1 ] = '\0' ;
 pw = xgetpwnam ( name ) ;
 if ( NULL == pw ) {
 ( void ) fprintf ( stderr , _ ( "No passwd entry for user '%s'\n" ) , name ) ;
 SYSLOG ( ( LOG_NOTICE , "No passwd entry for user '%s'" , name ) ) ;
 su_failure ( caller_tty , true ) ;
 }
 }


 ( void ) signal ( SIGQUIT , SIG_DFL ) ;
 if ( '*' == pw -> pw_shell [ 0 ] ) {
 subsystem ( pw ) ;
 endpwent ( ) ;
 endspent ( ) ;
 pw_free ( pw ) ;
 return check_perms ( ) ;
 }
 return pw ;
 }