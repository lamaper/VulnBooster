int main ( int argc , char * * argv ) {
 const char * cp ;
 struct passwd * pw = NULL ;


 ( void ) bindtextdomain ( PACKAGE , LOCALEDIR ) ;
 ( void ) textdomain ( PACKAGE ) ;
 save_caller_context ( argv ) ;
 OPENLOG ( "su" ) ;
 process_flags ( argc , argv ) ;
 initenv ( ) ;

 if ( PAM_SUCCESS != ret ) {
 SYSLOG ( ( LOG_ERR , "pam_start: error %d" , ret ) ;
 fprintf ( stderr , _ ( "%s: pam_start: error %d\n" ) , Prog , ret ) ) ;
 exit ( 1 ) ;
 }
 ret = pam_set_item ( pamh , PAM_TTY , ( const void * ) caller_tty ) ;
 if ( PAM_SUCCESS == ret ) {
 ret = pam_set_item ( pamh , PAM_RUSER , ( const void * ) caller_name ) ;
 }
 if ( PAM_SUCCESS != ret ) {
 SYSLOG ( ( LOG_ERR , "pam_set_item: %s" , pam_strerror ( pamh , ret ) ) ) ;
 fprintf ( stderr , _ ( "%s: %s\n" ) , Prog , pam_strerror ( pamh , ret ) ) ;
 pam_end ( pamh , ret ) ;
 exit ( 1 ) ;
 }

 if ( ( NULL == shellstr ) && ! change_environment ) {
 shellstr = getenv ( "SHELL" ) ;
 }
 if ( ! caller_is_root && restricted_shell ( pw -> pw_shell ) ) {
 shellstr = NULL ;
 change_environment = true ;
 }
 if ( NULL == shellstr ) {
 shellstr = pw -> pw_shell ;
 }
 if ( ( NULL == shellstr ) || ( '\0' == shellstr [ 0 ] ) ) {
 shellstr = SHELL ;
 }
 sulog ( caller_tty , true , caller_name , name ) ;

 SYSLOG ( ( LOG_INFO , "+ %s %s:%s" , caller_tty , ( '\0' != caller_name [ 0 ] ) ? caller_name : "???" , ( '\0' != name [ 0 ] ) ? name : "???" ) ) ;
 }

 pam_end ( pamh , PAM_ABORT ) ;
 exit ( 1 ) ;
 }
 ret = pam_setcred ( pamh , PAM_ESTABLISH_CRED ) ;
 if ( PAM_SUCCESS != ret ) {
 SYSLOG ( ( LOG_ERR , "pam_setcred: %s" , pam_strerror ( pamh , ret ) ) ) ;
 fprintf ( stderr , _ ( "%s: %s\n" ) , Prog , pam_strerror ( pamh , ret ) ) ;
 ( void ) pam_end ( pamh , ret ) ;
 exit ( 1 ) ;
 }
 ret = pam_open_session ( pamh , 0 ) ;
 if ( PAM_SUCCESS != ret ) {
 SYSLOG ( ( LOG_ERR , "pam_open_session: %s" , pam_strerror ( pamh , ret ) ) ) ;
 fprintf ( stderr , _ ( "%s: %s\n" ) , Prog , pam_strerror ( pamh , ret ) ) ;
 pam_setcred ( pamh , PAM_DELETE_CRED ) ;
 ( void ) pam_end ( pamh , ret ) ;
 exit ( 1 ) ;
 }
 prepare_pam_close_session ( ) ;
 if ( change_uid ( pw ) != 0 ) {
 exit ( 1 ) ;
 }

 setup_limits ( pw ) ;
 }
 if ( setup_uid_gid ( pw , caller_on_console ) != 0 ) {
 exit ( 1 ) ;
 }

 audit_log_acct_message ( audit_fd , AUDIT_USER_ROLE_CHANGE , NULL , "su" , ( '\0' != caller_name [ 0 ] ) ? caller_name : "???" , AUDIT_NO_ID , "localhost" , NULL , caller_tty , 1 ) ;
 close ( audit_fd ) ;

 if ( ! doshell ) {
 int err = - 1 ;


 if ( fd >= 0 ) {
 err = ioctl ( fd , TIOCNOTTY , ( char * ) 0 ) ;
 ( void ) close ( fd ) ;
 }
 else if ( ENXIO == errno ) {
 err = 0 ;
 }

 ( void ) fprintf ( stderr , _ ( "%s: Cannot drop the controlling terminal\n" ) , Prog ) ;
 exit ( 1 ) ;
 }
 }
 endpwent ( ) ;
 endspent ( ) ;
 closelog ( ) ;
 if ( fakelogin ) {
 char * arg0 ;
 cp = getdef_str ( "SU_NAME" ) ;
 if ( NULL == cp ) {
 cp = Basename ( shellstr ) ;
 }
 arg0 = xmalloc ( strlen ( cp ) + 2 ) ;
 arg0 [ 0 ] = '-' ;
 strcpy ( arg0 + 1 , cp ) ;
 cp = arg0 ;
 }
 else {
 cp = Basename ( shellstr ) ;
 }
 if ( ! doshell ) {
 int err ;
 argv += optind ;
 if ( NULL != command ) {
 argv -= 2 ;
 argv [ 0 ] = "-c" ;
 argv [ 1 ] = command ;
 }
 argv [ - 1 ] = cp ;
 execve_shell ( shellstr , & argv [ - 1 ] , environ ) ;
 err = errno ;
 ( void ) fprintf ( stderr , _ ( "Cannot execute %s\n" ) , shellstr ) ;
 errno = err ;
 }
 else {
 ( void ) shell ( shellstr , cp , environ ) ;
 }
 pw_free ( pw ) ;
 return ( errno == ENOENT ? E_CMD_NOTFOUND : E_CMD_NOEXEC ) ;
 }