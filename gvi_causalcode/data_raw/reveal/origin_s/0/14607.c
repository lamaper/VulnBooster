int virLogDefineOutputs ( virLogOutputPtr * outputs , size_t noutputs ) {

 char * tmp = NULL ;

 virLogLock ( ) ;
 virLogResetOutputs ( ) ;

 if ( VIR_STRDUP_QUIET ( tmp , outputs [ id ] -> name ) < 0 ) {
 virLogUnlock ( ) ;
 return - 1 ;
 }
 VIR_FREE ( current_ident ) ;
 current_ident = tmp ;
 openlog ( current_ident , 0 , 0 ) ;
 }

 virLogNbOutputs = noutputs ;
 virLogUnlock ( ) ;
 return 0 ;
 }