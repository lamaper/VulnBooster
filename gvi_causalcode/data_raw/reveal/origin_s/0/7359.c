void remoteDispatchGenericError ( remote_error * rerr ) {
 remoteDispatchStringError ( rerr , VIR_ERR_INTERNAL_ERROR , "library function returned error but did not set virterror" ) ;
 }