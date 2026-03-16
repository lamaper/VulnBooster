const char * * __xmlTreeIndentString ( void ) {
 if ( IS_MAIN_THREAD ) return ( & xmlTreeIndentString ) ;
 else return ( & xmlGetGlobalState ( ) -> xmlTreeIndentString ) ;
 }