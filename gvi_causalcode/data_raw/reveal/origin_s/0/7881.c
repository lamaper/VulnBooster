const char * TSInstallDirGet ( void ) {
 static std : : string prefix = Layout : : get ( ) -> prefix ;
 return prefix . c_str ( ) ;
 }