int TSContCall ( TSCont contp , TSEvent event , void * edata ) {
 Continuation * c = ( Continuation * ) contp ;
 return c -> handleEvent ( ( int ) event , edata ) ;
 }