void remoteDispatchError ( remote_error * rerr ) {
 virErrorPtr verr = virGetLastError ( ) ;
 if ( verr ) remoteDispatchCopyError ( rerr , verr ) ;
 else remoteDispatchGenericError ( rerr ) ;
 }