TSMutex TSContMutexGet ( TSCont contp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 Continuation * c = ( Continuation * ) contp ;
 return ( TSMutex ) ( c -> mutex . get ( ) ) ;
 }