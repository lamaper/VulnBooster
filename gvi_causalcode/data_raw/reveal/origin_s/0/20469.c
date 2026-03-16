relpRetVal relpTcpSetPrivKey ( relpTcp_t * pThis , char * cert ) {
 ENTER_RELPFUNC ;
 RELPOBJ_assert ( pThis , Tcp ) ;
 free ( pThis -> privKeyFile ) ;
 if ( cert == NULL ) {
 pThis -> privKeyFile = NULL ;
 }
 else {



 finalize_it : LEAVE_RELPFUNC ;
 }