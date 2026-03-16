const char * TSPluginDirGet ( void ) {
 static std : : string path = RecConfigReadPluginDir ( ) ;
 return path . c_str ( ) ;
 }