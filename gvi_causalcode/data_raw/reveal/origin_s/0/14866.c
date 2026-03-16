void virLogOutputFree ( virLogOutputPtr output ) {
 if ( ! output ) return ;
 if ( output -> c ) output -> c ( output -> data ) ;
 VIR_FREE ( output -> name ) ;
 VIR_FREE ( output ) ;
 }