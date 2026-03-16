void * * __xmlStructuredErrorContext ( void ) {
 if ( IS_MAIN_THREAD ) return ( & xmlStructuredErrorContext ) ;
 else return ( & xmlGetGlobalState ( ) -> xmlStructuredErrorContext ) ;
 }