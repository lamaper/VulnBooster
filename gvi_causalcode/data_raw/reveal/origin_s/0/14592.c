int virLogSetOutputs ( const char * src ) {
 int ret = - 1 ;
 int noutputs = 0 ;
 const char * outputstr = virLogDefaultOutput ;
 virLogOutputPtr * outputs = NULL ;
 if ( virLogInitialize ( ) < 0 ) return - 1 ;
 if ( src && * src ) outputstr = src ;
 if ( ! outputstr ) return 0 ;
 if ( ( noutputs = virLogParseOutputs ( outputstr , & outputs ) ) < 0 ) goto cleanup ;
 if ( virLogDefineOutputs ( outputs , noutputs ) < 0 ) goto cleanup ;
 outputs = NULL ;
 ret = 0 ;
 cleanup : virLogOutputListFree ( outputs , noutputs ) ;
 return ret ;
 }