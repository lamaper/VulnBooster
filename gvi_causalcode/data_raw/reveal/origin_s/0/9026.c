void addto_syslog ( int level , const char * msg ) {
 static char const * prevcall_progname ;
 static char const * prog ;
 const char nl [ ] = "\n" ;
 const char empty [ ] = "" ;
 FILE * term_file ;
 int log_to_term ;
 int log_to_file ;
 int pid ;
 const char * nl_or_empty ;
 const char * human_time ;
 if ( progname != prevcall_progname ) {
 prevcall_progname = progname ;
 prog = strrchr ( progname , DIR_SEP ) ;
 if ( prog != NULL ) prog ++ ;
 else prog = progname ;
 }
 log_to_term = msyslog_term ;
 log_to_file = FALSE ;

 else # endif if ( syslog_file != NULL ) log_to_file = TRUE ;
 else log_to_term = TRUE ;


 if ( msyslog_include_timestamp ) human_time = humanlogtime ( ) ;
 else human_time = NULL ;
 if ( msyslog_term_pid || log_to_file ) pid = getpid ( ) ;
 else pid = - 1 ;
 if ( '\n' != msg [ strlen ( msg ) - 1 ] ) nl_or_empty = nl ;
 else nl_or_empty = empty ;
 if ( log_to_term ) {
 term_file = ( level <= LOG_ERR ) ? stderr : stdout ;
 if ( msyslog_include_timestamp ) fprintf ( term_file , "%s " , human_time ) ;
 if ( msyslog_term_pid ) fprintf ( term_file , "%s[%d]: " , prog , pid ) ;
 fprintf ( term_file , "%s%s" , msg , nl_or_empty ) ;
 fflush ( term_file ) ;
 }
 if ( log_to_file ) {
 if ( msyslog_include_timestamp ) fprintf ( syslog_file , "%s " , human_time ) ;
 fprintf ( syslog_file , "%s[%d]: %s%s" , prog , pid , msg , nl_or_empty ) ;
 fflush ( syslog_file ) ;
 }
 }