int dtls1_shutdown ( SSL * s ) {
 int ret ;

 ret = BIO_dgram_sctp_wait_for_dry ( SSL_get_wbio ( s ) ) ;
 if ( ret < 0 ) return - 1 ;
 if ( ret == 0 ) BIO_ctrl ( SSL_get_wbio ( s ) , BIO_CTRL_DGRAM_SCTP_SAVE_SHUTDOWN , 1 , NULL ) ;
 }



 }