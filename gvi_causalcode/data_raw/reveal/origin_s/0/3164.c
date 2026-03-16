relpRetVal relpTcpDestruct ( relpTcp_t * * ppThis ) {
 relpTcp_t * pThis ;
 int i ;


 assert ( ppThis != NULL ) ;
 pThis = * ppThis ;
 RELPOBJ_assert ( pThis , Tcp ) ;
 if ( pThis -> sock != - 1 ) {
 close ( pThis -> sock ) ;
 pThis -> sock = - 1 ;
 }
 if ( pThis -> socks != NULL ) {
 for ( i = 1 ;
 i <= pThis -> socks [ 0 ] ;
 ++ i ) close ( pThis -> socks [ i ] ) ;
 free ( pThis -> socks ) ;
 }

 gnuRet = gnutls_bye ( pThis -> session , GNUTLS_SHUT_RDWR ) ;
 while ( gnuRet == GNUTLS_E_INTERRUPTED || gnuRet == GNUTLS_E_AGAIN ) {
 gnuRet = gnutls_bye ( pThis -> session , GNUTLS_SHUT_RDWR ) ;
 }
 gnutls_deinit ( pThis -> session ) ;
 }
 relpTcpFreePermittedPeers ( pThis ) ;

 free ( pThis -> pRemHostName ) ;
 free ( pThis -> pristring ) ;
 free ( pThis -> caCertFile ) ;
 free ( pThis -> ownCertFile ) ;
 free ( pThis -> privKeyFile ) ;
 free ( pThis ) ;
 * ppThis = NULL ;
 LEAVE_RELPFUNC ;
 }