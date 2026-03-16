void init_logging ( const char * name , u_int32 def_syslogmask , int is_daemon ) {
 static int was_daemon ;
 char * cp ;
 const char * pname ;
 if ( INIT_NTP_SYSLOGMASK == ntp_syslogmask && != def_syslogmask ) ntp_syslogmask = def_syslogmask ;
 cp = strrchr ( name , DIR_SEP ) ;
 if ( NULL == cp ) pname = name ;
 else pname = 1 + cp ;
 progname = estrdup ( pname ) ;

 if ( NULL != cp && ! strcasecmp ( cp , ".exe" ) ) * cp = '\0' ;




 else # endif setlogmask ( LOG_UPTO ( LOG_DEBUG ) ) ;
