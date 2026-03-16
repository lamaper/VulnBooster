static void check_perms_nopam ( const struct passwd * pw ) {
 const struct spwd * spwd = NULL ;
 const char * password = pw -> pw_passwd ;
 RETSIGTYPE ( * oldsig ) ( int ) ;
 if ( caller_is_root ) {
 return ;
 }
 if ( ( 0 == pw -> pw_uid ) && getdef_bool ( "SU_WHEEL_ONLY" ) && ! iswheel ( caller_name ) ) {
 fprintf ( stderr , _ ( "You are not authorized to su %s\n" ) , name ) ;
 exit ( 1 ) ;
 }
 spwd = getspnam ( name ) ;

 if ( NULL != spwd ) {
 password = spwd -> sp_pwdp ;
 }
 }
 switch ( check_su_auth ( caller_name , name , 0 == pw -> pw_uid ) ) {
 case 0 : break ;
 case 1 : password = "" ;
 break ;
 case 2 : ( void ) puts ( _ ( "(Enter your own password)" ) ) ;
 password = caller_pass ;
 break ;
 default : fprintf ( stderr , _ ( "You are not authorized to su %s\n" ) , name ) ;
 exit ( 1 ) ;
 }

 oldsig = signal ( SIGQUIT , die ) ;
 if ( pw_auth ( password , name , PW_SU , ( char * ) 0 ) != 0 ) {
 SYSLOG ( ( ( pw -> pw_uid != 0 ) ? LOG_NOTICE : LOG_WARN , "Authentication failed for %s" , name ) ) ;
 fprintf ( stderr , _ ( "%s: Authentication failure\n" ) , Prog ) ;
 su_failure ( caller_tty , 0 == pw -> pw_uid ) ;
 }
 ( void ) signal ( SIGQUIT , oldsig ) ;
 if ( NULL != spwd ) {
 ( void ) expire ( pw , spwd ) ;
 }
 if ( ! isttytime ( name , "SU" , time ( ( time_t * ) 0 ) ) ) {
 SYSLOG ( ( ( 0 != pw -> pw_uid ) ? LOG_WARN : LOG_CRIT , "SU by %s to restricted account %s" , caller_name , name ) ) ;
 fprintf ( stderr , _ ( "%s: You are not authorized to su at that time\n" ) , Prog ) ;
 su_failure ( caller_tty , 0 == pw -> pw_uid ) ;
 }
 }