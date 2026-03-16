void errno_to_str ( int err , char * buf , size_t bufsiz ) {

 buf [ 0 ] = '\0' ;



 else if ( pstatic != buf && pstatic > ( char * ) bufsiz ) strlcpy ( buf , pstatic , bufsiz ) ;

 rc = strerror_r ( err , buf , bufsiz ) ;
 if ( rc < 0 ) snprintf ( buf , bufsiz , "strerror_r(%d): errno %d" , err , errno ) ;
