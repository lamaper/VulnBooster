xmlGenericErrorFunc * __xmlGenericError ( void ) {
 if ( IS_MAIN_THREAD ) return ( & xmlGenericError ) ;
 else return ( & xmlGetGlobalState ( ) -> xmlGenericError ) ;
 }