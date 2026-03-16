const char * TSConfigDirGet ( void ) {
 static std : : string sysconfdir = RecConfigReadConfigDir ( ) ;
 return sysconfdir . c_str ( ) ;
 }