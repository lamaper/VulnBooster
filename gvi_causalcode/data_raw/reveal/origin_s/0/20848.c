void remoteDispatchAuthError ( remote_error * rerr ) {
 remoteDispatchStringError ( rerr , VIR_ERR_AUTH_FAILED , "authentication failed" ) ;
 }