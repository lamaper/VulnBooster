void save_config ( struct recvbuf * rbufp , int restrict_mask ) {
 static const char * illegal_in_filename = # if defined ( VMS ) ":[]" # elif defined ( SYS_WINNT ) ":\\/" # else "\\/" # endif ;
 char reply [ 128 ] ;

 char filename [ 128 ] ;
 char fullpath [ 512 ] ;
 const char savedconfig_eq [ ] = "savedconfig=" ;
 char savedconfig [ sizeof ( savedconfig_eq ) + sizeof ( filename ) ] ;
 time_t now ;
 int fd ;
 FILE * fptr ;

 snprintf ( reply , sizeof ( reply ) , "saveconfig prohibited by restrict ... nomodify" ) ;
 ctl_putdata ( reply , strlen ( reply ) , 0 ) ;
 ctl_flushpkt ( 0 ) ;
 NLOG ( NLOG_SYSINFO ) msyslog ( LOG_NOTICE , "saveconfig from %s rejected due to nomodify restriction" , stoa ( & rbufp -> recv_srcadr ) ) ;
 sys_restricted ++ ;
 return ;
 }

 snprintf ( reply , sizeof ( reply ) , "saveconfig prohibited, no saveconfigdir configured" ) ;
 ctl_putdata ( reply , strlen ( reply ) , 0 ) ;
 ctl_flushpkt ( 0 ) ;
 NLOG ( NLOG_SYSINFO ) msyslog ( LOG_NOTICE , "saveconfig from %s rejected, no saveconfigdir" , stoa ( & rbufp -> recv_srcadr ) ) ;
 return ;
 }
 if ( 0 == reqend - reqpt ) return ;
 strlcpy ( filespec , reqpt , sizeof ( filespec ) ) ;
 time ( & now ) ;
 if ( 0 == strftime ( filename , sizeof ( filename ) , filespec , localtime ( & now ) ) ) strlcpy ( filename , filespec , sizeof ( filename ) ) ;
 if ( NULL != strpbrk ( filename , illegal_in_filename ) ) {
 snprintf ( reply , sizeof ( reply ) , "saveconfig does not allow directory in filename" ) ;
 ctl_putdata ( reply , strlen ( reply ) , 0 ) ;
 ctl_flushpkt ( 0 ) ;
 msyslog ( LOG_NOTICE , "saveconfig with path from %s rejected" , stoa ( & rbufp -> recv_srcadr ) ) ;
 return ;
 }
 snprintf ( fullpath , sizeof ( fullpath ) , "%s%s" , saveconfigdir , filename ) ;
 fd = open ( fullpath , O_CREAT | O_TRUNC | O_WRONLY , S_IRUSR | S_IWUSR ) ;
 if ( - 1 == fd ) fptr = NULL ;
 else fptr = fdopen ( fd , "w" ) ;
 if ( NULL == fptr || - 1 == dump_all_config_trees ( fptr , 1 ) ) {
 snprintf ( reply , sizeof ( reply ) , "Unable to save configuration to file %s" , filename ) ;
 msyslog ( LOG_ERR , "saveconfig %s from %s failed" , filename , stoa ( & rbufp -> recv_srcadr ) ) ;
 }
 else {
 snprintf ( reply , sizeof ( reply ) , "Configuration saved to %s" , filename ) ;
 msyslog ( LOG_NOTICE , "Configuration saved to %s (requested by %s)" , fullpath , stoa ( & rbufp -> recv_srcadr ) ) ;
 snprintf ( savedconfig , sizeof ( savedconfig ) , "%s%s" , savedconfig_eq , filename ) ;
 set_sys_var ( savedconfig , strlen ( savedconfig ) + 1 , RO ) ;
 }
 if ( NULL != fptr ) fclose ( fptr ) ;


 ctl_flushpkt ( 0 ) ;
 }