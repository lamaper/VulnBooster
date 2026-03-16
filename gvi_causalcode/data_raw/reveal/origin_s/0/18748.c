static void virLogResetOutputs ( void ) {
 virLogOutputListFree ( virLogOutputs , virLogNbOutputs ) ;
 virLogOutputs = NULL ;
 virLogNbOutputs = 0 ;
 }