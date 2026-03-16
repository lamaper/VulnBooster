relpRetVal relpTcpSend ( relpTcp_t * pThis , relpOctet_t * pBuf , ssize_t * pLenBuf ) {
 ssize_t written ;
 ENTER_RELPFUNC ;
 RELPOBJ_assert ( pThis , Tcp ) ;

 written = gnutls_record_send ( pThis -> session , pBuf , * pLenBuf ) ;
 pThis -> pEngine -> dbgprint ( "librelp: TLS send returned %d\n" , ( int ) written ) ;
 if ( written == GNUTLS_E_AGAIN || written == GNUTLS_E_INTERRUPTED ) {
 pThis -> rtryOp = relpTCP_RETRY_send ;
 written = 0 ;
 }
 else {
 pThis -> rtryOp = relpTCP_RETRY_none ;
 if ( written < 1 ) {
 chkGnutlsCode ( pThis , "TLS record write failed" , RELP_RET_IO_ERR , written ) ;
 ABORT_FINALIZE ( RELP_RET_IO_ERR ) ;
 }
 }
 }
 else {

 const int errno_save = errno ;
 pThis -> pEngine -> dbgprint ( "relpTcpSend: sock %d, lenbuf %zd, send returned %d [errno %d]\n" , ( int ) pThis -> sock , * pLenBuf , ( int ) written , errno_save ) ;
 if ( written == - 1 ) {
 switch ( errno_save ) {
 case EAGAIN : case EINTR : written = 0 ;
 break ;
 default : ABORT_FINALIZE ( RELP_RET_IO_ERR ) ;
 break ;
 }
 }


 finalize_it : LEAVE_RELPFUNC ;
 }