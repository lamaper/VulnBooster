static int select_loop ( int maxFd , fd_set * workerset , bool * aborting ) {
 int i ;
 fd_set saveSet = * workerset ;
 if ( CancelRequested ) {
 * aborting = true ;
 return - 1 ;
 }
 else * aborting = false ;
 for ( ;
 ;
 ) {
 struct timeval * tvp ;

 0 , 1000000 }
 ;
 tvp = & tv ;


 i = select ( maxFd + 1 , workerset , NULL , NULL , tvp ) ;

 i = - 1 ;
 if ( WSAGetLastError ( ) == WSAEINTR ) errno = EINTR ;
 }

 if ( i < 0 || CancelRequested ) * aborting = true ;
 if ( i == 0 ) continue ;
 break ;
 }
 return i ;
 }