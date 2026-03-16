static void callOnErr ( const relpTcp_t * __restrict__ const pThis , char * __restrict__ const emsg , const relpRetVal ecode ) {
 char objinfo [ 1024 ] ;
 pThis -> pEngine -> dbgprint ( "librelp: generic error: ecode %d, " "emsg '%s'\n" , ecode , emsg ) ;
 if ( pThis -> pEngine -> onErr != NULL ) {
 if ( pThis -> pSrv == NULL ) {
 snprintf ( objinfo , sizeof ( objinfo ) , "conn to srvr %s:%s" , pThis -> pClt -> pSess -> srvAddr , pThis -> pClt -> pSess -> srvPort ) ;
 }
 else if ( pThis -> pRemHostIP == NULL ) {
 snprintf ( objinfo , sizeof ( objinfo ) , "lstn %s" , pThis -> pSrv -> pLstnPort ) ;
 }
 else {
 snprintf ( objinfo , sizeof ( objinfo ) , "lstn %s: conn to clt %s/%s" , pThis -> pSrv -> pLstnPort , pThis -> pRemHostIP , pThis -> pRemHostName ) ;
 }
 objinfo [ sizeof ( objinfo ) - 1 ] = '\0' ;
 pThis -> pEngine -> onErr ( pThis -> pUsr , objinfo , emsg , ecode ) ;
 }
 }