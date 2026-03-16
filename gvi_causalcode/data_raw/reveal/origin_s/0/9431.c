static void do_outgoing_pipe ( connection_t * c , char * command ) {

 if ( socketpair ( AF_UNIX , SOCK_STREAM , 0 , fd ) ) {
 logger ( LOG_ERR , "Could not create socketpair: %s\n" , strerror ( errno ) ) ;
 return ;
 }
 if ( fork ( ) ) {
 c -> socket = fd [ 0 ] ;
 close ( fd [ 1 ] ) ;
 ifdebug ( CONNECTIONS ) logger ( LOG_DEBUG , "Using proxy %s" , command ) ;
 return ;
 }
 close ( 0 ) ;
 close ( 1 ) ;
 close ( fd [ 0 ] ) ;
 dup2 ( fd [ 1 ] , 0 ) ;
 dup2 ( fd [ 1 ] , 1 ) ;
 close ( fd [ 1 ] ) ;
 char * host = NULL ;
 char * port = NULL ;
 sockaddr2str ( & c -> address , & host , & port ) ;
 setenv ( "REMOTEADDRESS" , host , true ) ;
 setenv ( "REMOTEPORT" , port , true ) ;
 setenv ( "NODE" , c -> name , true ) ;
 setenv ( "NAME" , myself -> name , true ) ;
 if ( netname ) {
 setenv ( "NETNAME" , netname , true ) ;
 }
 int result = system ( command ) ;
 if ( result < 0 ) {
 logger ( LOG_ERR , "Could not execute %s: %s\n" , command , strerror ( errno ) ) ;
 }
 else if ( result ) {
 logger ( LOG_ERR , "%s exited with non-zero status %d" , command , result ) ;
 }
 exit ( result ) ;

 return ;
