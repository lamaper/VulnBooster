int * __xmlDoValidityCheckingDefaultValue ( void ) {
 if ( IS_MAIN_THREAD ) return ( & xmlDoValidityCheckingDefaultValue ) ;
 else return ( & xmlGetGlobalState ( ) -> xmlDoValidityCheckingDefaultValue ) ;
 }