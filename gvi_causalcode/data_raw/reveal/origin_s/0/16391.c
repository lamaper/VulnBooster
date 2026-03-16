static void remoteDispatchStringError ( remote_error * rerr , int code , const char * msg ) {
 virError verr ;
 memset ( & verr , 0 , sizeof verr ) ;
 verr . code = code ;
 verr . domain = VIR_FROM_REMOTE ;
 verr . message = ( char * ) msg ;
 verr . level = VIR_ERR_ERROR ;
 verr . str1 = ( char * ) msg ;
 remoteDispatchCopyError ( rerr , & verr ) ;
 }