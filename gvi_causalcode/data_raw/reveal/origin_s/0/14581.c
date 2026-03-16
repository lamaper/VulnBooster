static void su_failure ( const char * tty , bool su_to_root ) {
 sulog ( tty , false , caller_name , name ) ;

 SYSLOG ( ( su_to_root ? LOG_NOTICE : LOG_INFO , "- %s %s:%s" , tty , ( '\0' != caller_name [ 0 ] ) ? caller_name : "???" , ( '\0' != name [ 0 ] ) ? name : "???" ) ) ;
 }
 closelog ( ) ;

 audit_log_acct_message ( audit_fd , AUDIT_USER_ROLE_CHANGE , NULL , "su" , ( '\0' != caller_name [ 0 ] ) ? caller_name : "???" , AUDIT_NO_ID , "localhost" , NULL , tty , 0 ) ;
 close ( audit_fd ) ;

 }