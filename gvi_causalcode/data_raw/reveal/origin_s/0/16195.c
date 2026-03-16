bool ispidowner ( pid_t pid ) {
 char path [ MAXPATHLEN ] ;
 struct stat sbuf ;
 snprintf ( path , sizeof ( path ) , "/proc/%d" , pid ) ;
 if ( stat ( path , & sbuf ) != 0 ) return ( FALSE ) ;
 if ( getuid ( ) != sbuf . st_uid ) return ( FALSE ) ;
 return ( TRUE ) ;
 }