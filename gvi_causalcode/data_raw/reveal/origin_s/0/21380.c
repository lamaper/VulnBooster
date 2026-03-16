int * __xmlDefaultBufferSize ( void ) {
 if ( IS_MAIN_THREAD ) return ( & xmlDefaultBufferSize ) ;
 else return ( & xmlGetGlobalState ( ) -> xmlDefaultBufferSize ) ;
 }