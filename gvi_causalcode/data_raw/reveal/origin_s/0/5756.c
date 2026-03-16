const char * * __xmlParserVersion ( void ) {
 if ( IS_MAIN_THREAD ) return ( & xmlParserVersion ) ;
 else return ( & xmlGetGlobalState ( ) -> xmlParserVersion ) ;
 }