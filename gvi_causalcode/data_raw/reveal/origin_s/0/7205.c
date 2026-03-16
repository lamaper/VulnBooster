const char * TSRuntimeDirGet ( void ) {
 static std : : string runtimedir = RecConfigReadRuntimeDir ( ) ;
 return runtimedir . c_str ( ) ;
 }