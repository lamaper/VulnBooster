static void set_environment ( struct passwd * pw ) {
 const char * cp ;
 if ( change_environment && fakelogin ) {
 cp = getenv ( "TERM" ) ;
 if ( NULL != cp ) {
 addenv ( "TERM" , cp ) ;
 }
 cp = getenv ( "COLORTERM" ) ;
 if ( NULL != cp ) {
 addenv ( "COLORTERM" , cp ) ;
 }

 if ( NULL != cp ) {
 addenv ( ( '/' == * cp ) ? tz ( cp ) : cp , NULL ) ;
 }
 cp = getdef_str ( "ENV_HZ" ) ;
 if ( NULL != cp ) {
 addenv ( cp , NULL ) ;
 }

 if ( NULL != cp ) {
 addenv ( "DISPLAY" , cp ) ;
 }
 cp = getenv ( "XAUTHORITY" ) ;
 if ( NULL != cp ) {
 addenv ( "XAUTHORITY" , cp ) ;
 }
 }
 else {
 char * * envp = environ ;
 while ( NULL != * envp ) {
 addenv ( * envp , NULL ) ;
 envp ++ ;
 }
 }
 cp = getdef_str ( ( pw -> pw_uid == 0 ) ? "ENV_SUPATH" : "ENV_PATH" ) ;
 if ( NULL == cp ) {
 addenv ( ( pw -> pw_uid == 0 ) ? "PATH=/sbin:/bin:/usr/sbin:/usr/bin" : "PATH=/bin:/usr/bin" , NULL ) ;
 }
 else if ( strchr ( cp , '=' ) != NULL ) {
 addenv ( cp , NULL ) ;
 }
 else {
 addenv ( "PATH" , cp ) ;
 }
 if ( getenv ( "IFS" ) != NULL ) {
 addenv ( "IFS= \t\n" , NULL ) ;
 }

 if ( change_environment ) {
 char * * envcp = pam_getenvlist ( pamh ) ;
 if ( NULL != envcp ) {
 while ( NULL != * envcp ) {
 addenv ( * envcp , NULL ) ;
 envcp ++ ;
 }
 }
 }


 if ( fakelogin ) {
 if ( shellstr != pw -> pw_shell ) {
 free ( pw -> pw_shell ) ;
 pw -> pw_shell = xstrdup ( shellstr ) ;
 }
 setup_env ( pw ) ;
 }
 else {
 addenv ( "HOME" , pw -> pw_dir ) ;
 addenv ( "USER" , pw -> pw_name ) ;
 addenv ( "LOGNAME" , pw -> pw_name ) ;
 addenv ( "SHELL" , shellstr ) ;
 }
 }
 }