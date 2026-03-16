static int rcancelrequested ( void ) {
 return InterruptPending && ( QueryCancelPending || ProcDiePending ) ;
 }