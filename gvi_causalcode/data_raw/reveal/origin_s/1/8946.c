void remoteDispatchConnError ( remote_error * rerr , virConnectPtr conn ATTRIBUTE_UNUSED ) {
 virErrorPtr verr = virGetLastError ( ) ;
 if ( verr ) remoteDispatchCopyError ( rerr , verr ) ;
 else remoteDispatchGenericError ( rerr ) ;
 }