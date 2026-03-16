int * __xmlKeepBlanksDefaultValue ( void ) {
 if ( IS_MAIN_THREAD ) return ( & xmlKeepBlanksDefaultValue ) ;
 else return ( & xmlGetGlobalState ( ) -> xmlKeepBlanksDefaultValue ) ;
 }